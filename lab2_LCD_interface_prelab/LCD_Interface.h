#pragma once


enum CursorMode{OFF, BLINK, NOTBLINK};

class LCD_Interface{
public:

	//constructor
	 LCD_Interface(){}
	 ~LCD_Interface(){}
	 //intialize the LCD
	 void intiLCD();

	 //clear all display and record
	 void clear();

	 //set the cursor mode
	 void setCursorMode(CursorMode mode);

	 //move cursor to a specific position
	 void moveCursor(int position);

	 //get current cursor position
	 int getCursorPos();

	 //get character codes at certain position
	 int getCharacterCode(int position);

	 //set a character at current cursor position
	 //cursor will automatically move to next
	 bool setChar(char character);
	 //set a character at current cursor position using character code, which will be provided 
	 //cursor will automatically move to next
	 bool setChar(int characterCode);


	 //put a string from current cursor position
	 //cursor will automatically move to next	
	 bool setString(char[] string);
	 //put a string from current cursor position using character code
	 //cursor will automatically move to next	
	 bool setString(int[] characterCodes);



private:
	 /*some lower level functions which will be called in upper level functions*/
	 //to to a DDRAM address
	 //void goTo(unsigned address);
	 //int[16] characterCodes = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	 //record the current cursor position
	int cursorPosition;
}