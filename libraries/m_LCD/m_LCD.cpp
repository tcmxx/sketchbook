
#include "m_LCD.h"
#include <Arduino.h>
		LCD::LCD(){};
		//Initialize the LCD. Screen will be cleaned. Curson will be at psotion 0. Cursor Mode is CURSOR_ON 
		
		//the eightBus is false, the order of ports is: RS, RW, E, DB0~DB8.
		//if the eightBus is true, the order of ports is: RS, RW, E, DB4~DB7.
		void LCD::initializaton(int port[],bool eightBus){
			busMode = eightBus;

			RS = port[0];
			RW = port[1];//
			E = port[2];

			if(eightBus == 1){
				DB0 = port[3];
				DB1 = port[4];
				DB2 = port[5];
				DB3 = port[6];
				DB4 = port[7];
				DB5 = port[8];
				DB6 = port[9];
				DB7 = port[10];
				
				pinMode(RW, OUTPUT);
				pinMode(RS, OUTPUT);
				pinMode(E,  OUTPUT);
				
				pinMode(DB0, OUTPUT);
				pinMode(DB1, OUTPUT);
				pinMode(DB2, OUTPUT);
				pinMode(DB3, OUTPUT);
				pinMode(DB4, OUTPUT);
				pinMode(DB5, OUTPUT);
				pinMode(DB6, OUTPUT);
				pinMode(DB7, OUTPUT);
			  
				delay(15);
				cmdWrite(B00110000);
				delay(5);
				cmdWrite(B00110000);
				delayMicroseconds(100);
				cmdWrite(B00110000);
				delay(5);
				//Function Set
				cmdWrite(0x38);//8 bit interface, 2 lines, 5*8 dots
				delayMicroseconds(40);
				//Display on
				cmdWrite(B00001111);//Display on, cursor off, blink off
				delayMicroseconds(40);
				//Display clear
				cmdWrite(0x01);
				delayMicroseconds(40);
				//EntryMode set
				cmdWrite(0x06);// Move Direction= inc,no display shift
				delayMicroseconds(2000);
			}else{
								
				DB4 = port[3];
				DB5 = port[4];
				DB6 = port[5];
				DB7 = port[6];
				
				pinMode(RW, OUTPUT);
				pinMode(RS, OUTPUT);
				pinMode(E,  OUTPUT);
				
				pinMode(DB4, OUTPUT);
				pinMode(DB5, OUTPUT);
				pinMode(DB6, OUTPUT);
				pinMode(DB7, OUTPUT);
			  
				delay(15);
				cmdWrite4(B00110000);
				delay(5);
				cmdWrite4(B00110000);
				delayMicroseconds(100);
				cmdWrite4(B00110000);
				delay(5);
				//Function Set
				cmdWrite(0x28);//8 bit interface, 2 lines, 5*8 dots
				delayMicroseconds(40);
				//Display on
				cmdWrite(B00001111);//Display on, cursor off, blink off
				delayMicroseconds(40);
				//Display clear
				cmdWrite(0x01);
				delayMicroseconds(40);
				//EntryMode set
				cmdWrite(0x06);// Move Direction= inc,no display shift
				delayMicroseconds(2000);
			}

			curCurMode = CURSOR_ON;
		};
		//See whether LCD is in busy mode
		//bool LCD::isBusy(){}; 

		//Clean the LCD desplay
		void LCD::cleanDisplay(){
			cmdWrite(LCD_CLR_DSP);
			
			delay(2);
		}

		
		void  LCD::displayOn(){
			setCursorMode(curCurMode);
		};
		void  LCD::displayOff(){
			cmdWrite(LCD_DSP_OFF);
		};
		
		
		
		//Set mode of the cursor
		void LCD::setCursorMode(CURSOR_MODE cursorMode){
			curCurMode = cursorMode;
			switch(cursorMode){
			CURSOR_ON:
				cmdWrite(B00001110);
				break;
			CURSOR_OFF:
				cmdWrite(B00001100);
				break;
			CURSOR_BLINK:
				cmdWrite(B00001111);
				break;
			default:
				cmdWrite(B00001100);
				break;
			}
			delayMicroseconds(40);
		}

		//Set address of the cursor. 
		//Only address 0-0x13 for line 1 and 0x40- 0x53 for line 2 are visible on LCD. 0x14-0x27, 0x54-0x67 are hidden and other address are invalid
		void LCD::setCursorPostion(uint_8 address){
			cmdWrite(0x80|address);
			delayMicroseconds(40);
		}
		void LCD::setCursorPostion(uint_8 line, uint_8 pos){
			if (line>2 || pos>0x40)
				return;
			unsigned char address = line*0x40 + pos;
			setCursorPostion(address);
		};
		
		//write a character at current currsor postion
		//The character  wriiten is decided by CGROM address
		void LCD::charWrite(char c){
			dataWrite(c);
			delayMicroseconds(40);
		};

	

		//Write a string onto LCD starting current postion
		void LCD::stringWrite(char s[]){
			//unsigned char DDRAM;
			for(int i = 0; s[i] != '\0'; i++){
				charWrite(s[i]);
			}
		}

		void  LCD::topLineWrite(char s[], int startCol){
			setCursorPostion(0, startCol);
			for(int i = 0; s[i] != '\0' && i + startCol< 48; i++){
				charWrite(s[i]);
			}
		};

		void  LCD::bottomLineWrite(char s[], int startCol){
			setCursorPostion(1, startCol);
			for(int i = 0; s[i] != '\0' && i + startCol< 48; i++){
				charWrite(s[i]);
			}
		};

		void  LCD::defineChar(int num, uint_8 data[]){
	  		unsigned char addr = 0x40;
	  		if(num<0 || num >7) return;
			for(int i = 0; i < num; i++){
				addr = addr + 0x08;
			}

	  		cmdWrite(addr);
	  		delayMicroseconds(50); 
	  		charWrite(0x1F&data[0]); 
	  		charWrite(0x1F&data[1]); 
	  		charWrite(0x1F&data[2]); 
	  		charWrite(0x1F&data[3]); 
	  		charWrite(0x1F&data[4]); 
	  		charWrite(0x1F&data[5]); 
	  		charWrite(0x1F&data[6]); 
	  		//charWrite(0x00000000); 
	  		delayMicroseconds(50);
		};

		void LCD::cmdWrite(unsigned char cmd){
			if(busMode == 1){
				 digitalWrite(RS,0);
				 digitalWrite(RW,0);
				 digitalWrite(E,1);
				 
				 digitalWrite(DB0, (0x01<<0&cmd)>0);
				 digitalWrite(DB1, (0x01<<1&cmd)>0);
				 digitalWrite(DB2, (0x01<<2&cmd)>0);
				 digitalWrite(DB3, (0x01<<3&cmd)>0);
				 digitalWrite(DB4, (0x01<<4&cmd)>0);
				 digitalWrite(DB5, (0x01<<5&cmd)>0);
				 digitalWrite(DB6, (0x01<<6&cmd)>0);
				 digitalWrite(DB7, (0x01<<7&cmd)>0);
				 
				 digitalWrite(E,0);
			}else{
				 digitalWrite(RS,0);
				 digitalWrite(RW,0);
				 digitalWrite(E,1);
				 
				 digitalWrite(DB4, (0x01<<4&cmd)>0);
				 digitalWrite(DB5, (0x01<<5&cmd)>0);
				 digitalWrite(DB6, (0x01<<6&cmd)>0);
				 digitalWrite(DB7, (0x01<<7&cmd)>0);
				 digitalWrite(E,0);
				 //delayMicroseconds(20);
				 digitalWrite(E,1);
				 digitalWrite(DB4, (0x01<<0&cmd)>0);
				 digitalWrite(DB5, (0x01<<1&cmd)>0);
				 digitalWrite(DB6, (0x01<<2&cmd)>0);
				 digitalWrite(DB7, (0x01<<3&cmd)>0);
				 
				 digitalWrite(E,0);
			}
		}

		//cmdWrite4(unsigend char)
		//write only 4 MSB bits of input to LCD bus
		//cmd: cmd to write
		void LCD::cmdWrite4(unsigned char cmd){
				 digitalWrite(RS,0);
				 digitalWrite(RW,0);
				 digitalWrite(E,1);
				 
				 digitalWrite(DB4, (0x01<<4&cmd)>0);
				 digitalWrite(DB5, (0x01<<5&cmd)>0);
				 digitalWrite(DB6, (0x01<<6&cmd)>0);
				 digitalWrite(DB7, (0x01<<7&cmd)>0);
				 digitalWrite(E,0);
		}


		void LCD::dataWrite(unsigned char data)
		{
			if(busMode == 1){
				 digitalWrite(RS,1);
				 digitalWrite(RW,0);
				 digitalWrite(E,1);
				 
				 digitalWrite(DB0, (0x01<<0&data)>0);
				 digitalWrite(DB1, (0x01<<1&data)>0);
				 digitalWrite(DB2, (0x01<<2&data)>0);
				 digitalWrite(DB3, (0x01<<3&data)>0);
				 digitalWrite(DB4, (0x01<<4&data)>0);
				 digitalWrite(DB5, (0x01<<5&data)>0);
				 digitalWrite(DB6, (0x01<<6&data)>0);
				 digitalWrite(DB7, (0x01<<7&data)>0);
				 
				 digitalWrite(E,0);
			}else{
				 digitalWrite(RS,1);
				 digitalWrite(RW,0);
				 digitalWrite(E,1);
				 
				 digitalWrite(DB4, (0x01<<4&data)>0);
				 digitalWrite(DB5, (0x01<<5&data)>0);
				 digitalWrite(DB6, (0x01<<6&data)>0);
				 digitalWrite(DB7, (0x01<<7&data)>0);
				 digitalWrite(E,0);
				 //delayMicroseconds(20);
				 digitalWrite(E,1);
				 digitalWrite(DB4, (0x01<<0&data)>0);
				 digitalWrite(DB5, (0x01<<1&data)>0);
				 digitalWrite(DB6, (0x01<<2&data)>0);
				 digitalWrite(DB7, (0x01<<3&data)>0);
				 
				 digitalWrite(E,0);
			}
		}

		


		bool LCD::isBusy(){
			digitalWrite(RS,0);
			digitalWrite(RW,1);
			pinMode(DB7, INPUT);
			int val = digitalRead(DB7);
			pinMode(DB7, OUTPUT);
			if(val == HIGH){
				return true;
			}else{
				return false;
			}
		}