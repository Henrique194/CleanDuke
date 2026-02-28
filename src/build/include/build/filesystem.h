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

#include <stdint.h>
#include <stdio.h>

#define MAXGROUPFILES 4 /* Warning: Fix groupfil if this is changed */


extern int32_t groupefil_crc32[MAXGROUPFILES];

int32_t initgroupfile(const char* filename);
void uninitgroupfile(void);
uint16_t crc16(uint8_t* data_p, uint16_t length);
uint32_t crc32_update(const uint8_t* buf, uint32_t length,
                      uint32_t crc_to_update);
int32_t kopen4load(const char* filename, int openOnlyFromGRP);
int32_t kread(int32_t handle, void* buffer, int32_t leng);
int32_t kread8(int32_t handle, uint8_t* buffer);
int32_t kread16(int32_t handle, int16_t* buffer);
int32_t kread32(int32_t handle, int32_t* buffer);
int32_t klseek(int32_t handle, int32_t offset, int whence);
int32_t kfilelength(int32_t handle);
void kclose(int32_t handle);
void kdfread(void* buffer, size_t dasizeof, size_t count, int32_t fil);
void dfread(void* buffer, size_t dasizeof, size_t count, FILE* fil);
void dfwrite(void* buffer, size_t dasizeof, size_t count, FILE* fil);

int getGRPcrc32(int grpID);

const char* getGameDir(void);
void setGameDir(const char* dir);

int32_t TCkopen4load(const char* filename, int32_t readfromGRP);

#if defined(__APPLE__) || defined(__linux__)
int32_t filelength(int32_t fd);
#endif
