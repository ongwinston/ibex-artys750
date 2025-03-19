add_executable(lc-romanToInt
    main.c
    romantoint.c
)

target_include_directories(lc-romanToInt PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../../common
    )

target_link_libraries(lc-romanToInt common)

####################
# Create .elf file #
####################

add_custom_command(TARGET lc-romanToInt POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_BINARY_DIR}/lc-romanToInt
    ${CMAKE_CURRENT_BINARY_DIR}/lc-romanToInt.elf
)

# Create disassembly file with all sections
add_custom_command(TARGET lc-romanToInt POST_BUILD
    COMMAND riscv32-unknown-elf-objdump 
    -D -S -r -x -t ${CMAKE_CURRENT_BINARY_DIR}/lc-romanToInt
    > ${CMAKE_CURRENT_BINARY_DIR}/lc-romanToInt.dis
)
