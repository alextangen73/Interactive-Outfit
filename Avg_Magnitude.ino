// This includes a file that has functions for the IMU
#include <SparkFunLSM6DS3.h>


LSM6DS3 myIMU;


float movementThreshold = 1.10;
float highMovementThreshold = 1.30;
float cutOff = .9;
float cutOff2 = .76;
int runningTotal;
int counter = 0;
int brightness = 0;
int brightness2 = 0;
int fadeAmount = 4;
int fadeAmount2 = 6;

void setup() {
  // put your setup code here, to run once:
// put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(11, OUTPUT); //blue lights
  pinMode(10, OUTPUT); //purple/blacklight lights
  pinMode(9, OUTPUT); //multicolor lights
  
  delay(1000); //relax...
  Serial.println("Processor came out of reset.\n");
  
  //Call .begin() to configure the IMU
  myIMU.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
//while(counter < 100) {
float avgMag = 0;
for(int x = 0 ; x < 8 ; x++)
{
float    aX = myIMU.readFloatAccelX();
float   aY = myIMU.readFloatAccelY();
   float  aZ = myIMU.readFloatAccelZ();

  Serial.println(aX);
  Serial.println(aY);
  Serial.println(aZ);
 
   //Serial.println(analogRead(myIMU.readFloatAccelX()));
   //Serial.println(analogRead(myIMU.readFloatAccelY()));
   //Serial.println(analogRead(myIMU.readFloatAccelZ())); 

    float magnitude = sqrt((aX * aX) + (aY * aY) + (aZ * aZ)); //Combine all vectors 
    avgMag += magnitude; // avgMag = avgMag + magnitude
}
avgMag /= 8;
//runningTotal += avgMag; } 

 
Serial.print("Average Magnitude: ");
Serial.println(avgMag);


float measuredValue = avgMag;
/*
//Average all the values
int counter = 0;
int measuredValue = 0;
while ( counter < 100) {
  measuredValue += avgMag;
  counter++;
}
measuredValue = measuredValue/ 100;
*/

Serial.print("Measured Value: ");
Serial.println(measuredValue);
delay(2000); //comment out to make more fluid



//If wearer is not moving, no light
if ( cutOff< measuredValue && measuredValue < movementThreshold) {

    Serial.println("No Movement");
    //for testing
    
 analogWrite(11, 190);   // turns on a brightness of 255-190
 analogWrite(10, 150); 
 digitalWrite(9, HIGH);  // turn the LED on (HIGH is the voltage level)
    
}


//Wearer is moving slowly
else if ( (measuredValue > movementThreshold && measuredValue < highMovementThreshold) || (cutOff2 < measuredValue && measuredValue < cutOff)) { //adding parenthesis () will perform that operation first

   //for testing // || means or
   Serial.println("Slow Movement");
   digitalWrite(9, HIGH);
  for (int counter =0; counter <100; counter++) {  
analogWrite(11, 255-brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness == 150 || brightness == 255) {
    fadeAmount = -fadeAmount ;
    //delay(2000);
   
}
  delay(40);
 analogWrite(10, 255-brightness2); 
 // change the brightness for next time through the loop:
  brightness2 = brightness2 + fadeAmount2;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness2 == 0 || brightness2 == 255) {
    fadeAmount2 = -fadeAmount2 ;
}
}
}

//Wearer is moving fast
else { 

Serial.println("High Movement");  //for testing
  
{  for (int counter =0; counter <12; counter++) {
 analogWrite(11, 150);   // turn the LED on (HIGH is the voltage level)
  delay(50);              // wait for a second
  analogWrite(11, 255);    // turn the LED off by making the voltage LOW
  delay(50);              // wait for a second  
  digitalWrite(10, LOW);
  delay(150);
  digitalWrite(10, HIGH);
  delay(150);
 digitalWrite(9,LOW);
 }
    
}
}

//reset the values
//counter =0;
//measuredValue =0;
}







