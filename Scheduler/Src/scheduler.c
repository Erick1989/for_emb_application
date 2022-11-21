
#include "scheduler.h"
#include "main.h"
#include <stdint.h>

#define DUMMY_XPSR 0x01000000U

#define TASK_READY_STATE 0x00
#define TASK_BLOCKED_STATE 0XFF

extern TCB_t user_tasks[NUM_TASKS];


static void init_task_const_param();
static void init_task_handlers();
static void init_psp_of_tasks();

void init_task_stack()
{
	uint32_t *pPSP = NULL;

	init_task_const_param();
	init_psp_of_tasks();
	init_task_handlers();

	for (int i = 0; i < elcount(user_tasks); i++)
	{
		pPSP = (uint32_t *)user_tasks[i].psp_value;
		pPSP--;
		*pPSP = DUMMY_XPSR; // DUMMY XPSR
		pPSP--;
		*pPSP = (uint32_t)user_tasks[i].task_handler; // PC
		pPSP--;
		*pPSP = 0xFFFFFD; // LR
		for (int j = 0; j < 13; j++)
		{
			pPSP--;
			*pPSP = 0;
		}
		user_tasks[i].psp_value = (uint32_t)pPSP;
	}
	return;
}

static void init_task_const_param()
{
	for (int i = 0; i < NUM_TASKS; i++)
	{
		user_tasks[i].state = TASK_READY_STATE;
		user_tasks[i].block_count = 0;
	}
}

static void init_task_handlers()
{
	user_tasks[0].task_handler = &idle_task;
	user_tasks[1].task_handler = &task1_handler;
	user_tasks[2].task_handler = &task2_handler;
	user_tasks[3].task_handler = &task3_handler;
	user_tasks[4].task_handler = &task4_handler;
}

static void init_psp_of_tasks()
{
	user_tasks[0].psp_value = IDLE_STACK_START;
	user_tasks[1].psp_value = T1_STACK_START;
	user_tasks[2].psp_value = T2_STACK_START;
	user_tasks[3].psp_value = T3_STACK_START;
	user_tasks[4].psp_value = T4_STACK_START;
}

__attribute__((naked)) void init_scheduler_stack(uint32_t scheduler_stack_top)
{
	__asm volatile("MSR MSP,%0" ::"r"(scheduler_stack_top)
				   :);
	__asm volatile("BX LR");
}


uint16_t current_task = 1;
uint32_t get_psp_value(void)
{
	return user_tasks[current_task].psp_value;
}

uint16_t get_next_ready_task(void)
{
	const uint16_t num_tasks = elcount(user_tasks);
	uint16_t i = (current_task + 1) % num_tasks;

	for (uint16_t j = 0; j < num_tasks; j++)
	{
		if (user_tasks[i].state == TASK_READY_STATE)
		{
			if (i == 0)
				continue;
			else
				return i;
		}
		i = (i + 1) % num_tasks;
	}
	return 0;
}

void update_next_task(void)
{
	current_task = get_next_ready_task();
}

__attribute__((naked)) void switch_sp_to_psp(void)
{
	// Initialize PSP with TASK1 stack start address
	__asm volatile("PUSH {LR}");
	__asm volatile("BL get_psp_value");
	__asm volatile("MSR PSP,R0");
	__asm volatile("POP {LR}");
	// Change SP to PSP using CONTROL register
	__asm volatile("MOV R0,#0x02");
	__asm volatile("MSR CONTROL,R0");
	__asm volatile("BX LR");
}

void init_systick_timer(uint32_t tick_hz)
{
	uint32_t *pSYST_RVR = (uint32_t *)0xE000E014;
	uint32_t *pSYST_CSR = (uint32_t *)0xE000E010;

	uint32_t count = (SYSTICK_TIM_CLK / tick_hz) - 1;
	*pSYST_RVR &= ~(0x00FFFFFFFF); // clear SVR
	*pSYST_RVR |= count;

	*pSYST_CSR |= (1 << 1); // enable Systick exception request
	*pSYST_CSR |= (1 << 2); // processor clock as clock source
	*pSYST_CSR |= (1 << 0); // enables counter

	return;
}

void save_psp_value(uint32_t current_psp_value)
{
	user_tasks[current_task].psp_value = current_psp_value;
	return;
}

__attribute__((naked)) void PendSV_Handler(void)
{
	/*Save the Context of the Current Task*/
	__asm volatile("PUSH {LR}");
	/*Get current running tasks PSP value*/
	__asm volatile("MRS R0,PSP");
	/*Using that PSP store SF2 (R4 to R11)*/
	__asm volatile("STMDB R0!,{R4-R11}");
	/*Save the current value of PSP*/
	__asm volatile("BL save_psp_value");
	/*Retrieve the Context of the Next Task*/
	/*Decide the next task to run*/
	__asm volatile("BL update_next_task");
	/*Get PSP value*/
	__asm volatile("BL get_psp_value");
	/*Retrieve SF2 (R4 to R11) from the retrieven PSP*/
	__asm volatile("LDMIA R0!,{R4-R11}");
	/*Uptade PSP value*/
	__asm volatile("MSR PSP,R0");
	__asm volatile("POP {LR}");
	__asm volatile("BX LR");
}

uint32_t g_tick_count = 0;
void update_global_tick_count(void)
{
	g_tick_count++;
}

void schedule(void)
{
	uint32_t *pICSR = (uint32_t *)0xE000ED04;
	*pICSR |= (1 << 28);
}

void task_delay(uint32_t tick_count)
{
	if (current_task != 0)
	{
		user_tasks[current_task].block_count = g_tick_count + tick_count;
		user_tasks[current_task].state = TASK_BLOCKED_STATE;
		schedule();
	}
}

void unblock_tasks()
{
	for (int i = 1; i < elcount(user_tasks); i++)
	{
		if (user_tasks[i].state == TASK_BLOCKED_STATE)
		{
			if (user_tasks[i].block_count <= g_tick_count)
				user_tasks[i].state = TASK_READY_STATE;
		}
	}
	return;
}

void SysTick_Handler(void)
{
	update_global_tick_count();
	unblock_tasks();
	schedule();
}
