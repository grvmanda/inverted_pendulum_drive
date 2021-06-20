

#include "BNO055.h"

using namespace std;

int main (int argc, char *argv[])
{

    BNO055 imuSens(40, 1);

    cout << "initializing driver" << endl;

    int err = imuSens.Init();

    cout << "err value: " << err << endl;
    cout << "err value: " << imuSens.status() << endl;

    // while(1)
    // {

    // }

    return 0;
} 



