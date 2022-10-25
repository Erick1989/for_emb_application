
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