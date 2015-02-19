/* 
 * File:   LSM303D_ACC_MAGNETO.h
 * Author: Christian Bodelsson<bodelsson@gmail.com>
 *
 * Created on February 17, 2015, 9:22 AM
 */

#ifndef LSM303D_ACC_MAGNETO_H
#define	LSM303D_ACC_MAGNETO_H
/*Output*/
#define	ACC_MAG_TEMP_OUT_L  0x05//R
#define	ACC_MAG_TEMP_OUT_H  0x06//R
#define	ACC_MAG_STATUS_M  0x07//R
#define	ACC_MAG_OUT_X_L_M  0x08//R
#define	ACC_MAG_OUT_X_H_M  0x09//R
#define	ACC_MAG_OUT_Y_L_M  0x0A//R
#define	ACC_MAG_OUT_Y_H_M  0x0B//R
#define	ACC_MAG_OUT_Z_L_M  0x0C//R
#define	ACC_MAG_OUT_Z_H_M  0x0D//R
/*END*/

//Reserved -- 0E 000 1110 -- Reserved
#define	ACC_MAG_WHO_AM_I  0x0F//R   01001001
//Reserved -- 10-11 -- -- Reserved
#define	ACC_MAG_INT_CTRL_M  0x12//R/W    11101000
#define	ACC_MAG_INT_SRC_M  0x13//R

#define	ACC_MAG_INT_THS_L_M  0x14//R/W
#define	ACC_MAG_INT_THS_H_M  0x15//R/W

#define	ACC_MAG_OFFSET_X_L_M  0x16//R/W
#define	ACC_MAG_OFFSET_X_H_M  0x17//R/W
#define	ACC_MAG_OFFSET_Y_L_M  0x18//R/W
#define	ACC_MAG_OFFSET_Y_H_M  0x19//R/W
#define	ACC_MAG_OFFSET_Z_L_M  0x1A//R/W
#define	ACC_MAG_OFFSET_Z_H_M  0x1B//R/W

#define	ACC_MAG_REFERENCE_X  0x1C//R/W
#define	ACC_MAG_REFERENCE_Y  0x1D//R/W
#define	ACC_MAG_REFERENCE_Z  0x1E//R/W

#define	ACC_MAG_CTRL0  0x1F//R/W
#define	ACC_MAG_CTRL1  0x20//R/W    00000111
#define	ACC_MAG_CTRL2  0x21//R/W
#define	ACC_MAG_CTRL3  0x22//R/W
#define	ACC_MAG_CTRL4  0x23//R/W
#define	ACC_MAG_CTRL5  0x24//R/W    00011000
#define	ACC_MAG_CTRL6  0x25//R/W     00100000
#define	ACC_MAG_CTRL7  0x26//R/W    00000001

#define ACC_MAG_STATUS_A    0x27
/*Output*/
#define ACC_MAG_OUT_X_L_A  0x28//R
#define ACC_MAG_OUT_X_H_A  0x29//R
#define ACC_MAG_OUT_Y_L_A  0x2A//R
#define ACC_MAG_OUT_Y_H_A  0x2B//R
#define ACC_MAG_OUT_Z_L_A  0x2C//R
#define ACC_MAG_OUT_Z_H_A  0x2D//R
/*END*/
#define ACC_MAG_FIFO_CTRL  0x2E//R/W
#define ACC_MAG_FIFO_SRC   0x2F//R

#define ACC_MAG_IG_CFG1    0x30//R/W 
#define ACC_MAG_IG_SRC1    0x31//R 
#define ACC_MAG_IG_THS1    0x32//R/W 
#define ACC_MAG_IG_DUR1    0x33//R/W 
#define ACC_MAG_IG_CFG2    0x34//R/W 
#define ACC_MAG_IG_SRC2    0x35//R 
#define ACC_MAG_IG_THS2    0x36//R/W 
#define ACC_MAG_IG_DUR2    0x37//R/W

#define ACC_MAG_CLICK_CFG  0x38//R/W 
#define ACC_MAG_CLICK_SRC  0x39//R 
#define ACC_MAG_CLICK_THS  0x3A//R/W

#define ACC_MAG_TIME_LIMIT 0x3B//R/W
#define ACC_MAG_TIME _LATENCY 0x3C//R/W
#define ACC_MAG_TIME_WINDOW   0x3D//R/W

#define ACC_MAG_Act_THS 0x3E//R/W
#define ACC_MAG_Act_DUR 0x3F//R/W



typedef struct acc_val_raw {
    int16_t x;
    int16_t y;
    int16_t z;

} Acc_raw;

typedef struct mag_val_raw {
    int16_t x;
    int16_t y;
    int16_t z;

} Mag_raw;

void init_acc(void);
void init_mag(void);
void read_acc_raw(struct acc_val_raw *_acc_raw_);
void read_mag_raw(struct mag_val_raw *_mag_raw_);

#endif	/* LSM303D_ACC_MAGNETO_H */

