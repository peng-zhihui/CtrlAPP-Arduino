#include "CtrlApp.h"

CtrlApp::CtrlApp(HardwareSerial &uart, uint32_t baud): m_puart(&uart)
{
  _baud = baud;
  
  wave_data[0]=0;
  wave_data[1]=0;
  wave_data[2]=0;
}


void CtrlApp::begin(void)
{
  m_puart->begin(_baud);
  while (m_puart->available() > 0)
  {
    m_puart->read();
  }
}


void CtrlApp::routine(void)
{
  while (m_puart->available() > 0)
  {
    char nullByte = char(m_puart->read());
    if (nullByte == ';')
    {
      comdata[data_p] = nullByte;
      data_p = 0;

      if ((char)comdata[1] == 'J')
      {
        strtok(comdata, ",");
        Joy_x = atof(strtok(NULL, ","));
        Joy_y = atof(strtok(NULL, ","));
      }
      else if ((char)comdata[1] == 'M')
      {
        strtok(comdata, ",");
        Grav_x = atof(strtok(NULL, ","));
        Grav_y = atof(strtok(NULL, ","));
      }
      else 
      {
      	Joy_x = 0;
        Joy_y = 0;
        Grav_x= 0;
        Grav_y= 0;
      }
    }
    else
    {
      comdata[data_p] = nullByte ;
      data_p++ ;
    }
  }
}

float CtrlApp::getJoyX(void)
{
  return Joy_x;
}

float CtrlApp::getJoyY(void)
{
  return Joy_y;
}

float CtrlApp::getGravX(void)
{
  return Grav_x;
}

float CtrlApp::getGravY(void)
{
  return Grav_y;
}

void CtrlApp::sendWave(float value1,float value2,float value3)
{
	wave_data[0] = value1;
  wave_data[1] = value2;
  wave_data[2] = value3;
	m_puart->print("V,");
  m_puart->print(wave_data[0]);
  m_puart->print(",");
  m_puart->print(wave_data[1]);
  m_puart->print(",");
  m_puart->println(wave_data[2]);

    delay(5);
}


