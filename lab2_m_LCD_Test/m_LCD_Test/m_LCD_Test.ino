
#include <m_LCD.h>


LCD mLCD;
unsigned char c1[] = {0x00, 0x7e, 0x3c, 0x18, 0x18, 0x3c, 0x7e};
unsigned char c2[] = {0x00, 0x00, 0x3c, 0x18, 0x18, 0x3c, 0x00};
unsigned char c3[] = {0xff, 0x7e, 0x3c, 0x18, 0x18, 0x00, 0x00};
unsigned char c4[] = {0xff, 0x7e, 0x3c, 0x18, 0x00, 0x00, 0x00};
unsigned char c5[] = {0xff, 0x7e, 0x3c, 0x00, 0x00, 0x00, 0x00};
unsigned char c6[] = {0xff, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char c7[] = {0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char c8[] = {0x00, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00};
void setup(){
  int port[] = {12,8, 7, 2, 3, 4, 5};
  mLCD.initializaton(port, 0);
  
   //mLCD.setCursorMode(CURSOR_BLINK);
  
  mLCD.defineChar(0, c1);
  mLCD.defineChar(1, c2);
  mLCD.defineChar(2, c3);
  mLCD.defineChar(3, c4);
  mLCD.defineChar(4, c5);
  mLCD.defineChar(5, c6);
  //mLCD.defineChar(6, c7);
  //mLCD.defineChar(7, c8);
}

void loop(){
  
  char le[] = "123456789123456789123456789123456789"; 
  char le2[] = "Boomba!";
  char le3[] = "Zigbee 4ever"; 
  mLCD.cleanDisplay();

  mLCD.displayOn();
  mLCD.setCursorPostion(0x00);
 
  
  
  mLCD.charWrite(0x00);
  mLCD.charWrite(0x01);
  mLCD.charWrite(0x02);
  mLCD.charWrite(0x03);


  mLCD.stringWrite(le2);

  delay(20000);
  
}
