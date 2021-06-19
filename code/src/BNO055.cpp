
#include "BNO055.h"

using namespace std;


/**
 * @brief initialize the I2C driver
 * 
 * @return int 
 */
int BNO055::_init()
{
    int file;
    char filename[20];
    int error = 0;

    snprintf(filename, 19, "/dev/i2c-%d", this->_devId);
    file = open(filename, O_RDWR);
    if (file < 0) {
    /* ERROR HANDLING; you can check errno to see what went wrong */
        this->_drvStatus = -1;
        return -1;
    }

    if (ioctl(file, I2C_SLAVE, this->_addr) < 0) {
    /* ERROR HANDLING; you can check errno to see what went wrong */
        this->_drvStatus = -2;
        return -1;
    }   

    this->_drvStatus = 0;
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
 * @return vector<int> 
 */
// vector<int> readIMU()
// {
//     /* Using SMBus commands */
//     res = i2c_smbus_read_word_data(file, reg);
//     if (res < 0) {
//     /* ERROR HANDLING: i2c transaction failed */
//     } else {
//     /* res contains the read word */
//     }
// }
