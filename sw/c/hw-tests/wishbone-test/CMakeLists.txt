add_executable(wishbone-test
    main.c
)

target_include_directories(wishbone-test PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../../common
    )

target_link_libraries(wishbone-test common)

####################
# Create .elf file #
####################

add_custom_command(TARGET wishbone-test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_BINARY_DIR}/wishbone-test
    ${CMAKE_CURRENT_BINARY_DIR}/wishbone-test.elf
)

# Create disassembly file with all sections
add_custom_command(TARGET wishbone-test POST_BUILD
    COMMAND riscv32-unknown-elf-objdump 
    -D -S -r -x -t ${CMAKE_CURRENT_BINARY_DIR}/wishbone-test
    > ${CMAKE_CURRENT_BINARY_DIR}/wishbone-test.dis
)
