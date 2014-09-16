
#define LCD_IDLE B00110000
#define LCD_8BIT_2LINE_8HEIGHT B00111000
#define LCD_DSP_ON_CURSOR_OFF B00001100
#define LCD_CLR_DSP B00000001
#define LCD_MOVE_R_NO_SHIFT B00000110
int LCD_RS = 9;
int LCD_RW = 8;
int LCD_E = 10;



void setup(){
  initLCD();
}

void loop(){
}


//initialize the LCD and MCU
void initLCD(){
  DDRD = B11111111;
  DDRB |= B00000111;
  
  PORTD = B00000000;
  PORTB = B00000000;
  
  delayMicroseconds(15);
  digitalWrite(LCD_RS, LOW);
  DDRD = LCD_IDLE;
  delayMicroseconds(5);
  DDRD = LCD_IDLE;
  delayMicroseconds(100);
  DDRD = LCD_IDLE;
  delayMicroseconds(5);
  DDRD = LCD_IDLE;
  delayMicroseconds(100);
  putData(LCD_8BIT_2LINE_8HEIGHT);
  delayMicroseconds(40);
  putData(LCD_DSP_ON_CURSOR_OFF);
  delayMicroseconds(40);
  putData(LCD_CLR_DSP);
  delayMicroseconds(5);
  putData(LCD_MOVE_R_NO_SHIFT);
}

//put the data onto ports and use enable bit to write/read data
void putData(unsigned char data){
  digitalWrite(LCD_E, HIGH);
  DDRD = data;
  digitalWrite(LCD_E, LOW);
}

//go to DDRAM
void gotoDDRAM(unsigned char addr){
  digitalWrite(LCD_RS, LOW);
  delayMicroseconds(1);
  putData(0x80|addr);
  delayMicroseconds(37);
}
