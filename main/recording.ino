void recordingMODE () {
   if(menu == 0) {
      
      if (button == 12) {
        

       if(screen_interrupt) {
        
        screen_interrupt=false;
       }
       else {
        // start recording
        if (!recordedStatus){
          
          recordedID = getNextID();
          Serial.print("\nRecording started! RecordingID: ");
          Serial.print(recordedID);

          recordedStatus = true;
          recordedStarted = millis();
          recordedProject = currentProject;
          Serial.print(";   Started: ");
          Serial.print(recordedStarted);

          saveSessionStatus();
        }

        // stop recording
        else {
           saveSessionStatus();
           recordedStatus = false;
           lastSavedMIN=0;
           recordedTime[0] = 0;
           recordedTime[1] = 0;
           recordedTime[2] = 0;
           recordedStarted = 0;

           Serial.print("\nRecording stopped!");
          
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print(line_one);
            lcd.setCursor(0,1);
            lcd.print(line_two);
          }
          

      // to prevent starting and stopping right away
      delay(3000);
      }
   }

    // change current project
      if(button == 4) {
        changeProject(-1);
        }

       if(button == 5) {
        changeProject(1);
        }

      if(!screen_interrupt) {
          line_one = listOfProjects[currentProject];
          line_two = String(recordedTime[0]) + "h : " + String(recordedTime[1]) + "m : " + String(recordedTime[2]) + "s";
        
      }
   
    }
}


void changeProject(int changeDirection) {  
      if (changeDirection == -1) {
        // go one project back
        if(currentProject>0) {
          currentProject--;
          }
        }

      if (changeDirection == 1){
        if(numberOfProjects-1>currentProject) {
          currentProject++;
          }
      }
      
}

void recordingUPDATE () {

  // update h/m/s
 
//    Serial.print(millis());
   
    unsigned long timern = millis();
    recordedTime[0] = (timern-recordedStarted)/3600000;
    recordedTime[1] = (timern-recordedStarted)/60000;
    recordedTime[2] = floor((timern-recordedStarted)/1000)-recordedTime[1]*60-recordedTime[0]*3600;

   if(lastSavedMIN<recordedTime[1] && !screen_interrupt) {
    saveSessionStatus();
    lastSavedMIN++;

    if (lastSavedMIN>0) {
          // stop recording
           //saveSessionStatus();
           recordedStatus = false;
           lastSavedMIN=0;
           recordedTime[0] = 0;
           recordedTime[1] = 0;
           recordedTime[2] = 0;
           recordedStarted = 0;

           Serial.print("\nMax length reached!");
           Serial.print("\nRecording stopped.");
           screen_interrupt = true;
           line_one = "RECORDING TOO LONG!";
           line_two = "MAX LENGTH 10H";
          
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print(line_one);
            lcd.setCursor(0,1);
            lcd.print(line_two);
    }
   }
}
