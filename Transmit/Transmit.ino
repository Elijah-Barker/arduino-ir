void setup() {
	// initialize digital pin 13 as an output.
	pinMode(13, OUTPUT);
}

void loop()
{
	// put your main code here, to run repeatedly:

	//delay (200);

//  const int CYCLES_MULTIPLE = 23;
//  const int CYCLES_TRUE = CYCLES_MULTIPLE*2;
//  const int CYCLES_FALSE = CYCLES_MULTIPLE;
//
//
//while (true)
//{
//  
//      transmit_cycles(CYCLES_TRUE, true);
//
//      transmit_cycles(CYCLES_FALSE, true);
//      delay(1000);
//      
//}
	int i = 0;
	for(i=0;i<256;i++)
	{
		transmit_byte('V');
		delay(100);
	}
	delay(1000);
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
		if((unsigned char)data<<j>>7)
		{
			transmit_cycles(CYCLES_TRUE, true);
		}
		else
		{
			transmit_cycles(CYCLES_FALSE, true);
		}
	}
	
	transmit_cycles(CYCLES_HEADER, false);
}

