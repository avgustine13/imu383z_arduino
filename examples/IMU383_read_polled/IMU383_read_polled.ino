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
  Serial.print(imu.ax());
  Serial.print(" ");
  Serial.print(imu.ay());
  Serial.print(" ");
  Serial.println(imu.az());
  Serial.print("[GX GY GZ] - ");
  Serial.print(imu.gx());
  Serial.print(" ");
  Serial.print(imu.gy());
  Serial.print(" ");
  Serial.println(imu.gz());
  Serial.print("Temp - ");
  Serial.println(imu.temp());  
  delay(1000);
}
