
String projectsRead()
{

  /* 
   *  Reads projects file on SD card and returns text as a String. 
   */

  File projectsFile;
  String projekti = "";

  Serial.print("Initializing SD card...");

  if (!SD.begin(53))
  {
    Serial.println("ERROR");
    Serial.println("initialization failed!");
    
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
  }
  else
  {
    // if the file didn't open, print an error:
    Serial.println("ERROR");
    Serial.println("error opening projects.txt");
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

  
  if (!SD.begin(53))
  {
    Serial.println("ERROR");
    Serial.println("Error with SD card. failed!");
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
    }
    else
    {
      // if the file didn't open, print an error:
      Serial.println("ERROR");
      Serial.println("Error writing nextID to pid.txt");
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

/* 
  * Sessions are numbered, each has it's own unique counterID. When a new session, the function is invoked to get the next free ID.
  */

  File sessionsFile;

  
  if (!SD.begin(53))
  {
    Serial.println("ERROR");
    Serial.println("Error with SD card. failed!");
    return 0;
  }


  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.


  // Get nextID from the file
  // open the file for reading:
  sessionsFile = SD.open("sessions.txt", FILE_WRITE);


    Serial.print("\nSaving session: " + String(recordedID) + ";" + String(recordedProject) + "$" + String(floor((millis()-recordedStarted)/1000)) + "#");

    if (sessionsFile)
    {

      sessionsFile.println(String(recordedID) + ";" + String(recordedProject) + "$" + String(floor((millis()-recordedStarted)/1000)) + "#");
     
      
      sessionsFile.close();
    }
    else
    {
      // if the file didn't open, print an error:
      Serial.println("ERROR");
      Serial.println("Error writing sessions!");
    }

  }


void saveStatistics () {
  /*
   * This function saves statistics (total time on projects).
   */
}
