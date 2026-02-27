set(LIB hud)

list(REMOVE_ITEM LIBS ${LIB})

add_library(${LIB} STATIC
    src/hu_draw.c
    src/hu_draw.h
    src/hu_main.c
    src/hu_statusbar.c
    src/hu_text.c
    src/hu_text.h
)

target_include_directories(${LIB} PRIVATE ${CMAKE_BINARY_DIR} "../")
target_include_directories(${LIB} PUBLIC "./include")
target_link_libraries(${LIB} PRIVATE ${LIBS} ${SDL2_ALL_LIBRARIES})
