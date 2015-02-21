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
#include "main.h"

    Gyro_raw gyro_raw;
    Gyro_dps gyro_dps;
    Gyro_angle gyro_angle;
    Acc_raw acc_raw;
    Acc_angle acc_angel;
    Mag_raw mag_raw;

/*
 *Main
 * 
 *  
 */
void init_sensor(uint8_t sensor) {
    switch (sensor) {
        case GYRO:
            init_gyro();
            break;
        case BAR:
            init_bar();
            break;
        case ACC:
            init_acc();
            break;
        case MAG:
            init_mag();
            break;
        default:
            break;
    }
}
void print_sensor(uint8_t sensor){
    switch(sensor){
        case BAR:
            printf("%f hpa",  read_pressure_hpa());
//            printf("%f ", read_temp_celsius());
            break;
        case GYRO:
            read_gyro_values(&gyro_raw);
            printf("[X: %d Y: %d Z: %d]\n",gyro_raw.x,gyro_raw.y,gyro_raw.z);
//            read_gyro_values_rate_dps(&gyro_data,&gyro_data_dps);
//            printf("[X: %f Y: %f Z: %f]\n",gyro_dps.x,gyro_dps.y,gyro_dps.z);
//            read_gyro_values_angle(&gyro_data_dps,&gyro_data_angle);
//            printf("[X: %f Y: %f Z: %f]\n",gyro_angle.x,gyro_angle.y,gyro_angle.z);
            break;
        case ACC:
            read_acc_values_raw(&acc_raw);
            read_acc_values_angle(&acc_raw, &acc_angel);
            printf("[X: %d Y: %d]\n", acc_angel.x, acc_angel.y);
            break;
        case MAG:
            read_mag_values_raw(&mag_raw);
            printf("[X: %d Y: %d Z: %d]\n",mag_raw.x,mag_raw.y,mag_raw.z);
            break;
        default:
            break;
    }
}

int main(void) {
   
    USART0Init();
    TWIInit();
    init_sensor(BAR);
    

    //Set stream pointer
    FILE usart0_str = FDEV_SETUP_STREAM(USART0SendByte, USART0ReceiveByte, _FDEV_SETUP_RW);
    //assign our stream to standart I/O streams, cause why re-invent the wheel? Great for debuging :-) Don't forget to exclude later on.!!!!!!!!!!!!!!!
    stdin = stdout = &usart0_str;
    

    while (1) {

        _delay_ms(500);
        print_sensor(0);


    }
    return 0;
}
