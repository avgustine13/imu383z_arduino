

#ifndef IMU383Z_h
#define IMU383Z_h

#if defined(ARDUINO) && ARDUINO >= 100         //arduino core v1.0 or later
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <SPI.h>

enum {
	AX = 0,
	AY,
	AZ,
	GX,
	GX,
	GZ,
	TEMP,
	//
	IMU383_PARAM_COUNT
};

class IMU383Z 
{
	public:
		IMU383Z(int _csPin, int _drdyPin = -1);
		void begin();
		void readData();
		float data[IMU383_PARAM_COUNT] = {0};
	private:				
		int s16(uint8_t* ui8);
		float getTemp(uint8_t* ui8);
		float getAcc(uint8_t* ui8);
		float getRate(uint8_t* ui8);
		void parseData(uint8_t* buffer);
		
		const int DATA_SIZE   = 18;
		const int FRAME_DELAY = 20;
		int csPin;
		int drdyPin;		
	
};

#endif