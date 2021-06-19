#ifndef _BNO055
#define _BNO055

#include <stdlib.h>
#include <cstdio>
#include <fstream>

// extern "C" {
    #include <linux/i2c-dev.h>
    #include <sys/ioctl.h>
    
#include <stddef.h>
#include <fcntl.h> 
#include <unistd.h> 
// }

class BNO055 {
    
    private:
        int _addr;
        int _devId;
        int _drvStatus;

        int _init();
        void _readData();

    public:        
        
        BNO055(int addr, int devID);
        int Init();
        int status();
        // vector<int> readIMU(void); 


};



#endif