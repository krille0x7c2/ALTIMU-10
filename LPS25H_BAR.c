/* 
 * File:   LPS25H_BAR.c
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
#include "twi_master.h"
#include "LPS25H_BAR.h"
#include "ALTIMU_10.h"


/*********************************************************************//**
 *Description: Read the tempature
 *
 *Input:
 *
 *Return: float value in Celsius
 *
 *Author: Christian Bodelsson<bodelsson@gmail.com>
 *************************************************************************/

float read_temp_celsius(void) {
    if (i2c_start(BAR_SLAVE_ADDRESS << 1) == 0) {
        i2c_write(BAR_TEMP_OUT_L | (1 << 7));

        if (i2c_rep_start(((uint8_t) BAR_SLAVE_ADDRESS << 1) | 1) == 0) {
            uint8_t tl = i2c_read(ACK);
            uint8_t th = i2c_read(NAK);
            int16_t temp = (int16_t) (th << 8 | tl);
            
            return (45.5 + ((float) temp) / 480); //To Celsius

        }

    }
    return 1;
}/*read_temp_celsius*/

/*********************************************************************//**
 *Description: Read the pressure 24-bit resolution 
 *
 *Input:
 *
 *Return: float value in hpa
 *
 *Author: Christian Bodelsson<bodelsson@gmail.com>
 ************************************************************************/
float read_pressure_hpa(void) {
    if (i2c_start(BAR_SLAVE_ADDRESS << 1) == 0) {
        i2c_write(BAR_PRESS_POUT_XL | (1 << 7));

        if (i2c_rep_start(((uint8_t) BAR_SLAVE_ADDRESS << 1) | 1) == 0) {
            uint8_t pxl = i2c_read(ACK);
            uint8_t pl = i2c_read(ACK);
            uint8_t ph = i2c_read(NAK);

            int32_t temp = (int32_t) (int8_t) ph << 16 | (uint16_t) pl << 8 | pxl;
            return ((float) temp / 4096);
        }
    }
    return 1;

}/*read_pressure_hpa*/

//TODO

/*********************************************************************//**
 *Description: Initialize the bar , power = 25uA on 1Hz
 *PD = 1 (active mode);  ODR = 011 (12.5 Hz pressure & temperature output data rate)
 *                                                        
 *Input:
 *
 *Return:
 *
 *Author: Christian Bodelsson<bodelsson@gmail.com>
 ************************************************************************/

void init_bar(void) {

    write_to_reg(BAR_SLAVE_ADDRESS, BAR_CTRL_REG1, 0xB0);
}/*init_bar*/

/*********************************************************************//**
 *Description: Power down the bar 0.5uA no sleep mode on this sensor :-(
 *PD=0 = power down
 *
 *Input:
 * 
 *Return:
 *
 *Author: Christian Bodelsson<bodelsson@gmail.com>
 *************************************************************************/
void power_down_bar(void){
    write_to_reg(GYRO_SLAVE_ADDRESS, BAR_CTRL_REG1, 0x00);
}/*power_down_bar*/
