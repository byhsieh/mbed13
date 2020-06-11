#include "mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"

Ticker servo_ticker;
PwmOut pin9(D9), pin8(D8);
Serial xbee(D12, D11);
BBCar car(pin8, pin9, servo_ticker);

// just wait for rpc call from the xbee!
int main(void) 
{
    // for D8
    double pwm_table0[] = {-150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 150};
    double speed_table0[] = {-15.790, -15.312, -13.876, -11.005, -5.184, 0.000, 5.184, 11.005, 13.876, 15.312, 15.790};
    
    // for D9
    double pwm_table1[] = {-150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 150};
    double speed_table1[] = {-15.711, -15.152, -13.797, -10.447, -4.865, 0, 4.865, 10.447, 13.797, 15.152, 15.711};

    // first and fourth argument : length of table
    car.setCalibTable(11, pwm_table0, speed_table0, 11, pwm_table1, speed_table1);
    
    char buf[256], outbuf[256];
    
    while (1) {
        for (int i = 0; ; i++) {
            buf[i] = xbee.getc();
            if (buf[i] == '\n') 
                break;
        }

        RPC::call(buf, outbuf);
        xbee.printf("%s\r\n", outbuf);

    }
}