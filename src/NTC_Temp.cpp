#include "NTC_Temp.h"
#include "Arduino.h"

NTC_Temp::NTC_Temp(float NTCR,float CONTACTR,unsigned int B,byte READPIN, bool POINT)
{
  this->ntcR = NTCR;
  this->contactR = CONTACTR;
  this->B_value = B;
  this->readPin = READPIN;
  this->point = POINT;   //NTC另一端连接的点的电位  连接5V(VCC)为HIGH 
  pinMode(readPin,INPUT);
}

float NTC_Temp::tempRead()
{
	//限幅+平均值滤波  读取SAMPLE_COUNT次
	u16_Sample_sum = 0;
	
	u16_min_Sample = 0;
	u16_max_Sample = 0;
  for(unsigned char i=0;i<SAMPLE_COUNT;i++)
  {
	  
    u16_Sample[i] = analogRead(readPin);
	
	u16_Sample_sum = u16_Sample_sum + u16_Sample[i];
	//memory the max and min sample
	if(i > 0)
	{
		if(u16_Sample[i] < u16_min_Sample){u16_min_Sample = u16_Sample[i];}
		else if(u16_Sample[i] > u16_max_Sample){u16_max_Sample = u16_Sample[i];}
	}
	//when i = 0,it should let 
	//min and max_Sample = AD_sample[0];
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
	
    Pin_voltage = u16_Sample_sum*(5.000000/1023.000000);     //转换实际电压值
	
	if(point == HIGH) //如果连接点为高电位 Rt求解公式为
	{
		temp = (5*contactR)/Pin_voltage - contactR; //求出Rt，实时热敏电阻电阻
	}
	else		//连接点为低电位 Rt求解公式为：
	{
		temp = Pin_voltage * contactR /(5-Pin_voltage);
	}
    
    temp = temp/ntcR;                   //求出Rt/R
    temp = log(temp);                 //求出ln(Rt/R)
    temp = temp / B_value;
    temp = temp + (1/T2);  
    temp = 1/(temp);    
    temp = temp - 273.15;             //最后结果 
    
    /*if((temp<0)||(temp>100)){
      Serial.println("error");
      return ;
    }
    */
    //sensVal = constrain(temp, 0, 100);
    //传感器返回值的范围限制在 0 到 100 之间

	return (temp);
}
/*
   * 热敏电阻串联一个nK电阻，由串联分压得出nK电阻的电压
   * a为nK电阻上的模拟电压值，转换为数值为
   * a = a*(5.000000/1023.000000);保留六位小数
   * V（nk电阻）= a = （5.000000*（n.000000/（n.000000+R）））
   * Rt即为热敏电阻的阻值
   * 换算得：
   *            （5*n）
   *        Rt = ------- - n
   *               V（a）
   * 
   * NTC 100 3950K 热敏电阻,B=3950,T2=25+273.15
   *  R为热敏电阻在25°时的阻值，为100000欧
   * 
   * 
   *               Rt 
   *   1      ln（----- ）
   *  ---           R            1
   *  T1 =  ---------------- + ----
   *                B           T2
   * 
   * 由此可以求出环境温度： 1/T1
   */