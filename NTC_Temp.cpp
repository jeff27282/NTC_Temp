#include "NTC_Temp.h"
#include "Arduino.h"

NTC_Temp::NTC_Temp(float NTCR,float CONTACTR,unsigned int B,byte READPIN, bool POINT)
{
  this->ntcR = NTCR;
  this->contactR = CONTACTR;
  this->B_value = B;
  this->readPin = READPIN;
  this->point = POINT;  
  pinMode(readPin,INPUT);
}

float NTC_Temp::tempRead()
{
	u16_Sample_sum = 0;
	
	u16_min_Sample = 0;
	u16_max_Sample = 0;
  for(unsigned char i=0;i<SAMPLE_COUNT;i++)
  {
	  
    u16_Sample[i] = analogRead(readPin);
	
	u16_Sample_sum = u16_Sample_sum + u16_Sample[i];
	if(i > 0)
	{
		if(u16_Sample[i] < u16_min_Sample){u16_min_Sample = u16_Sample[i];}
		else if(u16_Sample[i] > u16_max_Sample){u16_max_Sample = u16_Sample[i];}
	}
	else
	{
		u16_min_Sample = u16_Sample[i];
		u16_max_Sample = u16_Sample[i];
	}
	delay(1);
  }
	//minus max and min then average
	u16_Sample_sum = u16_Sample_sum - u16_min_Sample;
	u16_Sample_sum = u16_Sample_sum - u16_max_Sample;
	u16_Sample_sum = u16_Sample_sum / (SAMPLE_COUNT - 2);
	
    Pin_voltage = u16_Sample_sum*(5.000000/1023.000000);
	
	if(point == HIGH)
	{
		temp = (5*contactR)/Pin_voltage - contactR;
	}
	else
	{
		temp = Pin_voltage * contactR /(5-Pin_voltage);
	}
    
    temp = temp/ntcR;
    temp = log(temp);
    temp = temp / B_value;
    temp = temp + (1/T2);  
    temp = 1/(temp);    
    temp = temp - 273.15;
	return (temp);
}
