CC=/usr/bin/arm-none-eabi-g++
C=/usr/bin/g++
C_FLAGS= -g3
LIBS= -lgtest -lpthread -lgmock -lgmock_main
CC_FLAGS= -c -mcpu=cortex-m4 -mfloat-abi=soft -g3 -mthumb -std=gnu++14 -O0 -Wall --specs=nano.specs
CC_START_UP_FLAGS = -x assembler-with-cpp -MMD -MP

LKFLAGS= --specs=nosys.specs -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group

TEST_INC= -I ./inc -I ./inc/test 
SRC_INC=  -I ./inc -I ./inc/target

TEST_BUILD_DIR= build/UnitTest
DRIVER_BUILD_DIR= build/LedDriver
DEMO_BUILD_DIR= build/Demo

all: test driver demo start_up link

test:$(TEST_BUILD_DIR)/testRunner.o
driver:$(DRIVER_BUILD_DIR)/LedDriver.o
mock:$(DRIVER_BUILD_DIR)/RunTimeError.o
demo:$(DEMO_BUILD_DIR)/Demo.o
start_up:$(DEMO_BUILD_DIR)/startup_stm32f407vgtx.o
link:$(DEMO_BUILD_DIR)/Demo.elf

objects = $(DRIVER_BUILD_DIR)/RunTimeError.o $(DRIVER_BUILD_DIR)/LedDriver.o $(DEMO_BUILD_DIR)/Demo.o $(DEMO_BUILD_DIR)/startup_stm32f407vgtx.o

$(DEMO_BUILD_DIR)/Demo.elf: driver demo mock start_up src/STM32F407VGTX_FLASH.ld
	$(CC) -o "$@" $(objects)  -mcpu=cortex-m4 -T"src/STM32F407VGTX_FLASH.ld" -Wl,-Map="$(DEMO_BUILD_DIR)/Demo.map" $(LKFLAGS)

$(TEST_BUILD_DIR)/testRunner.o:test/testRunner.cpp test/Mock_RunTimeError.cpp src/LedDriver.cpp 
	$(C) $^ $(LIBS) $(TEST_INC) $(C_FLAGS) -o $@

$(DRIVER_BUILD_DIR)/LedDriver.o:src/LedDriver.cpp
	$(CC) $^ $(CC_FLAGS) $(SRC_INC) -o $@

$(DRIVER_BUILD_DIR)/RunTimeError.o:src/RunTimeError.cpp
	$(CC) $^ $(CC_FLAGS) $(SRC_INC) -o $@

$(DEMO_BUILD_DIR)/Demo.o:src/Demo.cpp
	$(CC)  $(CC_FLAGS)  $(SRC_INC) $^ -o $@

$(DEMO_BUILD_DIR)/startup_stm32f407vgtx.o:src/startup_stm32f407vgtx.s
	$(CC)  $(CC_FLAGS) $(CC_START_UP_FLAGS) $(SRC_INC) -MF"$(DEMO_BUILD_DIR)/startup_stm32f407vgtx.d" -MT"$@" $^ -o $@

.PHONY: clean
clean:
	rm -rf $(TEST_BUILD_DIR)/*.o $(TEST_BUILD_DIR)/*.elf $(TEST_BUILD_DIR)/*.map
	rm -rf $(DRIVER_BUILD_DIR)/*.o $(DRIVER_BUILD_DIR)/*.elf $(DRIVER_BUILD_DIR)/*.map
	rm -rf $(DEMO_BUILD_DIR)/*.o $(DEMO_BUILD_DIR)/*.elf $(DEMO_BUILD_DIR)/*.map $(DEMO_BUILD_DIR)/*.d
