int buttonPressed () {

  int buttonNumber = 0;
  int shiftRegister[100];
  int sum=0;

//set all fields to 0
 for(int i =0; i <100; i++) {
  shiftRegister[i] = 0;
 }

  if(digitalRead(2)) {
    buttonNumber=2;
    
    delay(250);
    }
  if(digitalRead(3)) {
    buttonNumber=3;
    
    delay(250);
    }
  if(digitalRead(4)) {
    buttonNumber=4;
   
    delay(250);
    }
  if(digitalRead(5)) {
    buttonNumber=5;
   
    delay(250);
    }

  if(digitalRead(12)) {

    /* 
     *  In case of button 12 which is conformation button we do smtg else. The button is activated only if it is pressed enough time.
     */

    Serial.print("\n");
    for(int i =0; i <100; i++) {
      shiftRegister[i] = digitalRead(12);
      delay(2);
      //Serial.print("\n");
      //Serial.print(i);

      // because we are stopping the main execution, we have to refresh display in this loop
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("...");
      lcd.setCursor(0,1);
      lcd.print(100-i);

      
    }
      
    for(int i =0; i <100; i++) {
      //Serial.print(shiftRegister[i]);
      sum = sum + shiftRegister[i];
    
     shiftRegister[i] = 0;
      }

      while(digitalRead(12)) {
        // just wait until user lifts his / her finger
      delay(5);
      Serial.print("\nLift yer finger, ya maggot!");
      }

      if(sum > 90) {
        /*
         * Some bouncing allowed.
         */
         
        buttonNumber=12;

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("...");
        lcd.setCursor(0,1);
         if (!recordedStatus) {
             lcd.print("REC. STARTING ...");
         }
         else {
             lcd.print("REC. STOPPING ...");
         }
         
        
      }
      else {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(line_one);
          lcd.setCursor(0,1);
          lcd.print(line_two);
          }
        }

      
    
  if(buttonNumber) {
    Serial.print("\n\nButton pressed: ");
    Serial.print(buttonNumber);
  }
    
  return buttonNumber;
}
