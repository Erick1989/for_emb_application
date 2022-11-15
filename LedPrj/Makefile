CC=/usr/bin/arm-none-eabi-gcc
C=/usr/bin/g++
LIBS= -lgtest -lpthread

testRunner.o: testRunner.cpp LibraryCode.cpp
	$(C) $^ $(LIBS) -o $@

.PHONY: clean
clean:
	rm -rf *.o *.elf *.map

.PHONY: load
load:
	openocd -f /usr/share/openocd/scripts/board/stm32f4discovery.cfg -f /usr/share/openocd/scripts/interface/stlink-v2.cfg