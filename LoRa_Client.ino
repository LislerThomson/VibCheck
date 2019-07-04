/*
 * LoRa_Client.ino
 * Authors: Lisler Thomson, Shadaab Saiyed, Nivedita Rajendran
 * Description: This program broadcasts a message using the SAMD21 and RFM95 LoRa Module and then
 *              waits for a reply.
 * Rev: A
 * Date: 07/02/2019
 */

#include <SPI.h>

//Radio Head Library:
#include <RH_RF95.h> 

// Sets the Interrupt and Chip Select pins for RFM95. for Sparkfun Pro RF it is 6 & 12 resp.
RH_RF95 rf95(12, 6);

int LED = 13; //Status LED is on pin 13

int packetCounter = 0; //Counts the number of packets sent
long timeSinceLastPacket = 0; //Tracks the time stamp of last packet received

float frequency = 921.2; // This is the Broadcast frequency

void setup()
{
  pinMode(LED, OUTPUT);

  SerialUSB.begin(9600);
  
  while(!SerialUSB); 
  SerialUSB.println("RFM Client!"); 

  //Initialize the Radio.
  if (rf95.init() == false){
    SerialUSB.println("Radio Init Failed - Freezing");
    while (1);
  }
  else{
    //An LED inidicator to let us know radio initialization has completed. 
    SerialUSB.println("Transmitter up!"); 
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }

  // Set frequency
  rf95.setFrequency(frequency);

  // Set Transmit Power
   rf95.setTxPower(14, false);
}


void loop()
{
  SerialUSB.println("Sending message");

  //Send a message to the other radio
  uint8_t toSend[] = "Hi there!";

  rf95.send(toSend, sizeof(toSend)); // Transmits the data in the array tosend[] 
  rf95.waitPacketSent(); // waits till the transmission is done.

}
