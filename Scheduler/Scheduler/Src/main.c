#include <stdint.h>
#include <stdio.h>
#include "scheduler.h"
#include "common.h"
#include "faulthandler.h"

void task1_handler(void);
void task2_handler(void);
void task3_handler(void);
void task4_handler(void);


uint32_t tasks_handlers[NUM_TASKS] = {
    (uint32_t)&task1_handler, (uint32_t)&task2_handler,
    (uint32_t)&task3_handler, (uint32_t)&task4_handler};


int main(void) {
  enable_processor_faults();
  init_scheduler_stack(SCHEDULER_STACK_START);
  init_task_stack();
  switch_sp_to_psp();
  init_systick_timer(TICK_HZ);
  task1_handler();
  for (;;)
    ;
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


