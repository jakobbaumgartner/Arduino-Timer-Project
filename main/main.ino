#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

/*
  SD card read/write
  
  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 51
 ** MISO - pin 50
 ** CLK - pin 52
 ** CS - pin 53 

*/

#include <SPI.h>
#include <SD.h>

int buttonPressed ();
void changeProject(int changeDirection);
void recordingUPDATE ();
void recordingMODE ();


  int button;
  int mode = 1;
  /*
   * This variable is used to set mode that device operates in.
   * 0 welcome screen
   * 1 record mode
   * 2 stats mode
   */

  int menu = 0;

  /*
   * This variable is used for opening menu. 
   * 0 menu closed
   * 1 ... menu page
   */

  // Message should not be longer than 16 chars or it should be in two lines.
  String line_one = "";
  String line_two = "";
  String line_one_old = "";
  String line_two_old = "";

  // Projects 
  String* listOfProjects = NULL;
  int numberOfProjects = 0;
  // currently open project
  int currentProject = 0;

  //RECORDING

    bool recordedStatus = false;
    int recordedID = NULL;
     // time recorded h/m/s
    int recordedTime[3]= {0,0,0};
    int recordedProject= NULL;
    unsigned long recordedStarted = NULL;
    int lastSavedMIN = 0;


void setup() {


  // start serial 
  Serial.begin(9600);
  Serial.print("\n\n\n\n---rebooted---\n---.-.-.-.-.-.-.-.--.---\n\n\n");
  
  
  // initialize the LCD
  lcd.begin();
  lcd.backlight();

  line_two = "Loading ...";

  
  
  // reads projects file and returns array of projects
  String projekti = projectsRead();

  listOfProjects =  projectsList(projekti);
  numberOfProjects = numOfProjects(projekti);



  // set input pins
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(12, INPUT);

  // set output pins
  pinMode(28, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(31, OUTPUT);


}

void loop() {

//  Serial.print("loopAhup");

  button=buttonPressed();

  if(recordedStatus){recordingUPDATE();}

  // changing mode button
  if(button == 2) {
    if(mode == 1) {mode = 2;}
    else if (mode == 2) {mode = 1;}
    Serial.print("\nMODE: ");
    Serial.print(mode);
  }

  

  // recording mode
  if(mode == 1) {
   recordingMODE();
  }

  // stats mode
  if(mode == 2) {
    
  }

  
  

  if(line_one != line_one_old || line_two != line_two_old) {

    /* Update LCD values if values of line_one or line_two strings have changed. */
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(line_one);
    lcd.setCursor(0,1);
    lcd.print(line_two);
  
//    Serial.print("\n\n -- NEW DISPLAY -- ");
//    Serial.print("\n------------------------------------------\n");
//    Serial.print(line_one);
//    Serial.print("\n");
//    Serial.print(line_two);
//    Serial.print("\n------------------------------------------\n");

    line_one_old = line_one;
    line_two_old = line_two;
    
    }

  

 

}
