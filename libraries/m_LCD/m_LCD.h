
#ifndef LCD_H
#define LCD_H

#define uint_8 unsigned char
//#define RW 8
//#define RS 9
//#define E  10
//#define DB PORTD
//#define busyBit 7
enum CURSOR_MODE { CURSOR_ON, CURSOR_OFF, CURSOR_BLINK};

class LCD{
	public:

		const static uint_8 LCD_8BIT_2LINE = 0x38;
		const static uint_8 LCD_DSP_ON_CRS_OFF_BLK_OFF = 0x0C;
		const static uint_8 LCD_CLR_DSP = 0x01;
		const static uint_8 LCD_DSP_OFF = 0x08;

		LCD();
		//Initialize the LCD. Screen will be cleaned. Curson will be at psotion 0. Cursor Mode is CURSOR_ON 
		//if the eightBus is false, the order of ports is: RS, RW, E, DB0~DB7.
		//if the eightBus is true, the order of ports is: RS, RW, E, DB4~DB7.
		void initializaton(int port[],bool eightBus);
		
		//See whether LCD is in busy mode
		//bool isBusy(); 

		void displayOn();
		void displayOff();
		
		//Clean the LCD desplay
		void cleanDisplay();

		//Set mode of the cursor
		void setCursorMode(CURSOR_MODE cursorMode);

		//Set address of the cursor. 
		//Only address 0-0x13 for line 1 and 0x40- 0x53 for line 2 are visible on LCD. 0x14-0x27, 0x54-0x67 are hidden and other address are invalid
		void setCursorPostion(uint_8 address);
		void setCursorPostion(uint_8 line, uint_8 pos);
		

		//write a character at current currsor postion
		//The character  wriiten is decided by CGROM address
		void charWrite(char c);
		
		//Write a string onto LCD starting current postion
		void stringWrite(char s[]);
		
		void topLineWrite(char s[], int startCol);
		void bottomLineWrite(char s[], int startCol);
		void defineChar(int num, char data[]);
		


	private:
		
		void cmdWrite(unsigned char cmd);
		void dataWrite(unsigned char data);
		void cmdWrite4(unsigned char cmd);
		bool isBuzy();
		bool busMode;
		
		int RW;
		int RS;
		int E;
		int DB0;
		int DB1;
		int DB2;
		int DB3;
		int DB4;
		int DB5;
		int DB6;
		int DB7;

		CURSOR_MODE curCurMode;
		//void gotoDDRAM(uint_8 addr);
};


#endif