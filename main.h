/* 
 * File:   main.h
 * Author: krille0x7c2
 *
 * Created on February 21, 2015, 9:43 PM
 */

#ifndef MAIN_H
#define	MAIN_H
#define GYRO    0
#define BAR     1
#define ACC     2
#define MAG     3
void init_sensor(uint8_t sensor);
void stop_sensor(uint8_t sensor);
void print_sensor(uint8_t sensor);

#endif	/* MAIN_H */

