/* 
 * File:   ALTIMU_10.h
 * Author: Christian Bodelsson<bodelsson@gmail.com>
 * Public Key: https://pgp.mit.edu/pks/lookup?op=get&search=0x3DD59D8AB91E4765
 * 
 * Description: The ALTIMU_10 contain 4 different sensors one three-axis angular
 * rate sensor[L3GD20H], one pressure sensor[LPS25H], one 3D digital linear acceleration sensor 
 * and a 3D digital magnetic sensor[LSM303D]. Here the slave addresses
 * for each sensor is defined below. Also two function prototypes, to be used
 * to read/write to the registers on the ALTIMU_10.
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
 * Created on February 16, 2015, 6:19 PM
 */

#ifndef ALTIMU_10_H
#define	ALTIMU_10_H

#ifdef	__cplusplus
extern "C" {
#endif


#define GYRO_SLAVE_ADDRESS  0x6B
#define ACC_MAG_SLAVE_ADDRESS   0x1D
#define BAR_SLAVE_ADDRESS   0x5D

extern uint8_t read_from_reg(unsigned char address_slave, unsigned char reg_slave);
extern uint8_t write_to_reg(unsigned char address_slave, unsigned char reg_slave, uint8_t data);




#ifdef	__cplusplus
}
#endif


#endif	/* ALTIMU_10_H */

