set(CGL_SRCS
    src/cell.h
    src/cell.cc
    src/main.cc
    src/world.h)
add_executable(cgl ${CGL_SRCS})

find_package(Curses REQUIRED)

target_link_libraries(cgl
    ${CURSES_LIBRARIES}
)