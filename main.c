/* 
 * File:   main.c
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
 * Created on February 16, 2015, 6:03 PM
 */


#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "twi_master.h"
#include "uart.h"
#include <util/delay.h>
#include "ALTIMU_10.h"
#include "LSM303D_ACC_MAG.h"
#include "L3GD20H_GYRO.h"
#include "LPS25H_BAR.h"
#include "main.h"
#define DEBUG 1

Gyro_raw gyro_raw;
Gyro_dps gyro_dps;
Gyro_angle gyro_angle;
Acc_raw acc_raw;
Acc_angle acc_angel;
Mag_raw mag_raw;


static void stop_sensor(uint8_t sensor) {
    switch (sensor) {
        case GYRO:
            power_down_gyro();
            /*this sensor also has a sleep mode :-)*/
            //            sleep_gyro();
            break;
        case BAR:
            power_down_bar();

            break;
        case ACC:
            power_down_acc();
            break;
        case MAG:
            power_down_mag();
            break;
        default:
            break;
    }
}

static void init_sensor(uint8_t sensor) {
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

static void print_sensor(uint8_t sensor) {
    switch (sensor) {
        case BAR:
            printf("%f hpa", read_pressure_hpa());
            //            printf("%f ", read_temp_celsius());
            break;
        case GYRO:
            read_gyro_values(&gyro_raw);
            //            printf("[X: %d Y: %d Z: %d]\n",gyro_raw.x,gyro_raw.y,gyro_raw.z);
            //            read_gyro_values_rate_dps(&gyro_data,&gyro_data_dps);
            //            printf("[X: %f Y: %f Z: %f]\n",gyro_dps.x,gyro_dps.y,gyro_dps.z);
            //            read_gyro_values_angle(&gyro_data_dps,&gyro_data_angle);
            //            printf("[X: %f Y: %f Z: %f]\n",gyro_angle.x,gyro_angle.y,gyro_angle.z);
            break;
        case ACC:
            read_acc_values_raw(&acc_raw);
            read_acc_values_angle(&acc_raw, &acc_angel);
            printf("[X: %f Y: %f]\n", acc_angel.x, acc_angel.y);
            break;
        case MAG:
            read_mag_values_raw(&mag_raw);
            printf("[X: %d Y: %d Z: %d]\n", mag_raw.x, mag_raw.y, mag_raw.z);
            break;
        default:
            break;
    }
}


int main(void) {
    uart_init();
    twi_init();
    init_sensor(NONE);

    



#if DEBUG          
    FILE uart_stream = FDEV_SETUP_STREAM(uart_send_byte, uart_receive_byte, _FDEV_SETUP_RW); //Set stream pointer
    //assign our stream to standard I/O streams, cause why re-invent the wheel? Great for debuging :-)
    stdin = stdout = &uart_stream;
#endif    




    for (;;) {
       
        _delay_ms(500);
        print_sensor(NONE);
        //        _delay_ms(50);
        stop_sensor(NONE);
        //        _delay_ms(1000);
        //        init_sensor(BAR);


    }
    return 0;
}
