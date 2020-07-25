/*
  SD card read/write
  
  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 51
 ** MISO - pin 50
 ** CLK - pin 52
 ** CS - pin 53 

*/

String FileName = "stats.txt";
bool writing = false;
bool removefile = true;

#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(53)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

if(removefile) {
  if(SD.remove(FileName)) {
    Serial.println("\nFile removed");}
  }

if (writing) {
    // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open(FileName, FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to " + FileName);

    // WRITE HERE:
    
    myFile.println("1;0#");
    myFile.println("2;0#");
    myFile.println("3;0#");
    myFile.println("4;0#");





    
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening " + FileName);
  }

  }

  // re-open the file for reading:
  myFile = SD.open(FileName);
  if (myFile) {
    Serial.println(FileName);

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening " + FileName);
  }
}

void loop() {
  // nothing happens after setup
}
