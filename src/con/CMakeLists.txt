set(LIB con)

list(REMOVE_ITEM LIBS ${LIB})

set(COMPILER_SRC
    src/compiler/cmds/com_action.c
    src/compiler/cmds/com_actor.c
    src/compiler/cmds/com_ai.c
    src/compiler/cmds/com_betaname.c
    src/compiler/cmds/com_braces.c
    src/compiler/cmds/com_cmds.h
    src/compiler/cmds/com_comment.c
    src/compiler/cmds/com_define.c
    src/compiler/cmds/com_gamestartup.c
    src/compiler/cmds/com_if.c
    src/compiler/cmds/com_include.c
    src/compiler/cmds/com_move.c
    src/compiler/cmds/com_music.c
    src/compiler/cmds/com_palfrom.c
    src/compiler/cmds/com_state.c
    src/compiler/com_main.c
    src/compiler/com_main.h
    src/compiler/com_keyword.c
    src/compiler/com_keyword.h
    src/compiler/com_label.c
    src/compiler/com_label.h
    src/compiler/com_misc.c
    src/compiler/com_misc.h
    src/compiler/com_parser.c
    src/compiler/com_parser.h
)

set(VM_SRC
    src/vm/ops/vm_action.c
    src/vm/ops/vm_actor.c
    src/vm/ops/vm_ai.c
    src/vm/ops/vm_braces.c
    src/vm/ops/vm_count.c
    src/vm/ops/vm_cstat.c
    src/vm/ops/vm_debris.c
    src/vm/ops/vm_debug.c
    src/vm/ops/vm_dist.c
    src/vm/ops/vm_endofgame.c
    src/vm/ops/vm_fall.c
    src/vm/ops/vm_glass.c
    src/vm/ops/vm_guts.c
    src/vm/ops/vm_hit_radius.c
    src/vm/ops/vm_if_plr.c
    src/vm/ops/vm_if.c
    src/vm/ops/vm_ifcansee.c
    src/vm/ops/vm_inventory.c
    src/vm/ops/vm_kill.c
    src/vm/ops/vm_mail.c
    src/vm/ops/vm_money.c
    src/vm/ops/vm_move.c
    src/vm/ops/vm_nullop.c
    src/vm/ops/vm_operate.c
    src/vm/ops/vm_pal.c
    src/vm/ops/vm_paper.c
    src/vm/ops/vm_plr_health.c
    src/vm/ops/vm_plr_kick.c
    src/vm/ops/vm_plr_stomp.c
    src/vm/ops/vm_quote.c
    src/vm/ops/vm_reset_plr.c
    src/vm/ops/vm_shoot.c
    src/vm/ops/vm_size.c
    src/vm/ops/vm_sleeptime.c
    src/vm/ops/vm_sound.c
    src/vm/ops/vm_spawn.c
    src/vm/ops/vm_state.c
    src/vm/ops/vm_strength.c
    src/vm/ops/vm_target.c
    src/vm/ops/vm_tip.c
    src/vm/ops/vm_wack_plr.c
    src/vm/ops/vm_water.c
    src/vm/ops/vm_weapon.c
    src/vm/ops/vm_ops.h
    src/vm/vm_dodge.c
    src/vm/vm_main.c
    src/vm/vm_main.h
    src/vm/vm_move.c
    src/vm/vm_op.c
)

add_library(${LIB} STATIC ${COMPILER_SRC} ${VM_SRC})

target_include_directories(${LIB}
    PRIVATE
        ${CMAKE_BINARY_DIR}
        "../"
        "src/compiler"
        "src/vm"
    PUBLIC
        "include/"
)
target_link_libraries(${LIB} PRIVATE ${LIBS} ${SDL2_ALL_LIBRARIES})
