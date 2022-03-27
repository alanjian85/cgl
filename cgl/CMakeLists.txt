configure_file(cgl_config.h.in cgl_config.h)

set(CGL_SRCS
    src/cell.cc
    src/cell.h
    src/main.cc
    src/world.cc
    src/world.h
)
add_executable(cgl ${CGL_SRCS})

find_package(Curses REQUIRED)
find_package(fmt REQUIRED)

target_link_libraries(cgl
    ${CURSES_LIBRARIES}
    fmt::fmt
)

target_include_directories(cgl PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CURSES_INCLUDE_DIRS}
)