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
#include "com_keyword.h"
#include "com_label.h"
#include "con/con.h"

void COM_State(con_compiler_t* ctx) {
    if (!ctx->curr_actor && !ctx->in_state_block) {
        COM_LexLabel(ctx);
        ctx->script_cursor--;
        ctx->label_code[ctx->label_cnt] = CON_EncodeScript(ctx->script_cursor);
        ctx->label_cnt++;
        ctx->in_state_block = 1;
        return;
    }
    const char* str = COM_LexLabel(ctx);
    if (COM_IsKeyword(str)) {
        COM_Error("Symbol '%s' is a key word.\n", str);
        return;
    }
    const int code = COM_GetLabel(ctx, str);
    if (code >= 0) {
        *ctx->script_cursor = ctx->label_code[code];
    } else {
        COM_Error("State '%s' not found.\n", str);
    }
    ctx->script_cursor++;
}

void COM_Ends(con_compiler_t* ctx) {
    if (ctx->in_state_block == 0) {
        COM_Error("Found 'ends' with no 'state'.\n");
    }
    if (ctx->brace_depth > 0) {
        COM_Error("Found more '{' than '}' before 'ends'.\n");
    }
    if (ctx->brace_depth < 0) {
        COM_Error("Found more '}' than '{' before 'ends'.\n");
    }
    ctx->in_state_block = 0;
}
