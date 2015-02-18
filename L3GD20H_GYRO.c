/* 
 * File:   L3GD20H_GYRO.c
 * Author: Christian Bodelsson<bodelsson@gmail.com>
 *
 * Created on February 17, 2015, 8:46 AM
 */
//TODO Write documentation
#include <avr/io.h>
#include "twi_master.h"
#include "L3GD20H_GYRO.h"
#include "ALTIMU_10.h"
/*************************************************************************
 Initiate the gyro more details later.... 
 
*************************************************************************/

void init_gyro(void) {
    
    write_to_reg(GYRO_SLAVE_ADDRESS,GYRO_LOW_ODR, 0x00);
    write_to_reg(GYRO_SLAVE_ADDRESS,GYRO_CTRL4, 0x00);
    write_to_reg(GYRO_SLAVE_ADDRESS,GYRO_CTRL1, 0x6F);
}/*init_gyro*/

//TODO
/*************************************************************************
 Read the values from all three axis.
 
 Return: valstruct loaded with x:y:z
 
*************************************************************************/
struct valstruct read_gyro_values(void) {

    Val val;
    if (i2c_start(GYRO_SLAVE_ADDRESS << 1) == 0) {
        i2c_write(GYRO_OUT_X_L | (1 << 7));//Auto increment registers by writing the MSB high

        if (i2c_rep_start(((uint8_t) GYRO_SLAVE_ADDRESS << 1) | 1) == 0) {
            uint8_t xlg = i2c_read(ACK);
            uint8_t xhg = i2c_read(ACK);
            
            uint8_t ylg = i2c_read(ACK);
            uint8_t yhg = i2c_read(ACK);

            uint8_t zhg = i2c_read(ACK);
            uint8_t zlg = i2c_read(NAK);


            val.x = (int16_t) (xhg << 8 | xlg);
            val.y = (int16_t) (yhg << 8 | ylg);
            val.z = (int16_t) (zhg << 8 | zlg);
            return val;
            
        }

    }
    return val;
}/*read_gyro_values*/
