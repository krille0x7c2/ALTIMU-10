/* 
 * File:   L3GD20H_GYRO.c
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

#include <avr/io.h>
#include <util/delay_basic.h>
#include <util/delay.h>
#include "ALTIMU_10.h"
#include "twi_master.h"
#include "L3GD20H_GYRO.h"
#include "LSM303D_ACC_MAG.h"




/***********************************************************************
 *Description: Initiate the gyro power 5.0mA
 * GYRO_LOW_ODR: LOW ODR DISABLED default setting
 * GYRO_CTRL4:   +/-250 dps       default setting
 * GYRO_CTRL1:   [[DR 01 200Hz ODR],[BW 10 50Hz bandwidth],[PD 1 normal mode],[Zen=Yen=Xen=1 all axes enabled]]  
 * 
 *Input:
 * 
 *Return:
 * 
 *Author: Christian Bodelsson<bodelsson@gmail.com>
 *************************************************************************/

void init_gyro(void) {

    write_to_reg(GYRO_SLAVE_ADDRESS, GYRO_LOW_ODR, 0x00);
    write_to_reg(GYRO_SLAVE_ADDRESS, GYRO_CTRL4, 0x00);
    write_to_reg(GYRO_SLAVE_ADDRESS, GYRO_CTRL1, 0x6F);
}/*init_gyro*/

/***********************************************************************
 *Description: Put the gyro to sleep 2.5mA
 *(For Sleep Mode set {PD:Zen:Yen:Xen} to {1000})
 * 
 *Input:
 * 
 *Return:
 * 
 *Author: Christian Bodelsson<bodelsson@gmail.com>
 *************************************************************************/
void sleep_gyro(void){
    write_to_reg(GYRO_SLAVE_ADDRESS, GYRO_CTRL1, 0x08);
}/*sleep_gyro*/


/***********************************************************************
 *Description: Power down the gyro 1uA
 *PD=0 = power down
 * 
 *Input:
 * 
 *Return:
 * 
 *Author: Christian Bodelsson<bodelsson@gmail.com>
 *************************************************************************/
void power_down_gyro(void){
    write_to_reg(GYRO_SLAVE_ADDRESS, GYRO_CTRL1, 0x00);
}/*power_down_gyro*/

/***********************************************************************
 *Description: Wake gyro 5.0mA
 *GYRO_CTRL1:   [[DR 01 200Hz ODR],[BW 10 50Hz bandwidth],[PD 1 normal mode],[Zen=Yen=Xen=1 all axes enabled]]
 * 
 *Input:
 * 
 *Return:
 * 
 *Author: Christian Bodelsson<bodelsson@gmail.com>
 *************************************************************************/
void wake_gyro(void){
    write_to_reg(GYRO_SLAVE_ADDRESS, GYRO_CTRL1, 0x6F);
}/*wake_gyro*/


/***********************************************************************
 *Description: Read the raw values from all three axis. 16-bit resolution
 *
 *Input: Pointer to data structure, passed by reference.
 * 
 *Return:
 * 
 *Author: Christian Bodelsson<bodelsson@gmail.com>
 *************************************************************************/
void read_gyro_values(struct gyro_data *_gyro_data_) {

//    timer1_init();
//    while (TCNT1 < DELAY_20M);
    _delay_ms(20);
    if (i2c_start(GYRO_SLAVE_ADDRESS << 1) == 0) {
        i2c_write(GYRO_OUT_X_L | (1 << 7)); //Auto increment registers by writing the asserting MSB 

        if (i2c_rep_start(((uint8_t) GYRO_SLAVE_ADDRESS << 1) | 1) == 0) {
            uint8_t xlg = i2c_read(ACK);
            uint8_t xhg = i2c_read(ACK);

            uint8_t ylg = i2c_read(ACK);
            uint8_t yhg = i2c_read(ACK);

            uint8_t zlg = i2c_read(ACK);
            uint8_t zhg = i2c_read(NAK);

            _gyro_data_->x = (int16_t) (xhg << 8 | xlg);
            _gyro_data_->y = (int16_t) (yhg << 8 | ylg);
            _gyro_data_->z = (int16_t) (zhg << 8 | zlg);

        }
    }

}/*read_gyro_values*/
/***********************************************************************
 *Description:
 *
 *Input: 
 *
 *Return: 
 *      
 *Author: Christian Bodelsson<bodelsson@gmail.com>
 *************************************************************************/
void read_gyro_values_rate_dps(struct gyro_data *_gyro_data, struct gyro_data_dps *gyro_data_dps) {
    gyro_data_dps->x = (float) _gyro_data->x * G_GAIN;
    gyro_data_dps->y = (float) _gyro_data->y * G_GAIN;
    gyro_data_dps->z = (float) _gyro_data->z * G_GAIN;

}/*read_gyro_values_dps*/

/***********************************************************************
 *Description:
 *
 *Input: 
 *
 *Return: 
 *      
 *Author: Christian Bodelsson<bodelsson@gmail.com>
 *************************************************************************/
void read_gyro_values_angle(struct gyro_data_dps *_gyro_data_dps, struct gyro_data_angle *gyro_data_angle) {
    gyro_data_angle->x = _gyro_data_dps->x * LOOP_PERIOD;
    gyro_data_angle->y = _gyro_data_dps->y * LOOP_PERIOD;
    gyro_data_angle->z = _gyro_data_dps->z * LOOP_PERIOD;

}/*read_gyro_values_angle*/

