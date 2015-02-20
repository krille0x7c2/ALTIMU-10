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
#include "usart.h"
#include <util/delay.h>
#include "ALTIMU_10.h"
#include "LSM303D_ACC_MAG.h"
#include "L3GD20H_GYRO.h"
#include "LPS25H_BAR.h"

/*
 *Main
 * 
 *  
 */

int main(void) {
    USART0Init();
    TWIInit();
    Gyro_raw gyro_raw;
    Gyro_dps gyro_dps;
    Gyro_angle gyro_angle;

    Acc_raw acc_raw;
    Acc_angle acc_angel;

    Mag_raw mag_raw;

    
    //Set stream pointer
    FILE usart0_str = FDEV_SETUP_STREAM(USART0SendByte, USART0ReceiveByte, _FDEV_SETUP_RW);
    //assign our stream to standart I/O streams, cause why re-invent the wheel? Great for debuging :-) Don't forget to exclude later on.!!!!!!!!!!!!!!!
    stdin = stdout = &usart0_str;
    /*gyro*/
    //            init_gyro();

    /*acc*/
//        init_acc();

    /*mag*/
    //    init_mag();


    /*pressure*/
    //        init_bar();

    while (1) {

        _delay_ms(500);
        /*gyro*/



        //        printf("[X: %d Y: %d Z: %d]\n",gyro_raw.x,gyro_raw.y,gyro_raw.z);

        //        printf("[X: %f Y: %f Z: %f]\n",gyro_dps.x,gyro_dps.y,gyro_dps.z);

        //        printf("[X: %f Y: %f Z: %f]\n",gyro_angle.x,gyro_angle.y,gyro_angle.z);


        /*pressure*/
        //                printf("%f ", read_temp_celsius());

        //            printf("%f hpa", read());

        /*acc*/
//        read_acc_values_raw(&acc_raw);
//        read_acc_values_angle(&acc_raw, &acc_angel);
//        printf("[X: %d Y: %d]\n", acc_angel.x, acc_angel.y);

        /*mag*/
        //        read_mag_raw(&mag_raw);
        //        printf("[X: %d Y: %d Z: %d]\n",mag_raw.x,mag_raw.y,mag_raw.z);


    }
    return 0;
}
