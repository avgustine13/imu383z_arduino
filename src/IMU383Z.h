//IMU383Z Arduino SDK library

/* USAGE
*  add this library as usual for Arduino SDK.
*  in main sketch
*  #include <IMU383Z>
*  create instance IMU383Z imu;
*  Constructor has two parameters (csPin - SS pin for SPI bus, drdyPin (default is -1) - data ready pin for interrupt read (if set to -1 - interrupt read disabled)
*  call SPI.begin()
*  call IMU383 .begin() 
*  call .readData() in a loop for polled read 
*  get any parameter by .get(PARAM_ID), PARAM_ID can be taken from enum below
*/

#ifndef IMU383Z_h
#define IMU383Z_h

#if defined(ARDUINO) && ARDUINO >= 100         //arduino core v1.0 or later
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class IMU383Z 
{
	public:
		IMU383Z(int _csPin, int _drdyPin = -1); //_csPin - SS SPI pin, _drdyPin - data ready pin (for interrupt read), if not set - polled read chosen
		void begin();
		void reset();
		void readData();
		float gx();
		float gy();
		float gz();
		float ax();
		float ay();
		float az();
		float temp();
		void toExtBuffer(uint8_t* extPtr); 
		
	private:				
		int16_t s16(uint8_t* ui8);
		float getTemp(uint8_t* ui8);
		float getAcc(uint8_t* ui8);
		float getRate(uint8_t* ui8);
		void transferSPI(uint8_t* buffer, uint8_t size);
		void parseData(uint8_t* buffer);
		
		static const int DATA_SIZE   	= 18;
		const int CONTROL_SIZE  = 4;
		const int FRAME_DELAY 	= 20;
		int csPin;
		int drdyPin;
		uint8_t dataBuffer[DATA_SIZE] = {0};
};

#endif