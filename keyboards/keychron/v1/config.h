/* Copyright 2021 @ Keychron(https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

/* key matrix pins */
#define MATRIX_ROW_PINS \
    { B5, B4, B3, A15, A14, A13 }
#define MATRIX_COL_PINS \
    { C14, C15, A0, A1, A2, A3, A4, A5, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* RGB Matrix Driver Configuration */
#define SNLED27351_I2C_ADDRESS_1 SNLED27351_I2C_ADDRESS_VDDIO
#define SNLED27351_I2C_ADDRESS_2 SNLED27351_I2C_ADDRESS_GND

/* Increase I2C speed to 1000 KHz */
#define I2C1_TIMINGR_PRESC 0U
#define I2C1_TIMINGR_SCLDEL 3U
#define I2C1_TIMINGR_SDADEL 0U
#define I2C1_TIMINGR_SCLH 15U
#define I2C1_TIMINGR_SCLL 51U

#define SNLED27351_PHASE_CHANNEL SNLED27351_SCAN_PHASE_9_CHANNEL

#define MOUSEKEY_DELAY 0            // 300 移動キーを押してからカーソルが移動するまでの遅延
#define MOUSEKEY_INTERVAL 0          // 50 カーソル移動間の時間
#define MOUSEKEY_MAX_SPEED 0         // 10 加速が停止する最大のカーソル速度
#define MOUSEKEY_TIME_TO_MAX 0       // 20 最大カーソル速度に達するまでの時間
#define MOUSEKEY_WHEEL_DELAY 0      // 300 ホイールキーを押してからホイールが動くまでの遅延
#define MOUSEKEY_WHEEL_INTERVAL 0   // 100 ホイールの動きの間の時間
#define MOUSEKEY_WHEEL_MAX_SPEED 2    // 8 スクロールアクションごとのスクロールステップの最大数
#define MOUSEKEY_WHEEL_TIME_TO_MAX 0 // 40 最大スクロール速度に達するまでの時間

#define MK_3_SPEED
#define MK_MOMENTARY_ACCEL

#define MK_C_INTERVAL_0 1 // 16
#define MK_C_INTERVAL_1 16 // 16
#define MK_C_INTERVAL_2 15 // 16

#define MK_W_INTERVAL_0 200 // 360
#define MK_W_INTERVAL_1 80 // 120
#define MK_W_INTERVAL_2 20 // 20
