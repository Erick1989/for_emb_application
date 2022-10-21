
#include <stdint.h>

__attribute__((naked)) void init_scheduler_stack(uint32_t scheduler_stack_top) {
  __asm volatile("MSR MSP,%0" ::"r"(scheduler_stack_top) :);
  __asm volatile("BX LR");
}