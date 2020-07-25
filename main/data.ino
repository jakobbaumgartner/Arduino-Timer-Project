
String projectsRead()
{

  /* 
   *  Reads projects file on SD card and returns text as a String. 
   */

  File projectsFile;
  String projekti = "";

  Serial.print("Initializing SD card...");

  digitalWrite(31, HIGH);
  if (!SD.begin(53))
  {
    Serial.println("ERROR");
    Serial.println("initialization failed!");
    SDerror=1;
    return "error";
  }

  Serial.println("initialization done.\n");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.

  // open the file for reading:
  projectsFile = SD.open("projects.txt");

  if (projectsFile)
  {

    // read from the file until there's nothing else in it:
    while (projectsFile.available())
    {

      projekti = projectsFile.readString();
    }

    //Serial.print(projekti);

    // close the file:
    projectsFile.close();
    digitalWrite(31, LOW);
  }
  else
  {
    // if the file didn't open, print an error:
    Serial.println("ERROR");
    Serial.println("error opening projects.txt");
    SDerror=1;
  }

  return projekti;
}





int getNextID()
{

  /* 
  * Sessions are numbered, each has it's own unique counterID. When a new session, the function is invoked to get the next free ID.
  */

  File counterIDFile;
  int counterID;
  String counterIDString = "";

  digitalWrite(31, HIGH);
  if (!SD.begin(53))
  {
    Serial.println("ERROR");
    Serial.println("Error with SD card. failed!");
    SDerror=1;
    return 0;
  }


  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.


  // Get nextID from the file
  // open the file for reading:
  counterIDFile = SD.open("pid.txt");

  if (counterIDFile)
  {

    // read from the file until there's nothing else in it:
    while (counterIDFile.available())
    {

      counterIDString = counterIDFile.readString();
    }

    //  converts read text to int 
    counterID = counterIDString.toInt();


    Serial.print("\n\nNext ID: ");
    Serial.print(counterIDString);
    // close the file:
    counterIDFile.close();


    Serial.println("\nRemoving pid.txt...");
    SD.remove("pid.txt");

    Serial.println("\nCreating pid.txt and writing nextID in it.");
    counterIDFile = SD.open("pid.txt", FILE_WRITE);

    if (counterIDFile)
    {

      counterIDFile.println(counterID+1);
      Serial.print("\nSaved ID: ");
      Serial.println(counterID+1);
      
      counterIDFile.close();
      digitalWrite(31, LOW);
    }
    else
    {
      // if the file didn't open, print an error:
      Serial.println("ERROR");
      Serial.println("Error writing nextID to pid.txt");
      SDerror=1;
    }

    return counterID;
  }
}






String *projectsList(String projekti)
{
  /*
   * Parses the projects file output and displays it in a nice (pointer to) array of strings.
   */

  int lengthofprojekti = projekti.length();
  int currentletter = 0;
  int currentproject = 0;
  int numberOfProjects = 0;
  int starting = 0;
  int stoping = 0;

  for (currentletter = 0; currentletter < lengthofprojekti; currentletter++)
  {
    if (projekti[currentletter] == '#')
    {
      numberOfProjects++;
    }
  }

  String *projectsList = new String[numberOfProjects];

  for (currentletter = 0; currentletter < lengthofprojekti; currentletter++)
  {
    if (projekti[currentletter] == ';')
    {
      starting = currentletter + 1;
    }

    if (projekti[currentletter] == '#')
    {
      stoping = currentletter;
      projectsList[currentproject] = projekti.substring(starting, stoping);
      currentproject++;
    }
  }

  for (currentletter = 0; currentletter < numberOfProjects; currentletter++)
  {
    Serial.print(projectsList[currentletter]);
    Serial.print(" - ");
  }

  return projectsList;
}





int numOfProjects(String projekti)
{
  /*
   * Parses the projects file output and returns number of projects.
   */

  int lengthofprojekti = projekti.length();
  int currentletter = 0;
  int numberOfProjects = 0;

  for (currentletter = 0; currentletter < lengthofprojekti; currentletter++)
  {
    if (projekti[currentletter] == '#')
    {
      numberOfProjects++;
    }
  }

  return numberOfProjects;
}





void saveSessionStatus () {
  /*
   * This function saves session status.
   */


  File sessionsFile;

  digitalWrite(31, HIGH);
  if (!SD.begin(53))
  {
    Serial.println("ERROR");
    Serial.println("Error with SD card. failed!");
    SDerror=1;
    return 0;
  }


  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.

  // open the file for reading:
  sessionsFile = SD.open("sessions.txt", FILE_WRITE);


    Serial.print("\n" + String(recordedID) + "?" + String(listOfProjects[recordedProject]) + ";" + String(recordedProject) + "$" + String(floor((millis()-recordedStarted)/1000)) + "#");

    if (sessionsFile)
    {

      sessionsFile.println(String(recordedID) + "?" + String(listOfProjects[recordedProject]) + ";" + String(recordedProject) + "$" + String(floor((millis()-recordedStarted)/1000)) + "#");
     
      
      sessionsFile.close();
      digitalWrite(31, LOW);
    }
    else
    {
      // if the file didn't open, print an error:
      Serial.println("ERROR");
      Serial.println("Error writing sessions!");
      SDerror=1;
    }

  }





String Statistics (bool save = false) {
  /*
   * This function gets statistics (total time on projects).
   * If parameter is true, than it also increments minutage or current project.
   */

     File statsFile;

     String statsString = "";

  digitalWrite(31, HIGH);
    if (!SD.begin(53))
    {
      Serial.println("ERROR");
      Serial.println("Error with SD card. failed!");
      return "ERROR";
      SDerror=1;
    }


    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
  
  
    // Get nextID from the file
    // open the file for reading:
    statsFile = SD.open("stats.txt");
   
    if (statsFile)
      {
          Serial.println("\nReading stats.txt...");
    
        // read from the file until there's nothing else in it:
        while (statsFile.available())
        {
    
          statsString = statsFile.readString();
        }
    
        statsFile.close();
        
        Serial.println("\n" + statsString);

       
        int start = 0;
        int stopp = 0;
        int projectn = 0;
        for(int i = 0; i<statsString.length(); i++) {
          if(statsString[i] == ';') {start=i;}
          if(statsString[i] == '#') {stopp=i;
          
          statsInt[projectn] = (statsString.substring(start+1, stopp)).toInt();
    
          projectn++;
          }
          
        }
    
    
        Serial.println("\nRemoving stats.txt...");
        SD.remove("stats.txt");
    
        Serial.println("\nCreating stats.txt and writing new stats in it.");
        statsFile = SD.open("stats.txt", FILE_WRITE);
    
        if (statsFile)
        {
          Serial.println("");
          for(int i = 0; i < numberOfProjects; i++) {
            if(recordedProject==i && save) {
              // increment recording project minutage
                statsInt[i]=statsInt[i]+1;
                Serial.println("\nIncrementing stats.");
              }
            statsFile.println(String(i+1) + ";" + String(statsInt[i]) + "#");
            Serial.print(String(i+1) + ": " + String(statsInt[i]) + " - ");
            }
          
          statsFile.close();
          digitalWrite(31, LOW);
        }
        else
        {
          // if the file didn't open, print an error:
          Serial.println("ERROR");
          Serial.println("Error opening stats.txt");
          SDerror=1;
        }
    
        return statsString;
      }
}
