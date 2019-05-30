/*********************************************************************************************
 *  File Name: transmitSensor.ino
 * Author: Shadaab Saiyed
 * Description : This program sends a counter value through LoRa Module.
 * Version: A
 * Date : 05/29/2019
 **********************************************************************************************/
#include <SPI.h>
#include <LoRa.h>

// Sample Data to be transmitted
int counter = 0; 

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Transmitter");

// Initialises the Module to Operate in 915MHz.
  if (!LoRa.begin(915E6)) {
    Serial.println("LoRa Initialisation Failed");
    while (1);
  }
}

void loop() {
  Serial.print("Sending Data: ");
  Serial.println(counter);

  // sending data packets
  LoRa.beginPacket(); // denotes the begining of the data packet
  LoRa.print(counter); // the data to be transmitted
  LoRa.endPacket(); // denotes the end of the data packet

  counter++; 

  delay(5000);
}
