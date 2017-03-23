#ifndef CtrlApp_h
#define CtrlApp_h
#include "Arduino.h"
#include <inttypes.h>
#include <SoftwareSerial.h>

class CtrlApp
{
  public:
    CtrlApp(HardwareSerial &uart, uint32_t baud = 9600);

    float getJoyX(void);
    float getJoyY(void);
    float getGravX(void);
    float getGravY(void);
    
    void sendWave(float value1,float value2,float value3);

    void begin(void);
    void routine(void);

  private:
  	HardwareSerial *m_puart;
    char comdata[100], data_p; 
    float Joy_x,Joy_y,Grav_x,Grav_y;
    float wave_data[3];
    uint32_t _baud;
    bool _valid;
};

#endif
