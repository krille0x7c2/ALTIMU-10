/* 
 * File:   L3GD20H_GYRO.h
 * Author: Christian Bodelsson<bodelsson@gmail.com>
 * Public Key: https://pgp.mit.edu/pks/lookup?op=get&search=0x3DD59D8AB91E4765
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Created on February 17, 2015, 9:21 AM
 */

#ifndef L3GD20H_GYRO_H
#define	L3GD20H_GYRO_H
#ifdef	__cplusplus
extern "C" {
#endif

#define GYRO_WHO_AM_I   0x0F//R 11010111
//Reserved - 10-1F -
#define GYRO_CTRL1   0x20//R/W  00000111
#define GYRO_CTRL2   0x21//R/W
#define GYRO_CTRL3   0x22//R/W
#define GYRO_CTRL4   0x23//R/W
#define GYRO_CTRL5   0x24//R/W

#define GYRO_REFERENCE   0x25//R/W
/*output*/
#define GYRO_OUT_TEMP  0x26 //R
#define GYRO_STATUS  0x27 //R
#define GYRO_OUT_X_L  0x28 //R
#define GYRO_OUT_X_H  0x29 //R
#define GYRO_OUT_Y_L  0x2A //R
#define GYRO_OUT_Y_H  0x2B //R
#define GYRO_OUT_Z_L  0x2C //R
#define GYRO_OUT_Z_H  0x2D //R
/*END*/
#define GYRO_FIFO_CTRL  0x2E //R/W
#define GYRO_FIFO_SRC  0x2F //R
#define GYRO_IG_CFG  0x30 //R/W
#define GYRO_IG_SRC  0x31 //R
#define GYRO_IG_THS_XH  0x32 //R/W
#define GYRO_IG_THS_XL  0x33 //R/W
#define GYRO_IG_THS_YH  0x34 //R/W
#define GYRO_IG_THS_YL  0x35 //R/W
#define GYRO_IG_THS_ZH  0x36 //R/W
#define GYRO_IG_THS_ZL  0x37 //R/W
#define GYRO_IG_DURATION  0x38//R/W
#define GYRO_LOW_ODR  0x39
#define G_GAIN    .00875
#define LOOP_PERIOD .02

typedef struct gyro_data {
    int16_t x;
    int16_t y;
    int16_t z;
} Gyro_raw;

typedef struct gyro_data_dps {
    float x;
    float y;
    float z;
} Gyro_dps;

typedef struct gyro_data_angle {
    float x;
    float y;
    float z;
} Gyro_angle;

extern void init_gyro(void);
extern void sleep_gyro(void);
extern void power_down_gyro(void);
extern void wake_gyro(void);

extern void read_gyro_values(struct gyro_data *_gyro_data);
extern void read_gyro_values_rate_dps(struct gyro_data *gyro_data, struct gyro_data_dps *_gyro_data_dps);
extern void read_gyro_values_angle(struct gyro_data_dps *gyro_data_dps, struct gyro_data_angle *_gyro_data_angle);

#ifdef	__cplusplus
}
#endif

#endif	/* L3GD20H_GYRO_H */

