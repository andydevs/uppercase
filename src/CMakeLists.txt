include_directories (${Uppercase_SOURCE_DIR}/include)
file(GLOB SRCS *.c)
add_executable(Uppercase ${SRCS})
