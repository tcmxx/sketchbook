//Author: Xiaoxiao Ma, Yi Cui
//Date  : Sept 16, 2014

#ifndef LCD_H
#define LCD_H

#define uint_8 unsigned char
enum CURSOR_MODE { CURSOR_ON, CURSOR_OFF, CURSOR_BLINK};


//LCD class serving as interface for HD44780 LCD on Arduino platform
//Call initialization(int[], bool) before use
//all printable characters supported, check HD44780 datasheet for other characters. You can define charater if not in the CGROM
//All functions are called involves certain amount of delay. Make sure your application could afford that before function call
//Calling such functions in ISR is a bad idea 
//cleanDisplay() and cursorHome() delay 2ms, other cmd delay 40us

class LCD{
	public:
		//Predefined LCD Commands: 
		const static uint_8 LCD_8BIT_2LINE = 0x38;
		const static uint_8 LCD_DSP_ON_CRS_OFF_BLK_OFF = 0x0C;
		const static uint_8 LCD_CLR_DSP = 0x01;
		const static uint_8 LCD_DSP_OFF = 0x08;

		//LCD()
		//Class Construcator function. Do nothing and should not be call
		//Input		 void
		//Return	 void
		LCD();

		//initialization(int,bool)
		//Initialize the LCD. Screen will be cleaned. Curson will be at psotion 0. Cursor Mode is CURSOR_ON 
		//port: pin numbers of Arduino ports used to interface LCD
		//		In eightBus mode,the order of ports is: RS, RW, E, DB0~DB7; In fourBus mode, the order of ports is: RS, RW, E, DB4~DB7
		//eightBUs: 1 eightBus mode, 0 fourBus mode
		void initializaton(int port[],bool eightBus);
		
		//See whether LCD is in busy mode
		//bool isBusy(); 

		//displayOn()
		//Turn on LCD display
		//Input		 void
		//Return	 void		
		void displayOn();

		//displayOff()
		//Turn off LCD display
		//Input		 void
		//Return	 void	
		void displayOff();
		
		//cleanDisplay()
		//Clean the LCD desplay
		//Input		 void
		//Return	 void	
		void cleanDisplay();

		//setCursorMode(CURSOR_MODE)
		//Set mode of the cursor
		//cursorMode: could be one of {CURSOR_ON, CURSOR_OFF, CURSOR_BLINK}
		void setCursorMode(CURSOR_MODE cursorMode);

		//setCursorPosition(uint_8)
		//Set address of the cursor. (In our interface design, cursor position is just the postion to be written for next character.) 
		//Note: Only address 0-0x13 for line 1 and 0x40- 0x53 for line 2 are visible on LCD. 0x14-0x27, 0x54-0x67 are hidden and other address are invalid
		//address: Desired cursor position (DDRAM address) 
		void setCursorPostion(uint_8 address);
		//setCursorPosition(uint_8,pos)
		//Set position of the cursor
		//line: line number of desired cursor position(1 or 2)
		//pos:  position (from left to right) of desired cursor position in that line (0 - 0x39)
		void setCursorPostion(uint_8 line, uint_8 pos);
		//cursorHome()
		//Set position of the cursor to home(Upper left corner) and return any shift
		void cursorHome();

		//shiftDisplayLeft()
		//Shift all display left(Both lines with cursor)
		void shiftDisplayLeft();

		//shiftDisplayRight()
		//Shift all display right(Both lines with cursor)
		void shiftDisplayRight();
		//shiftCursorLeft()
		//Shift the cursor left
		void shiftCursorLeft();

		//shiftCursorRight()
		//Shift the cursor right
		void shiftCursorRight();

		//dispLeftToRight()
		//set the display mode to be from left to right, which means the cursor position will automatically move to left by one after each write of character
		void dispLeftToRight();

		//dispRightToLeft()
		//set the display mode to be from right to left, which means the cursor position will automatically move to right by one after each write of character
		void dispRightToLeft();

		//charWrite(char)
		//write a character at current currsor postion
		//c: the desired character to be written. If c is a printable char, show it. If not a printable char, showing corresponding character in CGROM. 
		void charWrite(char c);
		
		//stringWrite(char[])
		//Write a string onto LCD starting current postion
		//s: string to be written. s should end with '\0'
		void stringWrite(char s[]);
		
		//topLineWrite(char[], int )
		//Write string onto LCD top line. Long String will be trimmed and won't show on second line
		//s: string to show on top line
		//startCol: start position(left to right) of string
		void topLineWrite(char s[], int startCol);

		//bottomLineWrite(char[], int )
		//Write string onto LCD bottom line. Long String will be trimmed and won't show on second line
		//s: string to show on bottom line
		//startCol: start position(left to right) of string
		void bottomLineWrite(char s[], int startCol);
		
		//defineChar(num,data)
		//Define a customized character and store in CGRAM (only support first 8 positons in CGROM)
		//num: 0-7, address of customized char. 
		//data: Pattern of user defined char.
		//		data should be a 7 bytes long array, each array entry corresponds to one line of charater going into CGRAM. To use the defined char, use the your input num as the parameter to represent the character in charWrite(char) or stringWrite(char[] )
		void defineChar(int num, uint_8 data[]);
		


	private:
		//cmdWrite(unsigned char)
		//write cmd to LCD
		//cmd: cmd code
		void cmdWrite(unsigned char cmd);

		//dataWrite(unsigned char)
		//write data to LCD
		//data: data to bw written
		void dataWrite(unsigned char data);


		void cmdWrite4(unsigned char cmd);

		bool isBusy();

		//busMode: 1 eightBus mode；0 fourBus mode
		bool busMode;
		//RW: 1 Read, 0 write
		int RW;
		//RS: 1 write as data; 0 write as command
		int RS;
		//E: Enable 
		int E;
		//DB7-DB0: data bus ports
		int DB0;
		int DB1;
		int DB2;
		int DB3;
		int DB4;
		int DB5;
		int DB6;
		int DB7;
		//current cursor Mode
		CURSOR_MODE curCurMode;
		//void gotoDDRAM(uint_8 addr);
};


#endif