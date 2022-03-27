set(CGL_SRCS
    src/cell.cc
    src/cell.h
    src/main.cc
    src/world.cc
    src/world.h
)
add_executable(cgl ${CGL_SRCS})

find_package(Curses REQUIRED)

target_link_libraries(cgl
    ${CURSES_LIBRARIES}
)