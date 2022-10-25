#include <stdint.h>
#include <stdio.h>

#include "scheduler.h"

void enable_processor_faults(void);
void init_task_stack(void);
void task1_handler(void);
void task2_handler(void);
void task3_handler(void);
void task4_handler(void);

#define NUM_TASKS 4U
#define DUMMY_XPSR 0x01000000U
#define elcount(x) (sizeof(x) / sizeof((x[0])))

uint32_t psp_of_tasks[NUM_TASKS] = {T1_STACK_START, T2_STACK_START,
                                    T3_STACK_START, T4_STACK_START};
uint32_t tasks_handlers[NUM_TASKS] = {
    (uint32_t)&task1_handler, (uint32_t)&task2_handler,
    (uint32_t)&task3_handler, (uint32_t)&task4_handler};

uint16_t current_task=0;

int main(void) {
  enable_processor_faults();
  init_scheduler_stack(SCHEDULER_STACK_START);
  init_task_stack();
  switch_sp_to_psp();
  init_systick_timer(TICK_HZ);
  for (;;)
    ;
}

void enable_processor_faults(void) {
  uint32_t *const pSHCSR = (uint32_t *)0xE000ED24;
  *pSHCSR |= (1 << 16);  // mem manage
  *pSHCSR |= (1 << 17);  // bus handler
  *pSHCSR |= (1 << 18);  // usage fault
}

uint32_t get_psp_value(void){
	return psp_of_tasks[current_task];
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

void task1_handler(void) {
  while (1) {
    printf("This is task1\n");
  }
}

void task2_handler(void) {
  while (1) {
    printf("This is task2\n");
  }
}

void task3_handler(void) {
  while (1) {
    printf("This is task3\n");
  }
}

void task4_handler(void) {
  while (1) {
    printf("This is task4\n");
  }
}

void MemManage_Handler(void) {
  printf("MemManage_Handler");
  while (1)
    ;
}

void UsageFault_Handler(void) {
  printf("UsageFault_Handler");
  while (1)
    ;
}

void BusFault_Handler(void) {
  printf("BusFault_Handler");
  while (1)
    ;
}

void HardFault_Handler(void) {
  printf("HardFault_Handler");
  while (1)
    ;
}
