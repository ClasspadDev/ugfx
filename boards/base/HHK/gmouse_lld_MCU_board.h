/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#ifndef _LLD_GMOUSE_MCU_BOARD_H
#define _LLD_GMOUSE_MCU_BOARD_H

#ifndef GINPUT_TOUCH_NOCALIBRATE
    #define GINPUT_TOUCH_NOCALIBRATE GFXON
#endif

#include <string.h>
#include <sdk/calc/calc.h>
#include <sdk/os/input.h>

// Resolution and Accuracy Settings
#define GMOUSE_MCU_PEN_CALIBRATE_ERROR		1
#define GMOUSE_MCU_PEN_CLICK_ERROR			0
#define GMOUSE_MCU_PEN_MOVE_ERROR			0
#define GMOUSE_MCU_FINGER_CALIBRATE_ERROR	3
#define GMOUSE_MCU_FINGER_CLICK_ERROR		5
#define GMOUSE_MCU_FINGER_MOVE_ERROR		3
#define GMOUSE_MCU_Z_MIN					0			// The minimum Z reading
#define GMOUSE_MCU_Z_MAX					1			// The maximum Z reading
#define GMOUSE_MCU_Z_TOUCHON				1			// Values between this and Z_MAX are definitely pressed
#define GMOUSE_MCU_Z_TOUCHOFF				0			// Values between this and Z_MIN are definitely not pressed

#undef GMOUSE_VFLG_POORUPDOWN
#define GMOUSE_VFLG_POORUPDOWN 0
#undef GMOUSE_VFLG_ONLY_DOWN
#define GMOUSE_VFLG_ONLY_DOWN 0

// How much extra data to allocate at the end of the GMouse structure for the board's use
#define GMOUSE_MCU_BOARD_DATA_SIZE			0

static gBool init_board(GMouse *m, unsigned driverinstance) {
    (void)m;
    (void)driverinstance;
    return gTrue;
}

static gCoord x, y, z = 0;

static gBool read_xyz(GMouse *m, GMouseReading *prd) {
    (void)m;
    struct Input_Event event;
    memset(&event, 0, sizeof(event));
    GetInput(&event, 0xFFFFFFFF, 0x10);
    if (event.type == EVENT_TOUCH) {
        z = (event.data.touch_single.direction & (TOUCH_DOWN | TOUCH_HOLD_DRAG)) != 0 ? 1 : 0;
        x = event.data.touch_single.p1_x;
        y = event.data.touch_single.p1_y;
    }
    prd->x = x;
    prd->z = z;
    prd->y = y;
    return gTrue;
}

#endif /* _LLD_GMOUSE_MCU_BOARD_H */
