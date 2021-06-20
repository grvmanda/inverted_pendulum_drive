
#include "BNO055.h"

using namespace std;


/**
 * @brief initialize the I2C driver
 * 
 * @return int 
 */
int BNO055::_init()
{
    char filename[20];
    int error = 0;

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
        this->_drvStatus = -2;
        return -1;
    }   

    this->_drvStatus = 0;

    /* Read out BTL version number for sanity check */
    __s32 res; 
    res = i2c_smbus_read_byte_data(this->_file, REG_BL_Rev_ID);
    if (res < 0) {
    /* ERROR HANDLING: i2c transaction failed */
    } else {
        cout << "BTL ID " << res << endl;
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
 * @return vector<int> 
 */
void BNO055::readIMU()
{
    __u8 reg = 0x10;
    __s32 res; 
    /* Using SMBus commands */
    res = i2c_smbus_read_word_data(this->_file, reg);
    if (res < 0) {
    /* ERROR HANDLING: i2c transaction failed */
    } else {
        cout << "IMU Data: " << res << endl;
    }
}
