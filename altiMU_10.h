/* 
 * File:   altiMU_10.h
 * Author: krille0x7c2
 *
 * Created on February 16, 2015, 6:19 PM
 */

#ifndef ALTIMU_10_H
#define	ALTIMU_10_H
//7-bit slave addresses for the three sensors
#define GYRO_SLAVE_ADDRESS  0x6B
#define ACC_MAG_SLAVE_ADDRESS   0x1D
#define BAR_SLAVE_ADDRESS   0x5D
/*TIMING, SAME FOR ALL*/
#define SCL_LOW_TIME_US    2//1.3us
#define SCL_HIGH_TIME_US   1//0.6us
#define SDA_SETUP_TIME_NS  100//ns
#define SDA_HOLD_TIME_MAX_US   1//0.6us
#define START_CONDITION_HOLD_US    1//0.6//us
#define STOP_SETUP_TIME_US 1//0.6us
#define BUS_FREE_STOP_START_US 2//1.3us


#endif	/* ALTIMU_10_H */

