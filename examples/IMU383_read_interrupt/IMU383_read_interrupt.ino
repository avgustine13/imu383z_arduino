//ESP32 example with read on data ready interrupt

#include <IMU383Z.h>
#include <SPI.h>

#define IMU_CS_PIN    5   //SPI CS pin
#define IMU_DRDY_PIN  27  //interrupt pin of needed MCU

IMU383Z imu(IMU_CS_PIN, IMU_DRDY_PIN);

void setup() {
  Serial.begin(115200);
  Serial.println("IMU383Z example with DRDY read");
  SPI.begin();
  imu.begin();
  delay(2000);
}

void loop() {
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
