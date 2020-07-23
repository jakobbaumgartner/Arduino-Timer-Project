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


  int mode = 0;
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
  String* listOfProjects = NULL;
  int numberOfProjects = 0;

  int two = 0;
  int three = 0;
  int four = 0;
  int five = 0;
  int twelve = 0;

  int mill=0;


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

  buttonPressed();

  









  

  if(line_one != line_one_old || line_two != line_two_old) {

    /* Update LCD values if values of line_one or line_two strings have changed. */
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(line_one);
    lcd.setCursor(0,1);
    lcd.print(line_two);
  
    Serial.print("\n\n -- NEW DISPLAY -- ");
    Serial.print("\n------------------------------------------\n");
    Serial.print(line_one);
    Serial.print("\n");
    Serial.print(line_two);
    Serial.print("\n------------------------------------------\n");

    line_one_old = line_one;
    line_two_old = line_two;
    
    }

  

 

}
