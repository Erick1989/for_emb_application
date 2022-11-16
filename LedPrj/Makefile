CC=/usr/bin/arm-none-eabi-gcc
C=/usr/bin/g++
LIBS= -lgtest -lpthread
TEST_INC= -I ./inc -I ./inc/test 
SRC_INC=  -I ./inc -I ./inc/target

testRunner.o:test/testRunner.cpp src/LedDriver.cpp 
	$(C) $^ $(LIBS) $(TEST_INC) -o $@

LibraryCode.o:src/LibraryCode2.cpp
	$(C) $^ $(LIBS) $(SRC_INC) -o $@

.PHONY: clean
clean:
	rm -rf *.o *.elf *.map

.PHONY: load
load:
	openocd -f /usr/share/openocd/scripts/board/stm32f4discovery.cfg -f /usr/share/openocd/scripts/interface/stlink-v2.cfg