/** \file ev3_lcd.h
 * \brief Functions and constants for controlling EV3 LCD
 *
 * ev3_lcd.h contains declarations for the EV3 C API LCD functions.
 *
 * License:
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the
 * License for the specific language governing rights and limitations
 * under the License.
 *
 * The Initial Developer of this code is John Hansen.
 * Portions created by John Hansen are Copyright (C) 2009-2013 John Hansen.
 * All Rights Reserved.
 *
 * ----------------------------------------------------------------------------
 *
 * \author John Hansen (bricxcc_at_comcast.net)
 * \date 2013-08-04
 * \version 1
 *
 * ----------------------------------------------------------------------------
 *
 * \author Ahmand Fatoum & Simón Rodriguez Perez(Hochschule Aschaffenburg)
 * \date 2015-02-28
 * \version 2
 * \note printf function added
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ev3_lcd_h
#define ev3_lcd_h

/* Print Text with Variables - Ahmad Fatoum*/

#ifdef __GNUC__
#pragma GCC system_header
#endif

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>
#include <libgen.h>

#include "../include/ev3_constants.h"

#define LCD_BYTE_WIDTH ((LCD_WIDTH + 7) / 8)
#define LCD_BUFFER_SIZE (LCD_BYTE_WIDTH * LCD_HEIGHT)

typedef uint8_t  IMGDATA;    //!< Image base type
typedef IMGDATA* IP;         //!< Instruction pointer type

typedef struct {
	int X;  /*!< The X coordinate. Valid range is from 0 to 177 inclusive.  */
	int Y;  /*!< The Y coordinate. Valid range is from 0 to 127 inclusive. */
} LocationType;

typedef LocationType* PLocationType;

typedef enum {
	ifRAW_FB0,
	ifRAW_BUF,
	ifXBM,
	ifP1,
	ifP4,
	ifBMP,
	ifPNG
} ImageFormat;

bool LcdInit();
bool LcdExit();
bool LcdInitialized();

void LcdSetAutoRefresh(bool bOn);
bool LcdUpdate();
bool LcdClean();
bool LcdScroll(short Y);


bool LcdSelectFont(uint8_t FontType);
uint8_t* LcdGetDisplay();
bool LcdText(char Color, short X, short Y, char* Text);
bool LcdIcon(char Color, short X, short Y, char IconType, char IconNum);
bool LcdBmpFile(char Color, short X, short Y, char* Name);
bool LcdPicture(char Color, short X, short Y, IP pBitmap);
bool LcdFillWindow(char Color, short Y, short Y1);
uint8_t* LcdGetFrameBuffer();
void LcdWriteDisplayToFile(char* filename, ImageFormat fmt);
void LcdWriteFrameBufferToFile(char* filename, ImageFormat fmt);

/**
 * Draw a circle.
 * This function lets you draw a circle on the screen with its center at the
 * specified x and y location, using the specified radius. Optionally specify
 * drawing options. If this argument is not specified it defaults to \ref DRAW_OPT_NORMAL.
 * Valid display option constants are listed in the \ref DisplayDrawOptionConstants group.
 * \sa SysDrawCircle, DrawCircleType
 *
 * \param x The x value for the center of the circle.
 * \param y The y value for the center of the circle.
 * \param radius The radius of the circle.
 * \param options The drawing options.
 * \return The result of the drawing operation.
 */
char CircleOutEx(int x, int y, uint8_t radius, unsigned long options);
#define CircleOut(_x, _y, _r) CircleOutEx((_x), (_y), (_r), DRAW_OPT_NORMAL)

/**
 * Draw a line.
 * This function lets you draw a line on the screen from x1, y1 to x2, y2.
 * Optionally specify drawing options. If this argument is not specified it
 * defaults to \ref DRAW_OPT_NORMAL. Valid display option constants are listed in
 * the \ref DisplayDrawOptionConstants group.
 * \sa SysDrawLine, DrawLineType
 *
 * \param x1 The x value for the start of the line.
 * \param y1 The y value for the start of the line.
 * \param x2 The x value for the end of the line.
 * \param y2 The y value for the end of the line.
 * \param options The drawing options.
 * \return The result of the drawing operation.
 */
