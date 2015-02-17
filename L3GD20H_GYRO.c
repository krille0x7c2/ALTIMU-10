/* 
 * File:   L3GD20H_GYRO.c
 * Author: krille0x7c2
 *
 * Created on February 17, 2015, 8:46 AM
 */
#include <avr/io.h>
#include "twi_master.h"
#include "L3GD20H_GYRO.h"
#include "altiMU_10.h"



uint8_t write_to_gyro_reg(unsigned char address, uint8_t data) {
    if (i2c_start(GYRO_SLAVE_ADDRESS << 1) == 0) {
        i2c_write(address);
        i2c_write(data);

        return 1;
    } else {
        return 0;
    }
}

uint8_t read_from_gyro_reg(unsigned char address) {

    if (i2c_start(GYRO_SLAVE_ADDRESS << 1) == 0) {
        i2c_write(address);

        if (i2c_rep_start(((uint8_t) GYRO_SLAVE_ADDRESS << 1) | 1) == 0) {


            return i2c_readNak();
        }
    }
    return 0;
}

uint8_t init_gyro(void) {
    write_to_gyro_reg(GYRO_LOW_ODR, 0x00);
    i2c_stop();
    write_to_gyro_reg(GYRO_CTRL4, 0x00);
    i2c_stop();
    write_to_gyro_reg(GYRO_CTRL1, 0x6F);
    i2c_stop();
    return 1;
}
//TODO
/**
 * Must convert values to dps ongoing work!
 * @return 
 */
struct valstruct read_gyro_values(void) {

    Val val;
    if (i2c_start(GYRO_SLAVE_ADDRESS << 1) == 0) {
        i2c_write(GYRO_OUT_X_L | (1 << 7));

        if (i2c_rep_start(((uint8_t) GYRO_SLAVE_ADDRESS << 1) | 1) == 0) {
            uint8_t xlg = i2c_readAck();
            uint8_t xhg = i2c_readAck();
            
            uint8_t ylg = i2c_readAck();
            uint8_t yhg = i2c_readAck();
            
            uint8_t zhg = i2c_readAck();
            uint8_t zlg = i2c_readNak();


            val.x = (int16_t) (xhg << 8 | xlg);
            val.y = (int16_t) (yhg << 8 | ylg);
            val.z = (int16_t) (zhg << 8 | zlg);

            
        }
        return val;

    }
    return val;
}
