#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);


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
  String line_two = "Loading ...";
  String line_one_old = "";
  String line_two_old = "";
  

void setup() {

  // start serial 
  Serial.begin(9600);
  
  
  // initialize the LCD
  lcd.begin();
  lcd.backlight();

  lcd.setCursor(0,1);
  lcd.print("Loading ...");
  
  
 
   
}

void loop() {

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
