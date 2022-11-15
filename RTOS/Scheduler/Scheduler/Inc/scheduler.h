#ifndef SCHEDULER
#define SCHEDULER
/*RAM MEMORY LAYOUT*/

/*G-------------------F----------E----------D----------C----------B---------A*/
/*--------------------X----------X----------X----------X----------X----------*/
/*--------------------X-SCHED----X----TASK4-X----TASK3-X----TASK2-X----TASK1-*/
/*--------------------X----------X----------X----------X----------X----------*/
/*--------------------X----------X----------X----------X----------X----------*/
/*--------------------X----------X----------X----------X----------X----------*/
/*--------------------X----------X----------X----------X----------X----------*/
/*--------------------X----------X----------X----------X----------X----------*/
/*--------------------X----------X----------X----------X----------X----------*/
/*<                              128KB of RAM                               >*/
/*A=SRAM_END= ,G=SRAM_START*/
/*<A-B>= SZ_TASK_STACK, TASK1 stack space           */
/*<B-C>= SZ_TASK_STACK, TASK2 stack space           */
/*<C-D>= SZ_TASK_STACK, TASK3 stack space           */
/*<D-E>= SZ_SCHEDULER_STACK, SCHEDULER stack space  */
/*<F-G>= Unsed  */

#include <stdint.h>
#include <stddef.h>
#include "common.h"

#define SZ_TASK_STACK (1024U)
#define SZ_SCHEDULER_STACK (1024U)
#define SRAM_START (0x20000000U)
#define SZ_SRAM ((128) * (1024))
#define SRAM_END ((SRAM_START) + (SZ_SRAM))

#define T1_STACK_START (SRAM_END)
#define T2_STACK_START ((SRAM_END) - (1 * (SZ_TASK_STACK)))
#define T3_STACK_START ((SRAM_END) - (2 * (SZ_TASK_STACK)))
#define T4_STACK_START ((SRAM_END) - (3 * (SZ_TASK_STACK)))
#define SCHEDULER_STACK_START ((SRAM_END) - (4 * (SZ_SCHEDULER_STACK)))

#define TICK_HZ 1000U
#define HSI_CLK 16000000U
#define SYSTICK_TIM_CLK HSI_CLK

__attribute__((naked)) void init_scheduler_stack(uint32_t scheduler_stack_top);
__attribute__((naked)) void switch_sp_to_psp(void);
__attribute__((naked)) void SysTick_Handler(void);


void init_systick_timer(uint32_t tick_hz);
void init_task_stack(void);
#endif
