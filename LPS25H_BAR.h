/* 
 * File:   LPS25H_BAR.h
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
 * Created on February 17, 2015, 9:20 AM
 */

#ifndef LPS25H_BAR_H
#define	LPS25H_BAR_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "LSM303D_ACC_MAG.h"


#define BAR_REF_P_XL    0x08//R/W
#define BAR_REF_P_L     0x09//R/W
#define BAR_REF_P_H     0x0A//R/W
#define BAR_WHO_AM_I    0x0F//R    10111101
#define BAR_RES_CONF    0x10//R/W  00000101
//Reserved 0x11-0x1F(No modify!!)
#define BAR_CTRL_REG1   0x20//R/W
#define BAR_CTRL_REG2   0x21//R/W
#define BAR_CTRL_REG3   0x22//R/W
#define BAR_CTRL_REG4   0x23//R/W
#define BAR_INT_CFG     0x24//R/W
#define BAR_INT_SOURCE  0x25//R
//Reserved 0x26 (No modify!!)
#define BAR_STATUS_REG  0x27//R
/*Output*/
#define BAR_PRESS_POUT_XL   0x28//R
#define BAR_PRESS_OUT_L 0x29//R
#define BAR_PRESS_OUT_H 0x2A//R
#define BAR_TEMP_OUT_L  0x2B//R
#define BAR_TEMP_OUT_H  0x2C//R
/*END*/
//Reserved 0x2D (No modify!!)

#define BAR_FIFO_CTRL   0x2E//R/W
#define BAR_FIFO_STATUS 0x2F//R
#define BAR_THS_P_L 0x30//R/W
#define BAR_THS_P_H 0x31//R/W
//Reserved 0x32-0x38 (No modify!!)
#define BAR_RPDS_L  0x39//R/W
#define BAR_RPDS_H  0x3A//R/W

extern float read_temp_celsius(void);
extern float read_pressure_hpa(void);
extern void init_bar(void);
extern void power_down_bar(void);





#ifdef	__cplusplus
}
#endif


#endif	/* LPS25H_BAR_H */

