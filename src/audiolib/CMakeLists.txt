set(LIB audiolib)

list(REMOVE_ITEM LIBS ${LIB})

# Source contains loads of files that are not used (only DOS). Delete them?
add_library(${LIB} STATIC
	dpmi.c
	dsl.c
	fx_man.c
	ll_man.c
	multivoc.c
	mv_mix.c
	mvreverb.c
	pitch.c
	sdl_midi.c
	sounds.c
)

target_include_directories(${LIB} PRIVATE ${CMAKE_BINARY_DIR} "../")
target_include_directories(${LIB} PUBLIC "./include")
target_link_libraries(${LIB} PRIVATE ${LIBS} ${SDL2_ALL_LIBRARIES})
