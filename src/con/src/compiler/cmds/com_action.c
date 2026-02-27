/*
 * Copyright (C) 1994-1995 Apogee Software, Ltd.
 * Copyright (C) 1996, 2003 - 3D Realms Entertainment
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
#include "com_misc.h"
#include "con/con.h"

void COM_Action(con_compiler_t* ctx) {
    if (ctx->curr_actor || ctx->in_state_block) {
        COM_LexNum(ctx);
        return;
    }

    ctx->script_cursor--;
    const char* str = COM_LexLabel(ctx);

    // Check to see it's already defined.
    if (COM_IsKeyword(str)) {
        COM_Error("Symbol '%s' is a key word.\n", str);
        return;
    }
    if (COM_IsLabel(ctx, str)) {
        COM_Warn("Duplicate action '%s' ignored.\n", str);
    } else {
        ctx->label_code[ctx->label_cnt] = CON_EncodeScript(ctx->script_cursor);
        ctx->label_cnt++;
    }

    i32 i = 0;
    while (i < 5 && COM_PeekKeyword(ctx) < 0) {
        COM_LexNum(ctx);
        i++;
    }
    while (i < 5) {
        *ctx->script_cursor = 0;
        ctx->script_cursor++;
        i++;
    }
}
