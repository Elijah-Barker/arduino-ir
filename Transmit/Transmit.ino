void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  
  delay (200);

  int i = 0;
  for(i=0;i<20;i++)
  {
    transmit(8*10);
    delay(100);
  }
  delay(1000);
}



void transmit(char data)
{
  const int CYCLES_MULTIPLE = 23
  const int CYCLES_HEADER = CYCLES_MULTIPLE*4;
  const int CYCLES_TRUE = CYCLES_MULTIPLE*2;
  const int CYBLES_FALSE = CYCLES_MULTIPLE;
  int i=0;

  //send whatever
  for(i=0;i<CYCLES_HEADER;i++)
  {
    digitalWrite(13, HIGH);
    delayMicroseconds(13);
    digitalWrite(13, LOW);
    delayMicroseconds(13);
  }
  //wait ten cycles before transmitting
  for(i=0;i<20;i++)
  {
    delayMicroseconds(13);
  }
  
  int j=0;
  for(;j<8;j++)
  {
    int myBit = data%2;
    data /= 2;

    if(myBit)
    {
      //send whatever
      for(i=0;i<CYCLES_TRUE;i++)
      {
        digitalWrite(13, HIGH);
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
    else
    {
      //send whatever
      for(i=0;i<CYCLES_FALSE;i++)
      {
        digitalWrite(13, HIGH);
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
  }
}

