#!/bin/sh
arm-none-eabi-gdb ./Demo.elf
#target remote localhost:3333
#monitor reset init` 
#monitor flash write_image erase Demo.elf` 
#monitor reset halt` 

#gdb usefull commands
#b file.cpp:line num
    #b Demo.cpp:11
    #b LedDriver.cpp:15
    #i b  -- list breakpoints
#print 
    #/x for hex 
    #/t for bin
    #/d for dec

#print /x pRccAhb1enr
#print /t *pRccAhb1enr
#display /x  pGpioBase
#display /t  *pGpioBase
#display /x  pGpioOdrReg
#display /t  *pGpioOdrReg


#to reset: monitor reset halt
#continue
    #c
#step 
    #s
