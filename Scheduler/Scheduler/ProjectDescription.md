# Simple Project Description

A simple scheduller will be created to demonstrate RTOS knowledge. The objective 
is to create a simple kernel that will schedule 4 tasks and each task must 
toggle an LED.

The tasks and the scheduller will have a different stack spaces, the scheduller 
will use MSP as holder for its current SP and the tasks will share PSP.
