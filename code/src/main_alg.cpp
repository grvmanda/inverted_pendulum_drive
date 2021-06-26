/**
 * @file main_alg.cpp
 * @author Gaurav Manda (grvmanda@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2021-06-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "BNO055.h"
#include<unistd.h>

using namespace std;

int main (int argc, char *argv[])
{

    BNO055 imuSens(40, 1);

    cout << "initializing driver" << endl;

    int err = imuSens.Init();

    cout << "err value: " << err << endl;
    cout << "err value: " << imuSens.status() << endl;

    imu_data_t data;
    while (1)
    {
        usleep(1000000);//sleeps for 3 second
        imuSens.readIMU(&data);
    }

    return 0;
} 



