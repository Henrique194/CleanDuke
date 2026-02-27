set(LIB menu)

list(REMOVE_ITEM LIBS ${LIB})

add_library(${LIB} STATIC
	animlib.c
	animlib.h
	menu.c
)

target_include_directories(${LIB} PRIVATE ${CMAKE_BINARY_DIR} "../")
target_include_directories(${LIB} PUBLIC "./include")
target_link_libraries(${LIB} PRIVATE ${LIBS} ${SDL2_ALL_LIBRARIES})
