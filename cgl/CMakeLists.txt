set(CGL_SRCS
    src/main.cc)
add_executable(cgl ${CGL_SRCS})

find_package(Curses REQUIRED)

target_link_libraries(cgl
    ${CURSES_LIBRARIES}
)