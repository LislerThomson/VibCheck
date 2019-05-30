/*********************************************************************************************
 *  File Name: readSensor
 * Author: Nivedita Rajendran
 * Description : This program reads a digital input from a sensor and stores it in a variable.
 * Version: A
 * Date : 05/29/2019
 **********************************************************************************************/
// digital pin 4 has a vibration sensor connected to it
int readSensor = 4;

void setup() {
Serial.begin(9600);
pinMode(readSensor, INPUT);  

}

void loop() {
int dataSensor = digitalRead(readSensor);

Serial.println(dataSensor);
delay(1);
}
