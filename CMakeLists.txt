cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE cmake/arm-none-eabi-gcc.cmake)

project(
	STM32F3_Blinky
	C CXX ASM
)

set(MCU_FAMILY STM32F303xC)
set(MCU_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")
set(LDSCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/stm32f303.ld")
set(LIBS "-lc -lm -lnosys -mfpu=fpv4-sp-d16 -mfloat-abi=hard")
set(LINKER_FLAGS "${MCU_FLAGS} -specs=nano.specs -T${LDSCRIPT} ${LIBS} -Wl,-Map=${PROJECT_NAME}.map,--cref -Wl,--gc-sections")

if(NOT CMAKE_BUILD_TYPE) 
	set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
	set(C_FLAGS "${MCU_FLAGS} -g -gdwarf-2")
	message(STATUS "Build type: Debug")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
	set(C_FLAGS "${MCU_FLAGS}")
	message(STATUS "Build type: Release")
endif()

set(
	CMAKE_C_FLAGS
	"${C_FLAGS} -fdata-sections -ffunction-sections"
	CACHE INTERNAL ""
)

set(
	CMAKE_ASM_FLAGS
	"-x assembler-with-cpp ${C_FLAGS} -Wall -fdata-sections -ffunction-sections"
	CACHE INTERNAL ""
)

set(
	CMAKE_EXE_LINKER_FLAGS
	"${LINKER_FLAGS}"
)

set(EXECUTABLE	${PROJECT_NAME}.elf)

set(
	SRCS
	app/src/main.c
	app/src/LED.c
	app/src/system_stm32f3xx.c
	app/src/startup_stm32f303xc.s
)

add_executable(
	${EXECUTABLE}
	${SRCS}
)

target_include_directories(${EXECUTABLE} PRIVATE app/inc)

add_subdirectory(libraries)

target_link_libraries(
	${EXECUTABLE}
	PRIVATE
		CMSIS
		STM32F3xx_HAL
)

include(cmake/stm32-postbuild.cmake)
