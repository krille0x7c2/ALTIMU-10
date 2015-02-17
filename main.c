#include "L3GD20H_GYRO.h"
#include "usart.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "twi_master.h"
#include "LPS25H_BAR.h"

#include "altiMU_10.h"
#include <util/delay.h>

uint8_t write_to_address(unsigned char address, uint8_t data) {
    if (i2c_start(BAR_SLAVE_ADDRESS << 1) == 0) {
        i2c_write(address);
        i2c_write(data);
        i2c_stop();
        return 1;
    } else {
        return 0;
    }
}

int main(void) {
    uint8_t u8ebyte;
    USART0Init();
    TWIInit();
    //    _delay_ms(100);
    //Set stream pointer
    FILE usart0_str = FDEV_SETUP_STREAM(USART0SendByte, USART0ReceiveByte, _FDEV_SETUP_RW);
    //assign our stream to standart I/O streams
    stdin = stdout = &usart0_str;
    if (read_from_address(BAR_FIFO_CTRL, &u8ebyte) == 1) {
        printf("\nBefore: %#04x", u8ebyte);
    }
    if (write_to_address(BAR_FIFO_CTRL, 0xff) == 1) {
        printf("\nWrote 0xff to: %d", BAR_FIFO_CTRL);
    }

    if (read_from_address(BAR_FIFO_CTRL, &u8ebyte) == 1) {
        printf("\nAfter: %#04x", u8ebyte);
    }
    if (write_to_address(BAR_FIFO_CTRL, 0x00) == 1) {
        printf("\nWrote 0x00 to: %d", BAR_FIFO_CTRL);
    }
    if (read_from_address(BAR_FIFO_CTRL, &u8ebyte) == 1) {
        printf("\nBack to normal: %#04x", u8ebyte);
    }

    while (1) {

    }
    return 0;
}
