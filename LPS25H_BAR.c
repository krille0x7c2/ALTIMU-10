/* 
 * File:   LPS25H_BAR.c
 * Author: Christian Bodelsson<bodelsson@gmail.com>
 *
 * Created on February 17, 2015, 8:46 AM
 */
//TODO Write documentation
#include <avr/io.h>
#include "twi_master.h"
#include "LPS25H_BAR.h"
#include "ALTIMU_10.h"

/*************************************************************************
 Read the tempature
 
 Return: float value in Celsius
 
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

/*************************************************************************
 Read the pressure
 
 Return: float value in hpa
 
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

/*************************************************************************
 Initialize the bar,, more info on the way
 
 ************************************************************************/

void init_bar(void) {

    write_to_reg(BAR_SLAVE_ADDRESS, BAR_CTRL_REG1, 0xB0);
}/*init_bar*/
