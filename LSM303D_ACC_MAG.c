/* 
 * File:   LSM303D_ACC_MAGNETO.c
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
 * Created on February 17, 2015, 8:46 AM
 */
//TODO enable power saving functions
#include <avr/io.h>
#include "ALTIMU_10.h"
#include "LSM303D_ACC_MAG.h"
#include "twi_master.h"
#include <math.h>


/*********************************************************************//**
 *Description: Power down the acc 1uA
 *AODR3 AODR2 AODR1 AODR0 = 0000 = power down
 *PD=0 = power down
 * 
 *Input:
 * 
 *Return:
 * 
 *Author: Christian Bodelsson<bodelsson@gmail.com>
 *************************************************************************/
void power_down_acc(void){
    write_to_reg(ACC_MAG_SLAVE_ADDRESS, ACC_MAG_CTRL1, 0x00);
}/*power_down_acc*/

/*********************************************************************//**
 *Description: Power down the mag 1uA
 *MD1 MD0 10 or 11 = power down
 * 
 *Input:
 * 
 *Return:
 * 
 *Author: Christian Bodelsson<bodelsson@gmail.com>
 *************************************************************************/
void power_down_mag(void){
    write_to_reg(ACC_MAG_SLAVE_ADDRESS, ACC_MAG_CTRL7, 0x02);
}/*power_down_mag*/

/*********************************************************************//**
 *Description: Initialize acc 300uA
 * (+/- 2 g full scale)
 * (50 Hz ODR); AZEN = AYEN = AXEN = 1 (all axes enabled)
 * 
 *Input:
 * 
 *Return:
 * 
 *Author: Christian Bodelsson<bodelsson@gmail.com>
 *************************************************************************/
void init_acc(void) {
    
    write_to_reg(ACC_MAG_SLAVE_ADDRESS, ACC_MAG_CTRL2, 0x00);
    write_to_reg(ACC_MAG_SLAVE_ADDRESS, ACC_MAG_CTRL1, 0x57);

}/*init_acc*/

/*********************************************************************//**
 *Description: Initialize mag
 * (high resolution mode); M_ODR = 001 (6.25 Hz ODR)
 * (+/- 4 gauss full scale)
 * (low power mode off); MD = 00 (continuous-conversion mode)
 * 
 *Input:
 * 
 *Return:
 * 
 *Author: Christian Bodelsson<bodelsson@gmail.com>
 *************************************************************************/

void init_mag(void) {

    write_to_reg(ACC_MAG_SLAVE_ADDRESS, ACC_MAG_CTRL5, 0x64);
    write_to_reg(ACC_MAG_SLAVE_ADDRESS, ACC_MAG_CTRL6, 0x20);
    write_to_reg(ACC_MAG_SLAVE_ADDRESS, ACC_MAG_CTRL7, 0x00);
}/*init_mag*/

/*********************************************************************//**
 *Description: read_acc_raw values 16-bit resolution
 * 
 *Input:
 * 
 *Return:
 * 
 *Author: Christian Bodelsson<bodelsson@gmail.com>
 *************************************************************************/

void read_acc_values_raw(struct acc_val_raw *_acc_raw_) {
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


/*********************************************************************//**
 *Description: Private function so the values will be 0 for y and x in correct state of sensor
 * 
 *Input:
 * 
 *Return:
 * 
 *Author: Christian Bodelsson<bodelsson@gmail.com>
 *************************************************************************/
static void normalize_angle(struct acc_val_angle *_acc_angle){
    _acc_angle->x -= (float) 180.0;
    if (_acc_angle->y > 90) {
        _acc_angle->y -= (float) 270;
    } else {
        _acc_angle->y += (float) 90;
    }
}/*normalize_angle*/

/*********************************************************************//**
 *Description: read_acc_angles values
 * 
 *Input:
 * 
 *Return:
 * 
 *Author: Christian Bodelsson<bodelsson@gmail.com>
 *************************************************************************/
void read_acc_values_angle(struct acc_val_raw *_acc_raw_, struct acc_val_angle *_acc_angle) {
    _acc_angle->x = (float) (atan2(_acc_raw_->y, _acc_raw_->z) + M_PI) * RAD_TO_DEG;
    _acc_angle->y = (float) (atan2(_acc_raw_->z, _acc_raw_->x) + M_PI) * RAD_TO_DEG;
    normalize_angle(_acc_angle);
   


}/*read_acc_angle*/


/*********************************************************************//**
 *Description: read_mag_raw values 16-bit resolution
 * 
 *Input:
 * 
 *Return:
 * 
 *Author: Christian Bodelsson<bodelsson@gmail.com>
 *************************************************************************/

void read_mag_values_raw(struct mag_val_raw *_mag_raw_) {
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