#include <stdint.h>
#include <stdio.h>
#include "scheduler.h"
#include "common.h"
#include "faulthandler.h"
#include "main.h"
#include "led.h"



TCB_t user_tasks[NUM_TASKS];

int main(void) {
  enable_processor_faults();
  init_scheduler_stack(SCHEDULER_STACK_START);
  init_task_stack();
  switch_sp_to_psp();
  led_init_all();
  led_on(LED_GREEN);
  init_systick_timer(TICK_HZ);
  task1_handler();
  for (;;)
    ;
}

void idle_task(void){
	while(1);
}

void task1_handler(void){
	while(1){
		led_on(LED_GREEN);
		task_delay(1000);
		led_off(LED_GREEN);
		task_delay(1000);
	}
}

void task2_handler(void){
	while(1){
		led_on(LED_BLUE);
		task_delay(250);
		led_off(LED_BLUE);
		task_delay(250);
	}
}

void task3_handler(void){
	while(1){
		led_on(LED_RED);
		task_delay(500);
		led_off(LED_RED);
		task_delay(500);
	}
}

void task4_handler(void){
	while(1){
		led_on(LED_ORANGE);
		task_delay(500);
		led_off(LED_ORANGE);
		task_delay(500);
	}
}