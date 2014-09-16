#define BACK 1 
#define LEFT 2 
#define RIGHT 3 
#define STOP 4 
#define FORWARD 0
const char SoP = 'C'; // \ Ideally these would be high ASCII characters and MUST 
const char EoP = 'E'; // / be something that doesn't occur inside of a legal packet! 
const int IDLE = 0; 

const int RW1 = 11; 
const int RW2 = 10; 
const int LW1 = 9; 
const int LW2 = 6; 
const int test = 8; // test point. 


unsigned char inByte; 

int SPEED = 150; 
int c; 
char mode; 

void move(int d){ 
  if(d == FORWARD){ 
    Serial.println(" *Driving fwd*"); 
    digitalWrite(test, HIGH); 
    analogWrite(LW1, IDLE); 
    analogWrite(LW2, SPEED); 
    analogWrite(RW1, IDLE); 
    analogWrite(RW2, SPEED); 
  } 
  else if(d == BACK){ 
    Serial.println(" *Driving back*"); 
    digitalWrite(test, HIGH); 
    analogWrite(LW1, SPEED); 
    analogWrite(LW2, IDLE); 
    analogWrite(RW1, SPEED); 
    analogWrite(RW2, IDLE); 
  } 
  else if(d == LEFT){ 
    Serial.println(" *Turning left* "); 
    digitalWrite(test, HIGH); 
    analogWrite(LW1, IDLE); 
    analogWrite(LW2, SPEED); 
    analogWrite(RW1, SPEED); 
    analogWrite(RW2, IDLE); 
  } 
  else if(d == RIGHT){ 
    Serial.println(" *Turning right* "); 
    digitalWrite(test, HIGH); 
    analogWrite(LW1, SPEED); 
    analogWrite(LW2, IDLE); 
    analogWrite(RW1, IDLE); 
    analogWrite(RW2, SPEED); 
  } 
  else{ 
    Serial.println(" *Not driving* "); 
    digitalWrite(test, LOW); 
    analogWrite(LW1, IDLE); 
    analogWrite(LW2, IDLE); 
    analogWrite(RW1, IDLE); 
    analogWrite(RW2, IDLE); 
  } 

} 

void setup(){ 
  Serial.begin(9600); 
  Serial.println("START"); 
  pinMode(RW1, OUTPUT); 
  pinMode(RW2, OUTPUT); 
  pinMode(LW1, OUTPUT); 
  pinMode(LW2, OUTPUT); 
  pinMode(test, OUTPUT); 

  //Initialize outputs immediately 
  digitalWrite(test, LOW); 
  analogWrite(LW1, IDLE); 
  analogWrite(LW2, IDLE);
  analogWrite(RW1, IDLE); 
  analogWrite(RW2, IDLE); 
  delay(10); 
  Serial.println("Ready, Steady, Go"); 
  delay(10); 
} 


void loop(){ 
  //Waiting for Start of Packet 
  delay(10); // We add these to give the Xbee time to catch up, this 

  // covers all that are followed by a return. 
  while(Serial.available()<1){}; // wait for character 

  inByte = Serial.read(); 
  if(inByte != SoP){ 
    //Not expected Start of Packet, bag 
    Serial.print("Expected SOP, got: "); 
    Serial.write((byte)inByte); 
    Serial.print("\n"); 
    return; 
  } 

  //We've got a legal SoP, move forward. 
  while(Serial.available()<1){}; //wait for next char. 
  inByte = Serial.read(); 
  if(inByte == EoP || inByte == SoP){ 
    Serial.println("SoP/EoP in length field"); 
    return; 
  } 

  //Parse length 
  if(inByte>'5' || inByte<'0'){ // We'll want this larger later! 
    Serial.println("Packet Length out of range"); 
    return; 
  } 


  int packet_size = inByte - '0'; 
  char packet[255]; // Way too big for what we are doing right now... 

  for(int i=0;(i<packet_size) && mode != EoP;i++){ 
    while(Serial.available()<1){}; //wait 
    inByte = Serial.read(); 
    if((inByte == EoP || inByte == SoP)){ 
      Serial.println("SoP/EoP in command field"); 
      return; 
    } 
    packet[i] = (char)inByte; 
    //Serial.println(inByte,BYTE); 
  } 

  packet[packet_size]='\0'; // Null terminate String for later. 

  //Check that packet ends when expected 
  while(Serial.available()<1){}; 

  inByte = Serial.read(); 
  if(inByte != EoP){ 
    Serial.println("EoP not found"); 
    return;
  } 

  // We have a legal packet! 

  //PARSE PACKET 

  if(packet[0] == '1'){ 
    //Move command
    mode=packet[1]; 
  } 
  else if(packet[0] == '2'){ 
    //Display Read 

  } 
  else if(packet[0] == '3'){   
    //Distance Read 

  } 
  else if(packet[0] == '4'){ 
    //Display Write 

    Serial.println(packet); 
    return; 
  } 
  else{ 

    Serial.println("unknown mode"); 
    return; 
  } 

  //Serial.println("Ready"); 
  switch(mode){ 
    case 'q':
    move(STOP);  
      break; 
    case 'B': 
      move(BACK); 
      break; 
    case 'F': 
      move(FORWARD); 
      break; 
    case 'L': 
      move(LEFT); 
      break; 
    case 'R': 
      move(RIGHT); 
      break; 
    default: 
    	if(mode > 48){
    		SPEED = (int)((mode-48)*255/9.0);
    	}
    	else{
      		Serial.println("Unknown command in legal packet"); 
      	}
     	break; 
  } 
} 
