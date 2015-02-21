/* 
 * File:   ALTIMU_10.c
 * Author: Christian Bodelsson<bodelsson@gmail.com>
 *
 * Created on February 17, 2015, 8:46 AM
 */
//TODO Write documentation
#include <avr/io.h>
#include <stdlib.h>
#include "twi_master.h"
#include "ALTIMU_10.h"



/*************************************************************************
 Write to slave register
 
 Input: [7-bit address to the slave] [Register value on slave] [Byte to send]
 
 Return: 0 if success
         1 if fail
 
 *************************************************************************/

uint8_t write_to_reg(unsigned char address_slave, unsigned char reg_slave, uint8_t data) {
    if (i2c_start(address_slave << 1) == 0) {
        i2c_write(reg_slave);
        i2c_write(data);
        i2c_stop();
        return 0;
    } else {
        return 1;
    }
}/*write_to_reg*/

/*************************************************************************
 Read from slave register
 
 Input: [7-bit address to the slave] [Register value on slave]
 
 Return: Byte if success
         1 if fail
 
 *************************************************************************/
uint8_t read_from_reg(unsigned char address_slave, unsigned reg_slave) {
    if (i2c_start(address_slave << 1) == 0) {
        i2c_write(reg_slave);
        if (i2c_rep_start(((uint8_t) address_slave << 1) | 1) == 0) {
            return i2c_read(NAK);
        }
    }
    return 1;
}/*read_from_reg*/


/*************************************************************************
 Constructor for Altimu
 
 *************************************************************************/
