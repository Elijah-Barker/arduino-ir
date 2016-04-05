#define RX_PIN 2
#define CYCLE_LEN 13
#define  CYCLES_MULTIPLE  23
#define  CYCLES_HEADER  CYCLES_MULTIPLE*4
#define CYCLES_TRUE = CYCLES_MULTIPLE*2
#define CYCLES_FALSE = CYCLES_MULTIPLE
int recive_bit();
unsigned int rx_ec();
unsigned int recive_byte();

void setup() {
	// initialize digital pin 13 as an output.
	pinMode(RX_PIN, INPUT);
	Serial.begin(9600);
}

void loop()
{
	// put your main code here, to run repeatedly:
	//Serial.println(recive_byte());
	int a=rx_ec();
	if(a>1)
		Serial.println(a);
	//delay (200);


}
unsigned int rx_ec(){
	static unsigned int l=0;
	static unsigned int c=0;
	unsigned int b=recive_byte();
	if(l==b)
		c=c+1;
	else
		c=0;
	if(c>=2){
		c=0;
		l=0;
		return b;
	}
	l=b;
	return c;
}
unsigned int recive_byte() {
	int i=0;
	unsigned int r=0;
	while(recive_bit()<2);
	/*for(i=0;i<7;i++){
		r=r|(recive_bit());
		r=r<<1;
	}*/
	for(i=0;i<8;i++){
		r=r|(recive_bit()<<i);
		//r=r<<1;
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

