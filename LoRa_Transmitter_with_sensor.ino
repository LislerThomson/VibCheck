
#include <SPI.h>
#include<Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t Tmp,GyX,GyY,GyZ;
char AcXU,AcYU,AcZU,AcXL,AcYL,AcZL;
//Radio Head Library:
#include <RH_RF95.h> 

RH_RF95 rf95(4, 3);

int LED = 13; //Status LED is on pin 13

int packetCounter = 0; //Counts the number of packets sent
long timeSinceLastPacket = 0; //Tracks the time stamp of last packet received

float frequency = 921.2; //Broadcast frequency

void setup()
{
  pinMode(LED, OUTPUT);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
  while(!Serial); 
  Serial.println("RFM Client!"); 

  //Initialize the Radio.
  if (rf95.init() == false){
    Serial.println("Radio Init Failed - Freezing");
    while (1);
  }
  else{
    //An LED inidicator to let us know radio initialization has completed. 
    Serial.println("Transmitter up!"); 
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }

  // Set frequency
  rf95.setFrequency(frequency);

   rf95.setTxPower(14, false);
}


void loop()
{
  Serial.println("Sending message");

  //Send a message to the other radio
  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcXU=Wire.read();
  AcXL=Wire.read();// 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcYU=Wire.read();
  AcYL=Wire.read();// 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZU=Wire.read();
  AcZL=Wire.read();// 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L) 
Serial.println(AcXU<<8 | AcXL);
Serial.println(AcYU<<8 | AcYL);
Serial.println(AcZU<<8 | AcZL);
  uint8_t toSend[] ={AcXU, AcXL, AcYU, AcYL, AcZU, AcZL} ;
    
  rf95.send(toSend, sizeof(toSend));
  rf95.waitPacketSent();
}
