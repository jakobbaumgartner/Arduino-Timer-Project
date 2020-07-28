void blueLEDStime (bool demo = false) {
  if (demo) {
    LEDStime = 10000;
  }
  
   unsigned long timee=millis()-recordedStarted;
   

 
  if (timee>LEDStime && timee<2*LEDStime) {
    digitalWrite(28, HIGH);
    //Serial.println("LED 1");
    }
   if (timee>2*LEDStime && timee<3*LEDStime) {
  digitalWrite(30, HIGH);
    //Serial.println("LED 2");
  }
   if (timee>3*LEDStime && timee<4*LEDStime) {
  digitalWrite(32, HIGH);
   // Serial.println("LED 3");
  }
   if (timee>4*LEDStime && timee<5*LEDStime) {
  digitalWrite(34, HIGH);
   // Serial.println("LED 4");
  }
   if (timee>5*LEDStime && timee<6*LEDStime) {
  digitalWrite(36, HIGH);
   // Serial.println("LED 5");
  }
}


void blueLEDSOff () {
  digitalWrite(28, LOW);
  digitalWrite(30, LOW);
  digitalWrite(32, LOW);
  digitalWrite(34, LOW);
  digitalWrite(36, LOW);
}
