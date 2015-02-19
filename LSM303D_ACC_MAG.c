/* 
 * File:   LSM303D_ACC_MAGNETO.c
 * Author: Christian Bodelsson<bodelsson@gmail.com>
 *
 * Created on February 17, 2015, 8:46 AM
 */
//TODO Write documentation and implement
#include <avr/io.h>
#include "ALTIMU_10.h"
#include "LSM303D_ACC_MAG.h"
#include "twi_master.h"
#include <math.h>

/*************************************************************************
 * Initialize acc
 * (+/- 2 g full scale)
 * (50 Hz ODR); AZEN = AYEN = AXEN = 1 (all axes enabled)
 
 *************************************************************************/
void init_acc(void) {
    write_to_reg(ACC_MAG_SLAVE_ADDRESS, ACC_MAG_CTRL2, 0x00);
    write_to_reg(ACC_MAG_SLAVE_ADDRESS, ACC_MAG_CTRL1, 0x57);

}/*init_acc*/

/*************************************************************************
 * Initialize mag
 * (high resolution mode); M_ODR = 001 (6.25 Hz ODR)
 * (+/- 4 gauss full scale)
 * (low power mode off); MD = 00 (continuous-conversion mode)
 
 *************************************************************************/

void init_mag(void) {
    write_to_reg(ACC_MAG_SLAVE_ADDRESS, ACC_MAG_CTRL5, 0x64);
    write_to_reg(ACC_MAG_SLAVE_ADDRESS, ACC_MAG_CTRL6, 0x20);
    write_to_reg(ACC_MAG_SLAVE_ADDRESS, ACC_MAG_CTRL7, 0x00);
}/*init_mag*/

/*************************************************************************
 * read_acc_raw values
 
 *************************************************************************/

void read_acc_raw(struct acc_val_raw *_acc_raw_) {
    if (i2c_start(ACC_MAG_SLAVE_ADDRESS << 1) == 0) {
        i2c_write(ACC_MAG_OUT_X_L_A | (1 << 7)); //Auto increment registers by writing the MSB high

        if (i2c_rep_start(((uint8_t) ACC_MAG_SLAVE_ADDRESS << 1) | 1) == 0) {
            uint8_t xlg = i2c_read(ACK);
            uint8_t xhg = i2c_read(ACK);

            uint8_t ylg = i2c_read(ACK);
            uint8_t yhg = i2c_read(ACK);

            uint8_t zlg = i2c_read(ACK);
            uint8_t zhg = i2c_read(NAK);

            _acc_raw_->x = (int16_t) (xhg << 8 | xlg);
            _acc_raw_->y = (int16_t) (yhg << 8 | ylg);
            _acc_raw_->z = (int16_t) (zhg << 8 | zlg);

        }
    }

}/*read_acc_raw*/

/*************************************************************************
 * read_acc_angles values
 * 
 
 *************************************************************************/
void read_acc_angel(struct acc_val_raw *_acc_raw_, struct acc_val_angle *_acc_angle) {
    _acc_angle->x = (float) (atan2(_acc_raw_->y, _acc_raw_->z) + M_PI) * RAD_TO_DEG;
    _acc_angle->y = (float) (atan2(_acc_raw_->z, _acc_raw_->x) + M_PI) * RAD_TO_DEG;
    
    _acc_angle->x -= (float) 180.0;
    if (_acc_angle->y > 90) {
        _acc_angle->y -= (float) 270;
    } else {
        _acc_angle->y += (float) 90;
    }


}/*read_acc_angle*/

/*************************************************************************
 * read_mag_raw values
 * 
 
 *************************************************************************/

void read_mag_raw(struct mag_val_raw *_mag_raw_) {
    if (i2c_start(ACC_MAG_SLAVE_ADDRESS << 1) == 0) {
        i2c_write(ACC_MAG_OUT_X_L_M | (1 << 7)); //Auto increment registers by writing the MSB high

        if (i2c_rep_start(((uint8_t) ACC_MAG_SLAVE_ADDRESS << 1) | 1) == 0) {
            uint8_t xlm = i2c_read(ACK);
            uint8_t xhm = i2c_read(ACK);

            uint8_t ylm = i2c_read(ACK);
            uint8_t yhm = i2c_read(ACK);

            uint8_t zlm = i2c_read(ACK);
            uint8_t zhm = i2c_read(NAK);

            _mag_raw_->x = (int16_t) (xhm << 8 | xlm);
            _mag_raw_->y = (int16_t) (yhm << 8 | ylm);
            _mag_raw_->z = (int16_t) (zhm << 8 | zlm);

        }
    }

}/*read_mag_raw*/