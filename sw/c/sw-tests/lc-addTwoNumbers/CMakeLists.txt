add_executable(lc-addTwoNumbers
    main.c
)

target_include_directories(lc-addTwoNumbers PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../../common
    )

target_link_libraries(lc-addTwoNumbers common)

####################
# Create .elf file #
####################

add_custom_command(TARGET lc-addTwoNumbers POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_BINARY_DIR}/lc-addTwoNumbers
    ${CMAKE_CURRENT_BINARY_DIR}/lc-addTwoNumbers.elf
)

# Create disassembly file with all sections
add_custom_command(TARGET lc-addTwoNumbers POST_BUILD
    COMMAND riscv32-unknown-elf-objdump 
    -D -S -r -x -t ${CMAKE_CURRENT_BINARY_DIR}/lc-addTwoNumbers
    > ${CMAKE_CURRENT_BINARY_DIR}/lc-addTwoNumbers.dis
)
