void recordingMODE () {
   if(menu == 0) {

      
      if (button == 12) {
       
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
        }

        // stop recording
        else {
           recordedStatus = false;

           Serial.print("\nRecording stopped!");
          
           
          }

      // to prevent starting and stopping right away
      delay(3000);
      }

      line_one = listOfProjects[currentProject];
      line_two = String(recordedTime[0]) + "h : " + String(recordedTime[1]) + "m : " + String(recordedTime[2]) + "s";
      //Serial.print("\nTime: \n");
      //Serial.print(recordedID);
    
    }

      
      
}

void recordingUPDATE () {

  // update h/m/s
  if(recordedStatus) {
//    Serial.print(millis());
   
    unsigned long timern = millis();
    recordedTime[0] = (timern-recordedStarted)/3600000;
    recordedTime[1] = (timern-recordedStarted)/60000;
    recordedTime[2] = floor((timern-recordedStarted)/1000)-recordedTime[1]*60-recordedTime[0]*3600;
   
  }
  
}
