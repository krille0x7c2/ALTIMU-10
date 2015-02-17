/* 
 * File:   LPS25H_BAR.c
 * Author: krille0x7c2
 *
 * Created on February 17, 2015, 8:46 AM
 */
#include <avr/io.h>
#include "twi_master.h"
#include "LPS25H_BAR.h"
#include "altiMU_10.h"

uint8_t write_to_bar_reg(unsigned char address, uint8_t data) {
    if (i2c_start(BAR_SLAVE_ADDRESS << 1) == 0) {
        i2c_write(address);
        i2c_write(data);

        return 1;
    } else {
        return 0;
    }
}

uint8_t read_from_bar_reg(unsigned char address) {

    if (i2c_start(BAR_SLAVE_ADDRESS << 1) == 0) {
        i2c_write(address);

        if (i2c_rep_start(((uint8_t) BAR_SLAVE_ADDRESS << 1) | 1) == 0) {


            return i2c_readNak();
        }
    }
    return 0;
}

float read_temp_celsius(void) {
    if (i2c_start(BAR_SLAVE_ADDRESS << 1) == 0) {
        i2c_write(BAR_TEMP_OUT_L | (1 << 7));

        if (i2c_rep_start(((uint8_t) BAR_SLAVE_ADDRESS << 1) | 1) == 0) {
            uint8_t tl = i2c_readAck();
            uint8_t th = i2c_readNak();
            int16_t temp = (int16_t) (th << 8 | tl);
            return (45.5 + ((float) temp) / 480); //To Celsius
            
        } else {
            return 98;
        }

    }
    return 99;
}

float read_pressure_hpa(void) {
    if (i2c_start(BAR_SLAVE_ADDRESS << 1) == 0) {
        i2c_write(BAR_PRESS_POUT_XL | (1 << 7));

        if (i2c_rep_start(((uint8_t) BAR_SLAVE_ADDRESS << 1) | 1) == 0) {
            uint8_t pxl = i2c_readAck();
            uint8_t pl = i2c_readAck();
            uint8_t ph = i2c_readNak();
            int32_t temp = (int32_t) (int8_t) ph << 16 | (uint16_t) pl << 8 | pxl;
            return  ((float)temp / 4096);
        } else {
            return 98;
        }

    }
    return 99;

}
uint8_t init_bar(void){
    write_to_bar_reg(BAR_CTRL_REG1, 0xB0);
    i2c_stop();
    return 1;
}

