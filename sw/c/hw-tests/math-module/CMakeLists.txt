add_executable(math-module
    main.c
)

target_include_directories(math-module PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../../common
    )

target_link_libraries(math-module common)

####################
# Create .elf file #
####################

add_custom_command(TARGET math-module POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_BINARY_DIR}/math-module
    ${CMAKE_CURRENT_BINARY_DIR}/math-module.elf
)

# Create disassembly file with all sections
add_custom_command(TARGET math-module POST_BUILD
    COMMAND riscv32-unknown-elf-objdump 
    -D -S -r -x -t ${CMAKE_CURRENT_BINARY_DIR}/math-module
    > ${CMAKE_CURRENT_BINARY_DIR}/math-module.dis
)
