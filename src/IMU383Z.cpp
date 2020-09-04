#include "IMU383Z.h"
#include <SPI.h>

static IMU383Z* imuPtr = nullptr;
/**************************************************************************/
static void imuReadDataIRQ()
/**************************************************************************/
{
	if (imuPtr != nullptr)
	{
		imuPtr->readData();
	}
}

/**************************************************************************/
IMU383Z::IMU383Z(int _csPin, int _drdyPin)
/**************************************************************************/
{
	csPin   = _csPin;
	drdyPin = _drdyPin;
}

/**************************************************************************/
void IMU383Z::begin()
/**************************************************************************/
{
	pinMode(csPin, OUTPUT);	 
	reset();
	 
	if (drdyPin) {
		pinMode(drdyPin, INPUT);
		char irqNum = digitalPinToInterrupt(drdyPin);  //If 2 is passed and you are compiling for an UNO you irqNum should be 0.
		if (irqNum != NOT_AN_INTERRUPT)
		{
			imuPtr = this;
			attachInterrupt(irqNum, imuReadDataIRQ, RISING);
		}
	}
}

/**************************************************************************/
void IMU383Z::reset()
/**************************************************************************/
{
	uint8_t buf[CONTROL_SIZE] = {0};
	buf[0] = 0x78;
	transferSPI(buf, CONTROL_SIZE);
	memset(buf, 0, CONTROL_SIZE);
	buf[0] = 0x7A;
    buf[1] = 0x01;
    transferSPI(buf, CONTROL_SIZE);
	memset(buf, 0, CONTROL_SIZE);     
    buf[0] = 0x78;
	transferSPI(buf, CONTROL_SIZE);
	memset(buf, 0, CONTROL_SIZE);      
    buf[0] = 0x7A;
    buf[2] = 0x06;
	transferSPI(buf, CONTROL_SIZE);
	memset(buf, 0, CONTROL_SIZE);            
    buf[0] = 0x78;
	transferSPI(buf, CONTROL_SIZE);     
}

/**************************************************************************/
void IMU383Z::readData()
/**************************************************************************/
{
	uint8_t buf[DATA_SIZE] = {0};
	buf[0] = 0x3E;
    buf[1] = 0x00;
    transferSPI(buf, DATA_SIZE);
	parseData(buf);
}

/**************************************************************************/
float IMU383Z::get(uint8_t paramId)
/**************************************************************************/
{
	if (paramId < IMU383_PARAM_COUNT) {
		return data[paramId];
	}
}

/**************************************************************************/
void IMU383Z::transferSPI(uint8_t* buf, uint8_t size)
/**************************************************************************/
{
	SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
	for (int i = 0; i < size/2; i++) {
        digitalWrite(csPin, LOW);        
        SPI.transfer(buf + i*2, 2);
        digitalWrite(csPin, HIGH);        
        delayMicroseconds(FRAME_DELAY);        
    }
	SPI.endTransaction(); 
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