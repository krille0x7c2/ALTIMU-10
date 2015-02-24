/* 
 * File:   ALTIMU_10.c
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
//TODO Write documentation
#include <avr/io.h>
#include <stdlib.h>
#include "twi_master.h"
#include "ALTIMU_10.h"
typedef unsigned char byte;


/*********************************************************************//**
 *Description: Write to slave register 
 *[M:START][address_slave][0][S:ACK][reg_slave][S:ACK][data][S:ACK][M:STOP]
 *
 *Input: [7-bit address to the slave] [Register on slave] [Byte to send]
 *
 *Return: 0 if success
 *        1 if fail
 *Author: Christian Bodelsson<bodelsson@gmail.com>
 *************************************************************************/

uint8_t write_to_reg(byte address_slave, byte reg_slave, uint8_t data) {
    if (i2c_start(address_slave << 1) == 0) {
        i2c_write(reg_slave);
        i2c_write(data);
        i2c_stop();
        return 0;
    } else {
        return 1;
    }
}/*write_to_reg*/

/*********************************************************************//**
 *Description: Read from slave register 
 *[M:START][address_slave][0][S:ACK][reg_slave][S:ACK][M:REPSTART][address_slave][1][S:ACK][data][S_ACK][M:NAK]
 *
 *Input: [7-bit address to the slave] [Register on slave]
 *
 *Return: Byte if success
 *        1 if fail
 *Author: Christian Bodelsson<bodelsson@gmail.com>
 *************************************************************************/
uint8_t read_from_reg(byte address_slave, byte reg_slave) {
    if (i2c_start(address_slave << 1) == 0) {
        i2c_write(reg_slave);
        if (i2c_rep_start(((uint8_t) address_slave << 1) | 1) == 0) {
            return i2c_read(NAK);
        }
    }
    return 1;
}/*read_from_reg*/
