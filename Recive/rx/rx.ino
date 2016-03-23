#define RX_PIN 2
#define CYCLE_LEN 13
#define  CYCLES_MULTIPLE  23
#define  CYCLES_HEADER  CYCLES_MULTIPLE*4
#define CYCLES_TRUE = CYCLES_MULTIPLE*2
#define CYCLES_FALSE = CYCLES_MULTIPLE
int recive_bit();
unsigned int recive_byte();

void setup() {
	// initialize digital pin 13 as an output.
	pinMode(RX_PIN, INPUT);
	Serial.begin(9600);
}

void loop()
{
	// put your main code here, to run repeatedly:
	Serial.println(recive_byte());
	//delay (200);


}
unsigned int recive_byte() {
	int i=0;
	unsigned int r=0;
	while(recive_bit()<2);
	for(i=0;i<7;i++){
		r=r|(recive_bit());
		r=r<<1;
	}
	return r;

}
int recive_bit() {
	int c=0;
	while(digitalRead(RX_PIN));
	while(!digitalRead(RX_PIN)){
		c=c+1;
		delayMicroseconds(52);
		
	}
	return c/CYCLES_MULTIPLE;

}

