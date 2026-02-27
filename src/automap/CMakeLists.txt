set(LIB automap)

list(REMOVE_ITEM LIBS ${LIB})

add_library(${LIB} STATIC
    src/am_main.c
    src/am_overhead.c
    src/am_overhead.h
    src/am_view.c
    src/am_view.h
)

target_include_directories(${LIB} PRIVATE ${CMAKE_BINARY_DIR} "../")
target_include_directories(${LIB} PUBLIC "./include")
target_link_libraries(${LIB} PRIVATE ${LIBS} ${SDL2_ALL_LIBRARIES})
