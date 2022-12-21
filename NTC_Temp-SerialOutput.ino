#include <NTC_Temp.h>

//
//  created 11 May 2021
//  by Alex
//
//  相关解释说明：
//  https://blog.csdn.net/changsic/article/details/116676147


//连接方式：GND----|4700|----|NTC |---VCC
//NTC_Temp temp1 = NTC_Temp(100000,4700,3950,A0,HIGH);
//NTC_Temp temp1 = NTC_Temp(10000,4700,3435,A0,HIGH);

//连接方式：GND----|NTC |----|4700|---VCC
NTC_Temp temp1 = NTC_Temp(100000,4700,3950,A0,LOW);
//NTC_Temp temp1 = NTC_Temp(10000,4700,3435,A0,LOW);

//NTC_Temp(int NTCR,int CONTACTR,int B,byte READPIN,boolean point)
//NTC电阻25°C时的阻值,串联电阻,   B值,     测压引脚,   NTC连接电位

void setup() {
  Serial.begin(9600);
}

void loop() {
  float i = temp1.tempRead();
  Serial.print(i);
  Serial.println("°C");
  delay(100);

}
