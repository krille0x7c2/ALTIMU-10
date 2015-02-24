/* 
 * File:   twi_master.c
 * Author: Christian Bodelsson<bodelsson@gmail.com>
 * Public Key: https://pgp.mit.edu/pks/lookup?op=get&search=0x3DD59D8AB91E4765
 * source: http://www.atmel.com/images/Atmel-8271-8-bit-AVR-Microcontroller-ATmega48A-48PA-88A-88PA-168A-168PA-328-328P_datasheet_Complete.pdf page 216
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
 * Created on February 16, 2015, 6:23 PM
 */
#include <avr/io.h>
#include "twi_master.h"
#include <inttypes.h>
#include <compat/twi.h>
#include <util/delay.h>

void twi_init(void) {
    //set SCL to 400kHz
    TWSR = 0x00;
    TWBR = 0x0C;
    //enable TWI
    TWCR = (1 << TWEN);
}

uint8_t twi_start(unsigned char address) {
    uint8_t twst;
    //send START condition
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    // wait until transmission completed
    while (!(TWCR & (1 << TWINT)));
    // check value of TWI Status Register. Mask prescaler bits.
    twst = TW_STATUS & 0xF8;
    if ((twst != TW_START) && (twst != TW_REP_START)) return 1;
    // send device address
    TWDR = address;
    TWCR = (1 << TWINT) | (1 << TWEN);
    // wail until transmission completed and ACK/NACK has been received
    while (!(TWCR & (1 << TWINT)));
    // check value of TWI Status Register. Mask prescaler bits.
    twst = TW_STATUS & 0xF8;
    return (twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) ? 1 : 0;
}

void twi_start_wait(unsigned char address) {
    uint8_t twst;
    while (1) {
        // send START condition
        TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
        // wait until transmission completed
        while (!(TWCR & (1 << TWINT)));
        // check value of TWI Status Register. Mask prescaler bits.
        twst = TW_STATUS & 0xF8;
        if ((twst != TW_START) && (twst != TW_REP_START)) continue;
        // send device address
        TWDR = address;
        TWCR = (1 << TWINT) | (1 << TWEN);
        // wail until transmission completed
        while (!(TWCR & (1 << TWINT)));
        // check value of TWI Status Register. Mask prescaler bits.
        twst = TW_STATUS & 0xF8;
        if ((twst == TW_MT_SLA_NACK) || (twst == TW_MR_DATA_NACK)) {
            /* device busy, send stop condition to terminate write operation */
            TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
            // wait until stop condition is executed and bus released
            while (TWCR & (1 << TWSTO));
            continue;
        }
        //if( twst != TW_MT_SLA_ACK) return 1;
        break;
    }
}

uint8_t twi_rep_start(unsigned char address) {
    return twi_start(address);
}

void twi_stop(void) {
    /* send stop condition */
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
    // wait until stop condition is executed and bus released
    while (TWCR & (1 << TWSTO));

}


uint8_t twi_write(unsigned char data) {
    // send data to the previously addressed device
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    // wait until transmission completed
    while (!(TWCR & (1 << TWINT)));
    // check value of TWI Status Register. Mask prescaler bits only need the top 5 bits
    return ((TW_STATUS & 0xF8) != TW_MT_DATA_ACK) ? 1 : 0;

}

uint8_t twi_readAck(void) {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    while (!(TWCR & (1 << TWINT)));

    return TWDR;

}

uint8_t twi_readNak(void) {
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));

    return TWDR;

}