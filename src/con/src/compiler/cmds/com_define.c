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

#include "com_cmds.h"
#include "com_misc.h"
#include "com_keyword.h"
#include "com_label.h"
#include "funct.h"
#include "types.h"

void COM_Define(con_compiler_t* ctx) {
    const char* str = COM_LexLabel(ctx);
    if (COM_IsKeyword(str)) {
        COM_Error("Symbol '%s' is a key word.\n", str);
        return;
    }
    COM_LexNum(ctx);
    if (COM_IsLabel(ctx, str)) {
        COM_Warn("Duplicate definition '%s' ignored.\n", str);
    } else {
        ctx->label_code[ctx->label_cnt] = *(ctx->script_cursor - 1);
        ctx->label_cnt++;
    }
    ctx->script_cursor -= 2;
}

void COM_DefineSound(con_compiler_t* ctx) {
    ctx->script_cursor--;
    COM_LexNum(ctx);
    i32 k = *(ctx->script_cursor - 1);
    if (k >= NUM_SOUNDS) {
        COM_Error("Exceeded sound limit of %d.\n", NUM_SOUNDS);
    }
    ctx->script_cursor--;

    i32 i = 0;
    while (*ctx->cursor == ' ') {
        ctx->cursor++;
    }

    while (*ctx->cursor != ' ') {
        sounds[k][i] = *ctx->cursor;
        ctx->cursor++;
        i++;
        if (i >= 13) {
            puts(sounds[k]);
            COM_Error("Sound filename exceeded limit of 13 characters.\n");
            while (*ctx->cursor != ' ')
                ctx->cursor++;
            break;
        }
    }
    sounds[k][i] = '\0';

    COM_LexNum(ctx);
    soundps[k] = *(ctx->script_cursor - 1);
    ctx->script_cursor--;

    COM_LexNum(ctx);
    soundpe[k] = *(ctx->script_cursor - 1);
    ctx->script_cursor--;

    COM_LexNum(ctx);
    soundpr[k] = *(ctx->script_cursor - 1);
    ctx->script_cursor--;

    COM_LexNum(ctx);
    soundm[k] = *(ctx->script_cursor - 1);
    ctx->script_cursor--;

    COM_LexNum(ctx);
    soundvo[k] = *(ctx->script_cursor - 1);
    ctx->script_cursor--;
}

void COM_DefineQuote(con_compiler_t* ctx) {
    ctx->script_cursor--;
    COM_LexNum(ctx);
    i32 k = *(ctx->script_cursor - 1);
    if (k >= NUMOFFIRSTTIMEACTIVE) {
        COM_Error("Quote amount exceeds limit of %d characters.\n", NUMOFFIRSTTIMEACTIVE);
    }
    ctx->script_cursor--;

    i32 i = 0;
    while (*ctx->cursor == ' ') {
        ctx->cursor++;
    }

    while (*ctx->cursor != '\n') {
        fta_quotes[k][i] = *ctx->cursor;
        ctx->cursor++;
        i++;
        if (i >= 64) {
            COM_Error("Quote exceeds character size limit of 64.\n");
            while (*ctx->cursor != '\n')
                ctx->cursor++;
            break;
        }
    }
    fta_quotes[k][i] = '\0';
}

void COM_DefineLevelName(con_compiler_t* ctx) {
    ctx->script_cursor--;
    COM_LexNum(ctx);
    ctx->script_cursor--;
    i32 j = *ctx->script_cursor;
    COM_LexNum(ctx);
    ctx->script_cursor--;
    i32 k = *ctx->script_cursor;
    while (*ctx->cursor == ' ') {
        ctx->cursor++;
    }

    i32 i = 0;
    while (*ctx->cursor != ' ' && *ctx->cursor != '\n') {
        level_file_names[j * 11 + k][i] = *ctx->cursor;
        ctx->cursor++;
        i++;
        if (i > 127) {
            COM_Error("Level file name exceeds character size limit of 128.\n");
            while (*ctx->cursor != ' ')
                ctx->cursor++;
            break;
        }
    }
#ifdef UNIX
    level_names[j * 11 + k][i] = '\0';
#else
    level_names[j * 11 + k][i - 1] = '\0';
#endif

    while (*ctx->cursor == ' ') {
        ctx->cursor++;
    }

    partime[j * 11 + k] =
        (((*(ctx->cursor + 0) - '0') * 10 + (*(ctx->cursor + 1) - '0')) * 26 * 60)
        + (((*(ctx->cursor + 3) - '0') * 10 + (*(ctx->cursor + 4) - '0')) * 26);

    ctx->cursor += 5;
    while (*ctx->cursor == ' ') {
        ctx->cursor++;
    }

    designertime[j * 11 + k] =
        (((*(ctx->cursor + 0) - '0') * 10 + (*(ctx->cursor + 1) - '0')) * 26 * 60)
        + (((*(ctx->cursor + 3) - '0') * 10 + (*(ctx->cursor + 4) - '0')) * 26);

    ctx->cursor += 5;
    while (*ctx->cursor == ' ') {
        ctx->cursor++;
    }

    i = 0;

    while (*ctx->cursor != '\n') {
        level_names[j * 11 + k][i] = toupper(*ctx->cursor);
        ctx->cursor++;
        i++;
        if (i >= 32) {
            COM_Error("Level name exceeds character size limit of 32.\n");
            while (*ctx->cursor != '\n')
                ctx->cursor++;
            break;
        }
    }
#ifdef UNIX
    level_names[j * 11 + k][i] = '\0';
#else
    level_names[j * 11 + k][i - 1] = '\0';
#endif
}

void COM_DefineSkillName(con_compiler_t* ctx) {
    ctx->script_cursor--;
    COM_LexNum(ctx);
    ctx->script_cursor--;

    i32 j = *ctx->script_cursor;
    while (*ctx->cursor == ' ') {
        ctx->cursor++;
    }

    i32 i = 0;
    while (*ctx->cursor != '\n') {
        skill_names[j][i] = toupper(*ctx->cursor);
        ctx->cursor++;
        i++;
        if (i >= 32) {
            COM_Error("Skill name exceeds character size limit of 32.\n");
            while (*ctx->cursor != '\n')
                ctx->cursor++;
            break;
        }
    }
#ifdef UNIX
    skill_names[j][i] = '\0';
#else
    skill_names[j][i - 1] = '\0';
#endif
}

void COM_DefineVolName(con_compiler_t* ctx) {
    ctx->script_cursor--;
    COM_LexNum(ctx);
    ctx->script_cursor--;

    i32 j = *ctx->script_cursor;
    while (*ctx->cursor == ' ') {
        ctx->cursor++;
    }

    i32 i = 0;
    while (*ctx->cursor != '\n') {
        volume_names[j][i] = toupper(*ctx->cursor);
        ctx->cursor++;
        i++;
        if (i >= 32) {
            COM_Error("Volume name exceeds character size limit of 32.\n");
            while (*ctx->cursor != '\n') {
                ctx->cursor++;
            }
            break;
        }
    }
#ifdef UNIX
    volume_names[j][i] = '\0';
#else
    volume_names[j][i - 1] = '\0';
#endif
}
