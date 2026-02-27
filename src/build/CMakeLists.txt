set(LIB build)

list(REMOVE_ITEM LIBS ${LIB})

add_library(${LIB} STATIC
	build.h
	engine.c
	engine.h
	filesystem.c
	filesystem.h
	fixedPoint_math.c
	fixedPoint_math.h
	icon.h
	macos_compat.h
	mathlib.c
	mmulti.c
	mmulti.h
	physics.c
	platform.h
	sdl_util.h
	sprite.c
	tiles.c
	tiles.h
	timer.c
	timer.h
	unix_compat.h
	win32_compat.h
)

target_include_directories(${LIB} PRIVATE ${CMAKE_BINARY_DIR} "../")
target_include_directories(${LIB} PUBLIC "./")
target_link_libraries(${LIB} PRIVATE ${LIBS} ${SDL2_ALL_LIBRARIES})
