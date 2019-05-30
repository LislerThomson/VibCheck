/*********************************************************************************************
 *  File Name: readSensor
 * Author: Nivedita Rajendran
 * Description : This program reads a digital input from a sensor and stores it in a variable.
 * Version: A
 * Date : 05/29/2019
 **********************************************************************************************/
// digital pin 4 has a vibration sensor connected to it
int readSensor = 4;
// the setup routine runs once when you press reset
void setup() {
Serial.begin(9600);
// making pin 4 as input
pinMode(readSensor, INPUT);  

}
// the loop routine runs over and over again 
void loop() {
// reading pin 4 digital value
int dataSensor = digitalRead(readSensor);
// print the value read from sensor on the serial monitor
Serial.println(dataSensor);
delay(1);
// hahaha
}
