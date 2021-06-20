#ifndef _BNO055
#define _BNO055

#include <stdlib.h>
#include <cstdio>
#include <fstream>
#include <iostream>

// extern "C" {
//     #include <linux/i2c-dev.h>
//     #include <sys/ioctl.h>
//     #include <i2c/smbus.h>
// }
// #include <stddef.h>
// #include <fcntl.h> 
// #include <unistd.h> 
// // }
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include <cerrno>
#include <cstring>
#include <clocale>

extern "C" {
    #include <linux/types.h>
#include <linux/i2c-dev.h>
// #include <errno.h>
// #include </usr/src/linux-headers-5.4.0-1035-raspi/include/linux/i2c.h>
// #include "/usr/src/linux-raspi-headers-5.4.0-1036/include/linux/i2c.h"
#include <i2c/smbus.h>
}

/* Operation mode */
#define REG_ADDR_OPR_MODE                   0x3D
#define REG_ADDR_OPR_MODE                   0x3D

/* IMU DATA */
#define REG_QUA_Data_z_MSB                  0x27
#define REG_QUA_Data_z_LSB                  0x26
#define REG_QUA_Data_y_MSB                  0x25
#define REG_QUA_Data_y_LSB                  0x24
#define REG_QUA_Data_x_MSB                  0x23
#define REG_QUA_Data_x_LSB                  0x22
#define REG_QUA_Data_w_MSB                  0x21
#define REG_QUA_Data_w_LSB                  0x20

/* Some random data to test */
#define REG_BL_Rev_ID                       0x06


class BNO055 {
    
    private:
        int _addr;
        int _devId;
        int _drvStatus;
        int _file;

        int _init();
        void _readData();

    public:        
        
        BNO055(int addr, int devID);
        int Init();
        int status();
        // vector<int> readIMU(void); 
        void readIMU(void); 


};



#endif