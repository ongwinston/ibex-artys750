add_executable(myprintf
    main.c
    myprintf.c
    test_myprintf.c
)

target_include_directories(myprintf PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../common
    )

target_link_libraries(myprintf common)

####################
# Create .elf file #
####################

add_custom_command(TARGET myprintf POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_BINARY_DIR}/myprintf
    ${CMAKE_CURRENT_BINARY_DIR}/myprintf.elf
)

# Create disassembly file with all sections
add_custom_command(TARGET myprintf POST_BUILD
    COMMAND riscv32-unknown-elf-objdump 
    -D -S -r -x -t ${CMAKE_CURRENT_BINARY_DIR}/myprintf
    > ${CMAKE_CURRENT_BINARY_DIR}/myprintf.dis
)
