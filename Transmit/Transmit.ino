#include <Servo.h>
#define SERVO_PIN 3
Servo aimservo;
void tx_ec(int m);
void setup() {
	// initialize digital pin 13 as an output.
	pinMode(13, OUTPUT);
	aimservo.attach(SERVO_PIN);

}
void aim(int v){
	static int cv=0;
	if(v>cv)
		cv+=2;
	else if(v<cv)
		cv-=2;
	aimservo.write(cv);
}

void loop()
{
	// put your main code here, to run repeatedly:
	int i = 0;
	const int min = 20;
	const int max =120;
	/*for(i=0;i<256;i++)
	{
		aim(i);
		transmit_byte(i);
		delay(100);
	}*/
	while(1){
		for(i=min;i<max;i++){
			aim(i);
			tx_ec(i);
			delay(25);
		}
		for(i=max;i>min;i--){
			aim(i);
			tx_ec(i);
			delay(25);
		}
	}

	delay(1000);
}
void tx_ec(int m){
	transmit_byte(m);
	transmit_byte(m);
	transmit_byte(m);

}

void transmit_cycles(int cycles, bool send_signal)
{
  int i=0;
	//send the cycles
	for(i=0;i<cycles;i++)
	{
    if(send_signal)digitalWrite(13, HIGH);
		delayMicroseconds(13);
		digitalWrite(13, LOW);
		delayMicroseconds(13);
	}
	//wait ten cycles before transmitting
	for(i=0;i<20;i++)
	{
		delayMicroseconds(13);
	}
}

void transmit_byte(unsigned char data)//little endian transmission of a byte 
{
	const int CYCLES_MULTIPLE = 23;
	const int CYCLES_HEADER = CYCLES_MULTIPLE*4;
	const int CYCLES_TRUE = CYCLES_MULTIPLE*2;
	const int CYCLES_FALSE = CYCLES_MULTIPLE;
	int i=0;

	transmit_cycles(CYCLES_HEADER, true);

	int j=0;
	for(;j<8;j++)
	{
	  //int mybit = data<<j>>7;//doesn't work

    int mybit = data%2;
    data = data/2;
    
		if(mybit)
		{
			transmit_cycles(CYCLES_TRUE, true);
		}
		else
		{
			transmit_cycles(CYCLES_FALSE, true);
		}
	}
	
	transmit_cycles(CYCLES_HEADER, false);

  delay(5);
}

