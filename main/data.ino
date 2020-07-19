
String projectsRead () {

  /* 
   *  Reads projects file on SD card and returns text as a String. 
   */

  File projectsFile;
  String projekti="";
    
  Serial.print("Initializing SD card...");

  if (!SD.begin(53)) {
    Serial.println("ERROR");
    Serial.println("initialization failed!");
    
  }
  
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.

  // open the file for reading:
  projectsFile = SD.open("projects.txt");
  
  if (projectsFile) {
    
       Serial.println("Projects:");

       // read from the file until there's nothing else in it:
        while (projectsFile.available()) {
      
            projekti = projectsFile.readString();
  
             }

       Serial.print(projekti);
       
      // close the file:
      projectsFile.close();
  } 
      else {
        // if the file didn't open, print an error:
        Serial.println("ERROR");
        Serial.println("error opening projects.txt");
      }

  return projekti;
}
