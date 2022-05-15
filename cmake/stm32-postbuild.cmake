set(TARGET_BIN ${PROJECT_NAME}.bin)
set(TARGET_HEX ${PROJECT_NAME}.hex)
set(TARGET_LSS ${PROJECT_NAME}.lss)

# create binary & hex files and show size of resulting firmware image
add_custom_command(
    TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${TARGET_HEX}
    COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${TARGET_BIN}
    COMMAND ${CMAKE_DUMP} -S $<TARGET_FILE:${PROJECT_NAME}.elf> > ${TARGET_LSS}
    COMMAND ${CMAKE_SIZE} -B ${PROJECT_NAME}.elf
    COMMENT "Generating ${TARGET_BIN}, ${TARGET_HEX} and ${TARGET_LSS}"
)
