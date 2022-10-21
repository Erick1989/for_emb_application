/*RAM MEMORY LAYOUT*/

/*G------------------F----------E----------D----------C----------B----------A*/
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


#define SZ_TASK_STACK          (1024U)
#define SZ_SCHEDULER_STACK     (1024U)
#define SRAM_START		       (0x20000000U)
#define SZ_SRAM		           ((128) * (1024))
#define SRAM_END	           ((SRAM_START) + (SZ_SRAM))

#define T1_STACK_START         (SRAM_END)
#define T2_STACK_START         ((SRAM_END) - (1*(SZ_TASK_STACK)))
#define T3_STACK_START         ((SRAM_END) - (2*(SZ_TASK_STACK)))
#define T4_STACK_START         ((SRAM_END) - (3*(SZ_TASK_STACK)))
#define SCHEDULER_STACK_START  ((SRAM_END) - (4*(SZ_SCHEDULER_STACK)))
