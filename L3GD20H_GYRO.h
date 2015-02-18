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

typedef struct valstruct {
    uint8_t x;
    uint8_t y;
    uint8_t z;
}Val;


void init_gyro(void);
struct valstruct read_gyro_values(void);


#endif	/* L3GD20H_GYRO_H */

