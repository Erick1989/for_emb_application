
#include "scheduler.h"

#include <stdint.h>

__attribute__((naked)) void init_scheduler_stack(uint32_t scheduler_stack_top) {
  __asm volatile("MSR MSP,%0" ::"r"(scheduler_stack_top) :);
  __asm volatile("BX LR");
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

__attribute__((naked)) void SysTick_Handler(void) { __asm volatile("NOP"); }