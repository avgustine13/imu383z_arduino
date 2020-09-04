//ESP32 example with polled read

#include <IMU383Z.h>
#include <SPI.h>

#define IMU_CS_PIN    5   //SPI CS pin

IMU383Z imu(IMU_CS_PIN);

void setup() {
  Serial.begin(115200);
  Serial.println("IMU383Z example polled");
  SPI.begin();
  imu.begin();
  delay(2000);
}

void loop() {
  imu.readData();
  Serial.print("[AX AY AZ] - ");
  Serial.print(imu.get(AX));
  Serial.print(" ");
  Serial.print(imu.get(AY));
  Serial.print(" ");
  Serial.println(imu.get(AZ));
  Serial.print("[GX GY GZ] - ");
  Serial.print(imu.get(GX));
  Serial.print(" ");
  Serial.print(imu.get(GY));
  Serial.print(" ");
  Serial.println(imu.get(GZ));
  Serial.print("Temp - ");
  Serial.println(imu.get(TEMP));  
  delay(1000);
}
