add_executable(ram-128
    main.c
)

target_include_directories(ram-128 PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../../common
    )

target_link_libraries(ram-128 common)

####################
# Create .elf file #
####################

add_custom_command(TARGET ram-128 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_BINARY_DIR}/ram-128
    ${CMAKE_CURRENT_BINARY_DIR}/ram-128.elf
)

# Create disassembly file with all sections
add_custom_command(TARGET ram-128 POST_BUILD
    COMMAND riscv32-unknown-elf-objdump 
    -D -S -r -x -t ${CMAKE_CURRENT_BINARY_DIR}/ram-128
    > ${CMAKE_CURRENT_BINARY_DIR}/ram-128.dis
)
