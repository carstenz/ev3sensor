/*
 * EV3 Sensor API
 *
 * This file contains code from lmstypes.h of the LEGO MINDSTORMS EV3 project
 * Copyright (C) 2010-2013 The LEGO Group
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/
 */

#ifndef BASICTYPES_H_
#define BASICTYPES_H_

// Some basic data type defines
typedef   unsigned char         UBYTE;  //!< Basic Type used to symbolise 8  bit unsigned values
typedef   unsigned short        UWORD;  //!< Basic Type used to symbolise 16 bit unsigned values
typedef   unsigned int          ULONG;  //!< Basic Type used to symbolise 32 bit unsigned values
typedef   signed short          SWORD;  //!< Basic Type used to symbolise 16 bit signed values
typedef   signed char           SBYTE;  //!< Basic Type used to symbolise 8  bit signed values
typedef   SBYTE                 DATA8;  //!< VM Type for 1 byte signed value
typedef   SWORD                 DATA16; //!< VM Type for 2 byte signed value
typedef   float                 DATAF;  //!< VM Type for 4 byte floating point value

#endif //BASICTYPES_H_