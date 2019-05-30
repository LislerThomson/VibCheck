/*********************************************************************************************
 *  File Name: receiverSensor.ino
 * Author: Lisler Thomson Pulikkottil
 * Description : This program receives the sensor data from the LoRa Module.
 * Version: A
 * Date : 05/29/2019
 **********************************************************************************************/
#include <SPI.h>
#include <LoRa.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Receiver");
  
// Initialising LoRa module with 915Mhz
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  
  // Checking if any data is received
  int packetSize = LoRa.parsePacket();
  
  if (packetSize) {
    // if data packet is received 
    Serial.print("Received Data Packet ");

    // Reads the data packet and displays on Serial Monitor
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }
  }
}