char LineOutEx(int x1, int y1, int x2, int y2, unsigned long options);
#define LineOut(_x1, _y1, _x2, _y2) LineOutEx((_x1), (_y1), (_x2), (_y2), DRAW_OPT_NORMAL)

/**
 * Draw a point.
 * This function lets you draw a point on the screen at x, y.
 * Optionally specify drawing options. If this argument is not specified it
 * defaults to \ref DRAW_OPT_NORMAL. Valid display option constants are listed in
 * the \ref DisplayDrawOptionConstants group.
 * \sa SysDrawPoint, DrawPointType
 *
 * \param x The x value for the point.
 * \param y The y value for the point.
 * \param options The drawing options.
 * \return The result of the drawing operation.
 */
char PointOutEx(int x, int y, unsigned long options);
#define PointOut(_x, _y) PointOutEx((_x), (_y), DRAW_OPT_NORMAL)

/**
 * Draw a rectangle.
 * This function lets you draw a rectangle on the screen at x, y with the
 * specified width and height.
 * Optionally specify drawing options. If this argument is not specified it
 * defaults to \ref DRAW_OPT_NORMAL. Valid display option constants are listed in
 * the \ref DisplayDrawOptionConstants group.
 * \sa SysDrawRect, DrawRectType
 *
 * \param x The x value for the top left corner of the rectangle.
 * \param y The y value for the top left corner of the rectangle.
 * \param width The width of the rectangle.
 * \param height The height of the rectangle.
 * \param options The drawing options.
 * \return The result of the drawing operation.
 */
char RectOutEx(int x, int y, int width, int height, unsigned long options);
#define RectOut(_x, _y, _w, _h) RectOutEx((_x), (_y), (_w), (_h), DRAW_OPT_NORMAL)


/**
 * Draw an ellipse.
 * This function lets you draw an ellipse on the screen with its center at the
 * specified x and y location, using the specified radii. Optionally specify
 * drawing options. If this argument is not specified it defaults to \ref DRAW_OPT_NORMAL.
 * Valid display option constants are listed in the \ref DisplayDrawOptionConstants group.
 * \sa SysDrawEllipse, DrawEllipseType
 *
 * \warning This function requires the enhanced NBC/NXC firmware version 1.28+.
 *
 * \param x The x value for the center of the ellipse.
 * \param y The y value for the center of the ellipse.
 * \param radiusX The x axis radius.
 * \param radiusY The y axis radius.
 * \param options The drawing options.
 * \return The result of the drawing operation.
 */
char EllipseOutEx(int x, int y, uint8_t radiusX, uint8_t radiusY, unsigned long options);
#define EllipseOut(_x, _y, _rx, _ry) EllipseOutEx((_x), (_y), (_rx), (_ry), DRAW_OPT_NORMAL)


bool LcdTextf(char Color, short X, short Y, const char *fmt, ...);


int LcdPrintf(char color, const char * fmt, ...);

int LcdPrintln(char color, const char * fmt, ...);


#ifdef __ASPRINTF
#include <stdarg.h>
int asprintf(char **, const char *, ...);
int vasprintf(char **, const char *, va_list)
#endif


#define LCD_COLOR_BLACK 1
#define LCD_COLOR_WHITE 0

short LcdRowToY(int row);

int Ev3Printf(const char *fmt, ...);

/**
 * Print formatted text on the display with a new line at the end.
 * Works like the normal printf but appends a linefeed at the end.
 */
int Ev3Println(const char *fmt, ...);

/**
 * Clear the display and reset the cursor to the top left corner.
 */
void Ev3Clear();

/**
 * Analog to Ev3Printf but automatically scrolls upwards to prevent 
 * text from being out of bounds.
 */
int TermPrintf(const char *fmt, ...);

/**
 * Analog to Ev3Printf but automatically scrolls upwards to prevent 
 * text from being out of bounds.
 */
int TermPrintln(const char *fmt, ...);

/**
 * Set cursor position for TermPrint*, LcdPrint* and Ev3Print*
 * @param x
 */
void SetCursorX(short x);

/**
 * Set cursor position for TermPrint*, LcdPrint* and Ev3Print*
 * @param y
 */
void SetCursorY(short y);

#endif // ev3_lcd_h

#ifdef __cplusplus
}
#endif
