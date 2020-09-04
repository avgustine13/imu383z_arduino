#include "IMU383Z.h"

/**************************************************************************/
IMU383Z::IMU383Z(int _csPin, int _drdyPin)
/**************************************************************************/
{
	csPin   = _csPin;
	drdyPin = _drdyPin;
}

/**************************************************************************/
IMU383Z::begin()
/**************************************************************************/
{
	 SPI.begin();
	 SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
	 pinMode(csPin, OUTPUT);
	 
	 if (drdyPin) {
		 pinMode(drdyPin, INPUT);
		 attachInterrupt(digitalPinToInterrupt(drdyPin), readData, RISING);
	 }
	 
}

/**************************************************************************/
IMU383Z::readData()
/**************************************************************************/
{
	uint8_t buf[DATA_SIZE] = {0};
	buf[0] = 0x3E;
    buf[1] = 0x00;
    for (int i = 0; i < DATA_SIZE/2; i++) {
        digitalWrite(csPin, LOW);        
        SPI.transfer(buf + i*2, 2);
        digitalWrite(csPin, HIGH);        
        delayMicroseconds(FRAME_DELAY);        
    }
	parseData(buf);
}

/**************************************************************************/
void IMU383Z::parseData(uint8_t* buffer)
/**************************************************************************/
{
	data[GX] 	= getRate(buffer + 4);
	data[GY] 	= getRate(buffer + 6);
	data[GZ] 	= getRate(buffer + 8);
	data[AX] 	= getAcc(buffer + 10);
	data[AY] 	= getAcc(buffer + 12); 
	data[AZ] 	= getAcc(buffer + 14); 
	data[TEMP]  = getTemp(buffer + 16);
}

/**************************************************************************/
int IMU383Z::s16(uint8_t* ui8)
/**************************************************************************/
{
  uint16_t value = ui8[1] | (ui8[0] << 8);
  return -1*(value & 0x8000) | (value & 0x7fff);
}

/**************************************************************************/
float IMU383Z::getTemp(uint8_t* ui8)
/**************************************************************************/ 
{       
  return s16(ui8) * 0.07311 + 31.0;   
}

/**************************************************************************/
float IMU383Z::getAcc(uint8_t* ui8)
/**************************************************************************/
{
  return s16(ui8) / 4000.0;
}

/**************************************************************************/
float IMU383Z::getRate(uint8_t* ui8)
/**************************************************************************/
{
  return s16(ui8) / 200.0;
}