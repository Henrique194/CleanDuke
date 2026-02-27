set(LIB renderer)

list(REMOVE_ITEM LIBS ${LIB})

add_library(${LIB} STATIC
    src/r_draw.c
    src/r_main.c
    src/r_mirror.c
    src/r_sprite.c
    src/r_wall.c
)

target_include_directories(${LIB} PRIVATE ${CMAKE_BINARY_DIR} "../")
target_include_directories(${LIB} PUBLIC "./include")
target_link_libraries(${LIB} PRIVATE ${LIBS} ${SDL2_ALL_LIBRARIES})
