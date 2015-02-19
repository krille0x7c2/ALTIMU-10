/* 
 * File:   main.c
 * Author: Christian Bodelsson<bodelsson@gmail.com>
 *
 * Created on February 16, 2015, 6:03 PM
 */
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "twi_master.h"
#include "LPS25H_BAR.h"
#include "L3GD20H_GYRO.h"
#include "ALTIMU_10.h"
#include "usart.h"
#include "LSM303D_ACC_MAG.h"
#include <util/delay.h>

/*
 *Main
 * 
 *  
 */


int main(void) {
    USART0Init();
    TWIInit();
    Val val;
    Val_dps val_dps;
    Val_angle val_angle;
    Acc_raw acc_raw;
    Mag_raw mag_raw;

    //Set stream pointer
    FILE usart0_str = FDEV_SETUP_STREAM(USART0SendByte, USART0ReceiveByte, _FDEV_SETUP_RW);
    //assign our stream to standart I/O streams, cause why re-invent the wheel? Great for debuging :-)
    stdin = stdout = &usart0_str;
    /*gyro*/
//            init_gyro();

    /*acc*/
//    init_acc();
    
    /*mag*/
//    init_mag();


    /*pressure*/
    //    init_bar();

    while (1) {
        
        _delay_ms(100);
        /*gyro*/
//                _delay_ms(20);
//                read_gyro_values(&val);
//                read_gyro_values_dps(&val,&val_dps);
//                read_gyro_values_angle(&val_dps,&val_angle);
//                printf("[X: %f Y: %f Z: %f]\n",val_angle.x,val_angle.y,val_angle.z);

        /*pressure*/
        //        printf("%f ", read_temp_celsius());
        //        printf("%f hpa", read_pressure_hpa());
        /*acc*/
//        read_acc_raw(&acc_raw);
//        printf("[X: %d Y: %d Z: %d]\n", acc_raw.x, acc_raw.y, acc_raw.z);
        /*mag*/
//        read_mag_raw(&mag_raw);
//        printf("[X: %d Y: %d Z: %d]\n",mag_raw.x,mag_raw.y,mag_raw.z);


    }
    return 0;
}
