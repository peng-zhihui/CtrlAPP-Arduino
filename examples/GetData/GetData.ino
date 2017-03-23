/*******************************************
  一个个人小项目，配套APP下载以及相关教程见
  http://www.arduino.cn/thread-43090-1-1.html
*******************************************/
#include <CtrlApp.h>

CtrlApp obj((HardwareSerial&)Serial, 9600);  //实例化检测对象

float Joy_x, Joy_y, Grav_x, Grav_y;
float a, b, c, angle;

void setup()
{
  obj.begin();      //初始化，后面不需要再用Serial.begin()
}

void loop()
{
  obj.routine();    //尽可能让这一句频繁运行

  //获取遥控数据，分别为摇杆和重力感应
  Joy_x = obj.getJoyX();
  Joy_y = obj.getJoyY();
  Grav_x = obj.getGravX();
  Grav_y = obj.getGravY();

  //制造一堆正弦波数据用于波形显示
  angle += 5;
  if (angle == 360)
    angle = 0;
  a = 100 * sin(angle / 180.0 * PI);
  b = 100 * sin((angle + 90) / 180.0 * PI);
  c = 100 * sin((angle + 180) / 180.0 * PI);

  obj.sendWave(a, b, c);  //发送到手机显示波形，参数为三个通道数据

  delay(50);
}