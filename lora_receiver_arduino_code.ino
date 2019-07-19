#include <SPI.h>

//Radio Head Library: 
#include <RH_RF95.h>

int16_t AcX, AcY, AcZ;

RH_RF95 rf95(12, 6);

int LED = 13; //Status LED on pin 13

int packetCounter = 0; //Counts the number of packets sent
long timeSinceLastPacket = 0; //Tracks the time stamp of last packet received
float frequency = 921.2;

void setup()
{
  pinMode(LED, OUTPUT);

  SerialUSB.begin(9600);
  while(!SerialUSB);
  SerialUSB.println("RFM Server!");

  //Initialize the Radio. 
  if (rf95.init() == false){
    SerialUSB.println("Radio Init Failed - Freezing");
    while (1);
  }
  else{
  // An LED indicator to let us know radio initialization has completed.
    SerialUSB.println("Receiver up!");
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }

  rf95.setFrequency(frequency); 

}

void loop()
{
  if (rf95.available()){
    // Should be a message for us now
    int8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf)-1;

    if (rf95.recv((uint8_t*)buf, &len)){
      digitalWrite(LED, HIGH); //Turn on status LED
      timeSinceLastPacket = millis(); //Timestamp this packet
      AcX = buf[0]<<8 | buf[1];
      AcY = buf[2]<<8 | buf[3];
      AcZ = buf[4]<<8 | buf[5];

      SerialUSB.print(AcX/16384.0);
      SerialUSB.print(" ");

      SerialUSB.print(" ");
      SerialUSB.print(AcY/16384.0);
      SerialUSB.print(" ");

      SerialUSB.print(" ");
      SerialUSB.print(AcZ/16384.0);
      
      SerialUSB.print("\n");
      SerialUSB.println();
    
    }
    else
      SerialUSB.println("Recieve failed");
  }
  
  //Turn off status LED if we haven't received a packet after 1s
  if(millis() - timeSinceLastPacket > 1000){
    digitalWrite(LED, LOW); //Turn off status LED
    timeSinceLastPacket = millis(); //Don't write LED but every 1s
  }
}
