/*
Testbenches for a 7-segment 4-digit led display
Spyros Seimenis 26/1/2013

Data sheet for multiplexed LED display:
http://dlnmh9ip6v2uc.cloudfront.net/datasheets/Components/LED/1LEDREDCC.pdf

Using the shift register:
http://www.codeproject.com/KB/system/ArduinoShiftRegisters/SingleShiftRegister_small.jpg

I am using only a shift register, 8 x 220Ω resistors and the led display with an arduino UNO
Each digit of my display is activated by pulling to LOW each pin.

In this version i write each time a data array and not digit by digit, 
it makes more complicated the pattern testbench though

*/
int dataPin = 2;     		// Define which pins will be used for the Shift Register control
int latchPin = 3;
int clockPin = 4;
int digit[4] = {11,10,9,8};	// The digit control
int pot = 5;

int data[5] = {0,0,0,0};	//data holds the displayed text each time

/* Used in the various testbenches */
/* The easiest number mapping out there!! for led in order DP.G.F.E.D.C.B.A */
int number[10] = {63,6,91,79,102,109,125,7,127,111}; 

/* only one segment , seg[0] is off*/
int seg[9] = {0,1,2,4,8,16,32,64,128};

int pattern[12] = {1,10,100,1000,6000,5000,4000,400,40,4,3,2};

int counter=0;
long beginTime;

void setup()
{
    pinMode(dataPin, OUTPUT);       //Configure each IO Pin
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(digit[0], OUTPUT);		//The digit pins
    pinMode(digit[1], OUTPUT);
    pinMode(digit[2], OUTPUT);
    pinMode(digit[3], OUTPUT);
    
  /* Initialize digits */
  for (int i = 0; i<4; i++)
    digitalWrite(digit[i], HIGH);
    
   /* For the timer testbench */
   beginTime = millis();
   
   //Serial.begin(9600);
    
}

void loop()
{   
	//timer();
	patternr();
}

/* Pattern testbench */
void patternr()
{
	if ( millis() - beginTime > analogRead(pot))
	{
		counter++;
		if (counter==12)counter=0;
		patternToData(counter);		
		beginTime = millis();
	}
	display();
}

/* Converts the counter to a 4 digit data array */
void patternToData(int counter){
  data[3] = seg[pattern[counter]%10];
  data[2] = seg[pattern[counter]%100/10];
  data[1] = seg[pattern[counter]%1000/100];
  data[0] = seg[pattern[counter]%10000/1000];
}

/* Converts the counter to a 4 digit data array */
void numberToData(int counter){
  data[3] = number[counter%10];
  data[2] = number[counter%100/10];
  data[1] = number[counter%1000/100];
  data[0] = number[counter%10000/1000];
}

/* Timer testbench */
void timer()
{
	if ( millis() - beginTime > analogRead(pot))
	{
		//Serial.println(analogRead(pot));
		counter++;
   	 	if (counter>9999)counter=0;
		numberToData(counter);
		beginTime = millis();
	}
	display();
}



/* Displays the content of the data array */
void display()
{
	for (int i = 0; i<4; i++)
	{
		/* Enable digit from leftmost */
		digitalWrite(digit[i], LOW);

		digitalWrite(latchPin, LOW);                     		//Pull latch LOW to start sending data
  		shiftOut(dataPin, clockPin, MSBFIRST, data[i]);  		//Send the data	
 		digitalWrite(latchPin, HIGH);                     		//Pull latch HIGH to stop sending data  
 		
 		delayMicroseconds(1000);
 		
 		/* Power off all segments to prevent flickering */
		digitalWrite(latchPin, LOW);
  		shiftOut(dataPin, clockPin, MSBFIRST, seg[0]);
 		digitalWrite(latchPin, HIGH);
 		
 		/* Disable digit */
 		digitalWrite(digit[i], HIGH);
  	}
}
 
