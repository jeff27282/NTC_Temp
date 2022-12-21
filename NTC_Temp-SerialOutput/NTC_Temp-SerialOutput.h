#include <NTC_Temp.h>

NTC_Temp temp1 = NTC_Temp(100000,4700,3950,A0,LOW);


void setup() {
  Serial.begin(9600);
}

void loop() {
  float i = temp1.tempRead();
  Serial.print(i);
  Serial.println("°C");
  delay(100);

}
