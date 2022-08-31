#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Adafruit_ADS1X15.h>

//initialize ADC
Adafruit_ADS1115 ads;
const int multiplier = 0.1875F;
int ain0 = 0; int ain1 = 0; int ain2 = 0; int ain3 = 0;

//initialize INA219
Adafruit_INA219 ina219_1 (0x40);    //Default adress is 0x40
Adafruit_INA219 ina219_2 (0x41);    // if A0 is jumpered
Adafruit_INA219 ina219_3 (0x44);    // if A1 is jumpered
//Adafruit_INA219 ina219 (0x45);    // if A0 and A1 is jumpered

void setup() {
Serial.begin(9600);
  ads.begin();

  //PLX DAQ
  Serial.println("CLEARDATA");
  Serial.println("LABEL, Time, VOLTAGE 1, VOLTAGE 2, VOLTAGE 3, VOLTAGE 4, CURRENT_MODULE, CURRENT_TRAFO1, CURRENT_TRAFO2");
  Serial.println("RESETTIMER");

  //Addressing INA219
  while (!Serial) {
      delay(1);
  }

  uint32_t currentFrequency;

  if (! ina219_1.begin()) {
    Serial.println("Failed to find INA219 1 chip");
    while (1) { delay(10); }
  }

  if (! ina219_2.begin()) {
    Serial.println("Failed to find INA219 2 chip");
    while (1) { delay(10); }
  }

    if (! ina219_3.begin()) {
    Serial.println("Failed to find INA219 3 chip");
    while (1) { delay(10); }
  }

}

void loop() { 
  //ADC Voltage
  int16_t adc0, adc1, adc2, adc3;
  int16_t sen0, sen1, sen2, sen3;
  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);
  ain0 = ((adc0*multiplier)/1000)+0.220; 
  ain1 = ((adc1*multiplier)/1000)+0.100;
  ain2 = ((adc2*multiplier)/1000)+0.250;
  ain3 = ((adc3*multiplier)/1000)+1.170;
  sen0 = movingAvg(ain0); 
  sen1 = movingAvg(ain1);
  sen2 = movingAvg(ain2);
  sen3 = movingAvg(ain3);

  //Power Current INA219
  float current_1 = 0; float current_2 = 0; float current_3 = 0;
  current_1 = ina219_1.getCurrent_mA();
  current_2 = ina219_2.getCurrent_mA();
  current_3 = ina219_3.getCurrent_mA();
  

  //print
  Serial.print("DATA,TIME,");
  Serial.print(sen0, 3);
  Serial.print(",");
  Serial.print(sen1, 3);
  Serial.print(",");
  Serial.print(sen2, 3);
  Serial.print(",");
  Serial.print(sen3, 3);
  Serial.print(",");
  Serial.print(current_2, 3);
  Serial.print(",");
  Serial.print(current_3, 3);
  Serial.print(",");
  Serial.print(current_1, 3);
  Serial.println(" ");

delay(1000);
}
