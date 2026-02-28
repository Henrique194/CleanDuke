/*
 * Copyright (C) 1994-1995 Apogee Software, Ltd.
 * Copyright (C) 1996, 2003 - 3D Realms Entertainment
 * Copyright (C) Henrique Barateli, <henriquejb194@gmail.com>, et al.
 *
 * This file is part of Duke Nukem 3D version 1.5 - Atomic Edition
 *
 * Duke Nukem 3D is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include "com_parser.h"
#include "com_keyword.h"
#include "cmds/com_cmds.h"
#include "com_misc.h"
#include "duke3d.h"


typedef void (*cmd_parser_t)(con_compiler_t* ctx);

static cmd_parser_t parsers[NUM_KEYWORDS] = {
    [CK_DEF_LEVEL_NAME] = COM_DefineLevelName,
    [CK_ACTOR] = COM_Actor,
    [CK_ADD_AMMO] = COM_LexNum2,
    [CK_IF_RND] = COM_IfNum,
    [CK_END_ACTOR] = COM_EndActor,
    [CK_IF_CAN_SEE] = COM_If,
    [CK_IF_HIT_WEAPON] = COM_If,
    [CK_ACTION] = COM_Action,
    [CK_IF_PLAYER_DIST_LT] = COM_IfNum,
    [CK_IF_PLAYER_DIST_GT] = COM_IfNum,
    [CK_ELSE] = COM_Else,
    [CK_STRENGTH] = COM_LexNum,
    [CK_SHOOT] = COM_LexNum,
    [CK_PAL_FROM] = COM_PalFrom,
    [CK_SOUND] = COM_LexNum,
    [CK_STATE] = COM_State,
    [CK_ENDS] = COM_Ends,
    [CK_DEFINE] = COM_Define,
    [CK_COMMENT] = COM_SkipComment,
    [CK_IF_AI] = COM_IfNum,
    [CK_ADD_WEAPON] = COM_LexNum2,
    [CK_AI] = COM_AI,
    [CK_ADD_PLAYER_HEALTH] = COM_LexNum,
    [CK_IF_DEAD] = COM_If,
    [CK_IF_SQUISHED] = COM_If,
    [CK_SIZE_TO] = COM_LexNum2,
    [CK_LEFT_BRACE] = COM_LeftBrace,
    [CK_RIGHT_BRACE] = COM_RightBrace,
    [CK_SPAWN] = COM_LexNum,
    [CK_MOVE] = COM_Move,
    [CK_IF_WAS_WEAPON] = COM_IfNum,
    [CK_IF_ACTION] = COM_IfNum,
    [CK_IF_ACTION_COUNT] = COM_IfNum,
    [CK_DEBRIS] = COM_LexNum2,
    [CK_BLOCK_COMMENT] = COM_SkipBlockComment,
    [CK_SET_SPRITE_STAT] = COM_LexNum,
    [CK_IF_MOVE] = COM_IfNum,
    [CK_IF_ON_WATER] = COM_If,
    [CK_IF_IN_WATER] = COM_If,
    [CK_IF_CAN_SHOOT_TARGET] = COM_If,
    [CK_IF_COUNT] = COM_IfNum,
    [CK_ADD_INVENTORY] = COM_LexNum2,
    [CK_IF_ACTOR_NOT_STAYPUT] = COM_If,
    [CK_HIT_RADIUS] = COM_LexNum5,
    [CK_IF_PLAYER] = COM_IfPlayer,
    [CK_COUNT] = COM_LexNum,
    [CK_IF_ACTOR] = COM_IfNum,
    [CK_MUSIC] = COM_Music,
    [CK_INCLUDE] = COM_Include,
    [CK_IF_STRENGTH] = COM_IfNum,
    [CK_DEFINE_SOUND] = COM_DefineSound,
    [CK_GUTS] = COM_LexNum2,
    [CK_IF_SPAWNED_BY] = COM_IfNum,
    [CK_GAME_STARTUP] = COM_GameStartup,
    [CK_IF_GAP_Z_LT] = COM_IfNum,
    [CK_IF_HIT_SPACE] = COM_If,
    [CK_IF_OUTSIDE] = COM_If,
    [CK_IF_MULTIPLAYER] = COM_If,
    [CK_IF_IN_SPACE] = COM_If,
    [CK_DEBUG] = COM_LexNum,
    [CK_END_OF_GAME] = COM_LexNum,
    [CK_IF_BULLET_NEAR] = COM_If,
    [CK_IF_RESPAWN] = COM_If,
    [CK_IF_FLOOR_DIST_LT] = COM_IfNum,
    [CK_IF_CEILING_DIST_LT] = COM_IfNum,
    [CK_SPRITE_PAL] = COM_LexNum,
    [CK_IF_PLAYER_INVENTORY] = COM_IfPlayerInventory,
    [CK_BETA_NAME] = COM_BetaName,
    [CK_CHANGE_ACTOR] = COM_LexNum,
    [CK_IF_PLAYER_HEALTH_LT] = COM_IfNum,
    [CK_DEFINE_QUOTE] = COM_DefineQuote,
    [CK_QUOTE] = COM_LexNum,
    [CK_IF_IN_OUTER_SPACE] = COM_If,
    [CK_IF_NOT_MOVING] = COM_If,
    [CK_IF_SPRITE_PAL] = COM_IfNum,
    [CK_MONEY] = COM_LexNum,
    [CK_SOUND_ONCE] = COM_LexNum,
    [CK_ADD_KILLS] = COM_LexNum,
    [CK_STOP_SOUND] = COM_LexNum,
    [CK_IF_AWAY_FROM_WALL] = COM_If,
    [CK_IF_CAN_SEE_TARGET] = COM_If,
    [CK_GLOBAL_SOUND] = COM_LexNum,
    [CK_LOTS_OF_GLASS] = COM_LexNum,
    [CK_IF_GOT_WEAPON_ONCE] = COM_IfNum,
    [CK_USER_ACTOR] = COM_UserActor,
    [CK_SIZE_AT] = COM_LexNum2,
    [CK_ADD_STRENGTH] = COM_LexNum,
    [CK_SET_SPRITE_STAT_OR] = COM_LexNum,
    [CK_MAIL] = COM_LexNum,
    [CK_PAPER] = COM_LexNum,
    [CK_SLEEP_TIME] = COM_LexNum,
    [CK_DEFINE_VOL_NAME] = COM_DefineVolName,
    [CK_DEFINE_SKILL_NAME] = COM_DefineSkillName,
    [CK_IF_NO_SOUNDS] = COM_If,
    [CK_CLIP_DIST] = COM_LexNum,
    [CK_IF_ANGLE_DIFF_LT] = COM_IfNum,
};


con_keyword_t COM_ParseCmd(con_compiler_t* ctx) {
    if (ctx->error > 12) {
        // Too many errors, stop compiling.
        return CK_NONE;
    }
    if (ctx->cursor[0] == '\0' || ctx->cursor[1] == '\0') {
        // End of file.
        return CK_NONE;
    }
    con_keyword_t keyword = COM_LexKeyword(ctx);
    if (keyword == CK_NONE) {
        return CK_NONE;
    }
    cmd_parser_t parser = parsers[keyword];
    if (parser) {
        parser(ctx);
    }
    return keyword;
}

void COM_ParseFile(con_compiler_t* ctx) {
    while (true) {
        con_keyword_t keyword = COM_ParseCmd(ctx);
        if (keyword == CK_NONE) {
            break;
        }
    }
    if ((ctx->error + ctx->warning) > 12) {
        printf("  * ERROR! Too many warnings or errors.\n");
    }
    if (ctx->warning > 0 || ctx->error > 0) {
        printf("Found %hhd warning(s), '%c' error(s).\n", ctx->warning, ctx->error);
    }
    ctx->total_lines += ctx->line_number;
    script[0] = CON_EncodeScript(ctx->script_cursor);
}
