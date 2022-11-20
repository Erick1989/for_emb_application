
#include "scheduler.h"

#include <stdint.h>

#define DUMMY_XPSR 0x01000000U

uint16_t current_task=0;
uint32_t psp_of_tasks[NUM_TASKS] = {T1_STACK_START, T2_STACK_START,
                                    T3_STACK_START, T4_STACK_START};

extern uint32_t tasks_handlers[NUM_TASKS];

__attribute__((naked)) void init_scheduler_stack(uint32_t scheduler_stack_top) {
  __asm volatile("MSR MSP,%0" ::"r"(scheduler_stack_top) :);
  __asm volatile("BX LR");
}

void init_task_stack() {
  uint32_t *pPSP = NULL;
  for (int i = 0; i < elcount(psp_of_tasks); i++) {
    pPSP = (uint32_t *)psp_of_tasks[i];
    pPSP--;
    *pPSP = DUMMY_XPSR;  // DUMMY XPSR
    pPSP--;
    *pPSP = tasks_handlers[i];  // PC
    pPSP--;
    *pPSP = 0xFFFFFD;  // LR
    for (int j = 0; j < 13; j++) {
      pPSP--;
      *pPSP = 0;
    }
    psp_of_tasks[i] = (uint32_t)pPSP;
  }
  return;
}

__attribute__((naked)) void switch_sp_to_psp(void) {
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


void init_systick_timer(uint32_t tick_hz) {
  uint32_t *pSYST_RVR = (uint32_t *)0xE000E014;
  uint32_t *pSYST_CSR = (uint32_t *)0xE000E010;

  uint32_t count = (SYSTICK_TIM_CLK / tick_hz) - 1;
  *pSYST_RVR &= ~(0x00FFFFFFFF);  // clear SVR
  *pSYST_RVR |= count;

  *pSYST_CSR |= (1 << 1);  // enable Systick exception request
  *pSYST_CSR |= (1 << 2);  // processor clock as clock source
  *pSYST_CSR |= (1 << 0);  // enables counter

  return;
}

__attribute__((naked)) void SysTick_Handler(void) {
  	/*Save the Context of the Current Task*/
	__asm volatile ("PUSH {LR}");
	  /*Get current running tasks PSP value*/
	__asm volatile ("MRS R0,PSP");
	  /*Using new task PSP store (R4 to R11)*/
	__asm volatile ("STMDB R0!,{R4-R11}");
	  /*Save the current value of PSP*/
	__asm volatile ("BL save_psp_value");
	/*Retrieve the Context of the Next Task*/
	  /*Decide the next task to run*/
	__asm volatile ("BL update_next_task");
	  /*Get PSP value*/
	__asm volatile ("BL get_psp_value");
	  /*Retrieve SF2 (R4 to R11) from the retrieven PSP*/
	__asm volatile ("LDMIA R0!,{R4-R11}");
	  /*Uptade PSP value*/
	__asm volatile ("MSR PSP,R0");
	__asm volatile ("POP {LR}");
	__asm volatile ("BX LR");
  }

static void save_psp_value(uint32_t current_psp_value){
	psp_of_tasks[current_task]= current_psp_value;
	return;
}

static void update_next_task(void){
	current_task++;
	current_task%=NUM_TASKS;
}

static uint32_t get_psp_value(void){
	return psp_of_tasks[current_task];
}



