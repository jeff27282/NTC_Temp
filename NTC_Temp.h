#ifndef NTC_Temp_H
#define NTC_Temp_H

#include "Arduino.h"

#define SAMPLE_COUNT 10
#define T2 			(273.15+25)

class NTC_Temp
{
  private:
          float ntcR;             //NTC电阻25°C时的阻值
          float contactR;         //串联电阻阻值
          unsigned int B_value;            //B值
          byte readPin;         //测压引脚

		  unsigned int u16_Sample_sum = 0;
          unsigned int u16_Sample[SAMPLE_COUNT] = {};
		  unsigned int u16_max_Sample;
		  unsigned int u16_min_Sample;

          float Pin_voltage;
          float temp;
		  bool point;
  public:
          NTC_Temp(float NTCR,float CONTACTR,unsigned int B,byte READPIN,bool point);
          float tempRead();
          
};
#endif
