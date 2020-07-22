int buttonPressed () {

  int buttonNumber = NULL;

  if(digitalRead(2)) {buttonNumber=2;}
  if(digitalRead(3)) {buttonNumber=3;}
  if(digitalRead(4)) {buttonNumber=4;}
  if(digitalRead(5)) {buttonNumber=5;}
  if(digitalRead(12)) {buttonNumber=12;}
  

  return buttonNumber;
}
