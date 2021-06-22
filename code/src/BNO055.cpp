/**
 * @file BNO055.cpp
 * @author Gaurav Manda (grvmanda@gmail.com)
 * @brief Driver code for I2C based IMU sensor
 * @version 1.0
 * @date 2021-06-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include "BNO055.h"

using namespace std;

/**
 * @brief 
 * 
 * @param data 
 * @param addr 
 * @return error_codes 
 */
auto BNO055::_readByte(__s32 *data, __u8 addr) -> error_codes {

    __s32 res; 
    res = i2c_smbus_read_byte_data(this->_file, addr);
    if (res < 0) {
    /* ERROR HANDLING: i2c transaction failed */
        return FAIL_TO_READ_BYTE;
    } else {
        // cout << "data: " << res << endl;
        *data = res;
        return NO_ERROR;
    }

}

/**
 * @brief initialize the I2C driver
 * 
 * @return int 
 */
int BNO055::_init()
{
    char filename[20];
    int error = 0;
    __s32 res; 

    snprintf(filename, 19, "/dev/i2c-%d", this->_devId);
    cout << "filename " << filename << endl;
    this->_file = open(filename, O_RDWR);
    if (this->_file < 0) {
    /* ERROR HANDLING; you can check errno to see what went wrong */
        cout << "error: " << strerror(errno) << endl;
        this->_drvStatus = -1;
        return -1;
    }

    if (ioctl(this->_file, I2C_SLAVE, this->_addr) < 0) {
    /* ERROR HANDLING; you can check errno to see what went wrong */
        cout << "error: " << strerror(errno) << endl;
        this->_drvStatus = -2;
        return -1;
    }   

    this->_drvStatus = 0;

    /* Read out BTL version number for sanity check */
    res = i2c_smbus_read_byte_data(this->_file, REG_BL_Rev_ID);
    if (res < 0) {
    /* ERROR HANDLING: i2c transaction failed */
        cout << "error: " << strerror(errno) << endl;
    } else {
        cout << "BTL ID " << res << endl;
    }

    /* Set CONFIG_MODE to IMU Fusion mode */
    res = i2c_smbus_write_byte_data(this->_file, REG_ADDR_OPR_MODE, VALUE_OPR_MODE_IMU);
    if (res < 0) {
        cout << "error: " << strerror(errno) << endl;
    } else {
        cout << "wrote IMU config mode" << endl;
    }

    return error;
}

/**
 * @brief constructor for class BNO055
 * 
 * @param addr  address of the BNO055. By default it is 0x28; sometimes it can be 0x29
 * @param devID This defines which I2C device is used on the hardware. 
 */
BNO055::BNO055(int addr, int devID)
{
    this->_addr = addr;
    this->_devId = devID;
}

/**
 * @brief reinitialize the driver if it failed
 * 
 * @return int 
 */
int BNO055::Init()
{
    return _init();
}

/**
 * @brief status of the driver
 * 
 * @return int  
 */
int BNO055::status()
{
    return _drvStatus;
}

/**
 * @brief 
 * 
 * @param imu_data 
 * @return error_codes 
 */
error_codes BNO055::readIMU(imu_data_t *imu_data)
{
    __s32 lsbByte;
    __s32 msbByte;
    __s32 res; 

    BNO055::_readByte(&lsbByte, REG_EUL_Pitch_LSB);
    BNO055::_readByte(&msbByte, REG_EUL_Pitch_MSB);

    imu_data->pitch = ((double)((__s16) ((msbByte << 8) + lsbByte))) / 16;

    BNO055::_readByte(&lsbByte, REG_EUL_Roll_LSB);
    BNO055::_readByte(&msbByte, REG_EUL_Roll_MSB);

    imu_data->roll = ((double)((__s16) ((msbByte << 8) + lsbByte))) / 16;

    BNO055::_readByte(&lsbByte, REG_EUL_Heading_LSB);
    BNO055::_readByte(&msbByte, REG_EUL_Heading_MSB);

    imu_data->heading = ((double)((__s16) ((msbByte << 8) + lsbByte))) / 16;

    cout << "-------------------------" << endl;

    cout << "pitch " << imu_data->pitch << endl;
    cout << "roll " << imu_data->roll << endl;
    cout << "heading " << imu_data->heading << endl;

    return NO_ERROR;
}
