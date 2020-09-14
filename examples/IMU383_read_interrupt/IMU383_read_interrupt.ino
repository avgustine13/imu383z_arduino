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
