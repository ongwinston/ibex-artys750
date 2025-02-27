add_executable(artys7_demo
    main.c
    test_gpio.c
    test_pwm.c
    test_uart.c
    test_wishbone.c
    romantoint.c
)

target_include_directories(artys7_demo PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../common
    )

target_link_libraries(artys7_demo common)

####################
# Create .elf file #
####################

add_custom_command(TARGET artys7_demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_BINARY_DIR}/artys7_demo
    ${CMAKE_CURRENT_BINARY_DIR}/artys7_demo.elf
)

# Create disassembly file with all sections
add_custom_command(TARGET artys7_demo POST_BUILD
    COMMAND riscv32-unknown-elf-objdump 
    -D -S -r -x -t ${CMAKE_CURRENT_BINARY_DIR}/artys7_demo
    > ${CMAKE_CURRENT_BINARY_DIR}/artys7_demo.dis
)
