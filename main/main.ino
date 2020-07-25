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

// SET SHORTER TIME PERIODS FOR DEMONSTRATION
bool demomode = true;

  // PROTOTYPES
String projectsRead();
int getNextID();
String *projectsList(String projekti);
int numOfProjects(String projekti);
void saveSessionStatus ();
String Statistics (bool save = false);

int buttonPressed();

void blueLEDStime (bool demo = false);
void blueLEDSOff ();

int buttonPressed ();
void changeProject(int changeDirection);
void recordingUPDATE ();
void recordingMODE ();
String Statistics (bool save = false);

void statsMODE();



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

  // SCREEN
  // Message should not be longer than 16 chars or it should be in two lines.
  String line_one = "";
  String line_two = "";
  String line_one_old = "";
  String line_two_old = "";
  bool screen_interrupt = false;

  // PROJECTS 
  String* listOfProjects = NULL;
  int numberOfProjects = 0;
  // currently open project
  int currentProject = 0;

  //RECORDING

  bool recordedStatus = false;
  int recordedID = 0;
   // time recorded h/m/s
  int recordedTime[3]= {0,0,0};
  int recordedProject= 0;
  unsigned long recordedStarted = 0;
  int lastSavedMIN = 0;

  //STATISTICS
  int statsInt[10];
  unsigned long lastUpdated=-6000;


  // SD
  int SDerror= 0;
  unsigned long SDerrorTime=-500;

  //LEDS
  unsigned long LEDStime = 10*60*1000;

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

  // load stats
  Statistics();

  //digitalWrite(36, HIGH);
}

void loop() {

 

// Serial.print("loopAhup");

  button=buttonPressed();

  if(recordedStatus){
     recordingUPDATE();
     blueLEDStime (demomode);}
  else {blueLEDSOff ();}

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
    statsMODE();
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

    // blinking red light in case of SD error
    if(SDerror != 0 && millis()-SDerrorTime>500) {
      SDerrorTime = millis();
      if(SDerror == 1) {
          digitalWrite(31, HIGH);
        SDerror=2;
      }
      else {
        digitalWrite(31, LOW);
        SDerror=1;
        }
    }

 

}
