/**
 * @file BNO055.h
 * @author Gaurav Manda (grvmanda@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _BNO055
#define _BNO055

#include <stdlib.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include <cerrno>
#include <cstring>
#include <clocale>

extern "C" {
    #include <linux/types.h>
    #include <linux/i2c-dev.h>
    #include <i2c/smbus.h>
}

#include "common.h"

/*---------------- REGISTER ADDRESSES --------------------*/

/* Operation mode */
#define REG_ADDR_OPR_MODE                   0x3D

/* IMU DATA in Q*/
#define REG_QUA_Data_z_MSB                  0x27
#define REG_QUA_Data_z_LSB                  0x26
#define REG_QUA_Data_y_MSB                  0x25
#define REG_QUA_Data_y_LSB                  0x24
#define REG_QUA_Data_x_MSB                  0x23
#define REG_QUA_Data_x_LSB                  0x22
#define REG_QUA_Data_w_MSB                  0x21
#define REG_QUA_Data_w_LSB                  0x20

/* IMU DATA in Euler*/
#define REG_EUL_Pitch_MSB                   0x1F
#define REG_EUL_Pitch_LSB                   0x1E
#define REG_EUL_Roll_MSB                    0x1D
#define REG_EUL_Roll_LSB                    0x1C
#define REG_EUL_Heading_MSB                 0x1B
#define REG_EUL_Heading_LSB                 0x1A

/* Some random data to test */
#define REG_BL_Rev_ID                       0x06

/*------------------- VALUES -----------------------------*/
#define VALUE_OPR_MODE_IMU                  0x08


typedef struct {
    // __s16 q_x;
    // __s16 q_y;
    // __s16 q_z;
    // __s16 q_w;
    double heading;
    double pitch;
    double roll;
} imu_data_t;


class BNO055 {
    
    private:
        int _addr;
        int _devId;
        int _drvStatus;
        int _file;
        imu_data_t _prev_IMU_data;

        int _init();
        auto _readByte(__s32 *data, __u8 addr) -> error_codes;
        auto _readWord(__s32 *data, __u8 addr) -> error_codes;
        auto _writeByte(__s32 *data, __u8 addr) -> error_codes;
        auto _writeWord(__s32 *data, __u8 addr) -> error_codes;

    public:        
        
        BNO055(int addr, int devID);
        int Init();
        int status();

        auto readIMU(imu_data_t *imu_data) -> error_codes; 

};



#endif