#include "faulthandler.h"

void enable_processor_faults(void) {
  uint32_t *const pSHCSR = (uint32_t *)0xE000ED24;
  *pSHCSR |= (1 << 16);  // mem manage
  *pSHCSR |= (1 << 17);  // bus handler
  *pSHCSR |= (1 << 18);  // usage fault
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
