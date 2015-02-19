/* 
 * File:   L3GD20H_GYRO.h
 * Author: Christian Bodelsson<bodelsson@gmail.com>
 *
 * Created on February 17, 2015, 9:21 AM
 */

#ifndef L3GD20H_GYRO_H
#define	L3GD20H_GYRO_H

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

typedef struct gyro_data {
    int16_t x;
    int16_t y;
    int16_t z;
} Val;

typedef struct gyro_data_dps {
    float x;
    float y;
    float z;
} Val_dps;

typedef struct gyro_data_angle {
    float x;
    float y;
    float z;
} Val_angle;


void init_gyro(void);
void read_gyro_values(struct gyro_data *_gyro_data_);
void read_gyro_values_dps(struct gyro_data *_gyro_data_, struct gyro_data_dps *gyro_data_dps);
void read_gyro_values_angle(struct gyro_data_dps *_gyro_data_dps, struct gyro_data_angle *gyro_data_angle);


#endif	/* L3GD20H_GYRO_H */

