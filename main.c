#include "usart.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "twi_master.h"
#include "LPS25H_BAR.h"
#include "L3GD20H_GYRO.h"

#include "altiMU_10.h"
#include <util/delay.h>

/*
 *Main
 * 
 *  
 */




int main(void) {
    USART0Init();
    TWIInit();
    
    //Set stream pointer
    FILE usart0_str = FDEV_SETUP_STREAM(USART0SendByte, USART0ReceiveByte, _FDEV_SETUP_RW);
    //assign our stream to standart I/O streams
    stdin = stdout = &usart0_str;
     /*acc*/
//    init_gyro();
    
    /*pressure*/
//    init_bar();

    while (1) {
        _delay_ms(1000);
        
        /*acc*/
//        struct valstruct val;
//        val = read_gyro_values();
//        printf("[X: %d Y: %d Z: %d]",val.x,val.y,val.z);
        
       /*pressure*/
//        printf("%f ", read_temp_celsius());
//        printf("%f hpa", read_pressure_hpa());
//        i2c_stop();

    }
    return 0;
}
