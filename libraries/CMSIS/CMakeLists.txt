add_library(CMSIS INTERFACE)

target_compile_definitions(
    CMSIS 
    INTERFACE
        -D${MCU_FAMILY}
)

target_include_directories(
    CMSIS
    INTERFACE
        Core/Include
        Device/STM32F3xx/Include
)
