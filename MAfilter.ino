float movingAvg (float x) {
  int sensRead = 5;            //number of samples
  float sensSum[sensRead];     //sum of sensor readings
  float arraySum = 0.0;
  for(int k=0; k < sensRead; k++) {
    sensSum[k] = x;
    arraySum += sensSum[k];
    delay(10);
  }
  float sensMA = arraySum/sensRead;  //average sensor readings
  return sensMA;
}