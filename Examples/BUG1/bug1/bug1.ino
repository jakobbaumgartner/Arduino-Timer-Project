void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

unsigned long i=0;
unsigned long recordedTime[3]= {0,0,0};
unsigned long recordedStarted = 0;

void loop() {
  // put your main code here, to run repeatedly:
  i=i+10000;
  recordedTime[0] = (i-recordedStarted)/3600000;
  recordedTime[1] = floor((i-recordedStarted)/60000)-recordedTime[0]*60;
  recordedTime[2] = floor((i-recordedStarted)/1000)-recordedTime[1]*60-recordedTime[0]*3600;
Serial.println(String(recordedTime[0]) + "h : " + String(recordedTime[1]) + "m : " + String(recordedTime[2]) + "s");
}
