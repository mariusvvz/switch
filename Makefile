# MPLAB IDE generated this makefile for use with GNU make.
# Project: switch c.mcp
# Date: Sat Nov 10 13:34:37 2012

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

switch\ c.cof : Untitled.o
	$(LD) /p18F45K22 /l"C:\Program Files (x86)\Microchip\mplabc18\v3.40\lib" "Untitled.o" /u_CRUNTIME /z__MPLAB_BUILD=1 /o"switch c.cof" /M"switch c.map" /W

Untitled.o : ../../../photobooth/switch/Untitled.c ../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/delays.h ../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/stdio.h ../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/math.h ../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/USART.h ../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/stdlib.h ../../../photobooth/switch/Untitled.c ../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/p18f45k22.h ../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/p18cxxx.h ../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/stdarg.h ../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/stddef.h ../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/pconfig.h
	$(CC) -p=18F45K22 "C:\Users\Marius\Desktop\photobooth\switch\Untitled.c" -fo="Untitled.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "Untitled.o" "switch c.cof" "switch c.hex"

