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

#pragma once

#include "build/build.h"


typedef struct {
    // The x-dimension of the tile number.
    short width;

    // The y-dimension of the tile number.
    short height;
} dimensions_t;

typedef struct {
    // The dimension of the tile in texels unit.
    dimensions_t dim;

    // sed to check if a texture is in RAM or in the GRP.
    uint8_t lock;

    // Flag for animating the tile.
    int32_t anim_flags;

    // The wall texture data.
    uint8_t* data;
} tile_t;


extern tile_t tiles[MAXTILES];

void setviewtotile(short tilenume, int32_t tileWidth, int32_t tileHeight);

void squarerotatetile(short tilenume);

void loadtile(short tilenume);

uint8_t* allocatepermanenttile(short tilenume, int32_t width, int32_t height);

int loadpics(char* filename, char* gamedir);

void copytilepiece(
    int32_t tilenume1,
    int32_t sx1,
    int32_t sy1,
    int32_t xsiz,
    int32_t ysiz,
    int32_t tilenume2,
    int32_t sx2,
    int32_t sy2
);


// Bitvector marking picture used for rendition.
extern uint8_t gotpic[(MAXTILES + 7) >> 3];
void setgotpic(int32_t tilenume);


int animateoffs(int16_t tilenum);

extern uint8_t* pic;

void TILE_MakeAvailable(short picID);
