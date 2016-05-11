#include <sparki.h>
  
  int xI = 0;
  int yI = 0;
  int tI = 0;
  int tnot = 0;


void setup() {
  // put your setup code here, to run once:
  

}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long timeStart = millis();
  
  int xR = 0;
  int tR = 0;
  int dim = 0.085; //        m
  int speed = 0.02717; //    m/s
  int threshold = 500;
  int xItemp = 0;
  int yItemp = 0;
  int tItemp = 0;
  
 
  int lineLeft   = sparki.lineLeft();   // measure the left IR sensor
  int lineCenter = sparki.lineCenter(); // measure the center IR sensor
  int lineRight  = sparki.lineRight();  // measure the right IR sensor
 
  if ( lineLeft < threshold ) // if line is below left line sensor
  {  
    sparki.moveLeft(); // turn left
    xR = speed/2;
    tR = -speed/dim;
  }
 
  if ( lineRight < threshold ) // if line is below right line sensor
  {  
    sparki.moveRight(); // turn right
    xR = speed/2;
    tR = speed/dim;
  }
 
  // if the center line sensor is the only one reading a line
  if ( (lineCenter < threshold) && (lineLeft > threshold) && (lineRight > threshold) )
  {
    sparki.moveForward(); // move forward
    xR = speed;
    tR = 0;
  }  

  /*
  sparki.clearLCD(); // wipe the screen
 
  sparki.print("Line Left: "); // show left line sensor on screen
  sparki.println(lineLeft);
 
  sparki.print("Line Center: "); // show center line sensor on screen
  sparki.println(lineCenter);
 
  sparki.print("Line Right: "); // show right line sensor on screen
  sparki.println(lineRight);
 
  sparki.updateLCD(); // display all of the information written to the screen
  */
  int dt = 0.1; //seconds

  xItemp = xI + cos(tnot)*xR*dt;
  yItemp = yI + sin(tnot)*xR*dt;
  tItemp = tI + tR*dt;

  xI = xItemp;
  yI = yItemp;
  tI = tItemp;
  
  
  //xI = xI + cos(tnot)*xR*dt;
  //yI = yI + sin(tnot)*xR*dt;
  //tI = tI + tR*dt;
  
  tnot = atan(yItemp/xItemp);

  sparki.clearLCD(); // wipe the screen
 
  sparki.print("xI: "); // show left line sensor on screen
  sparki.println(xItemp);
 
  sparki.print("yI: "); // show center line sensor on screen
  sparki.println(yItemp);
 
  sparki.print("thetaI: "); // show right line sensor on screen
  sparki.println(tItemp);
 
  sparki.updateLCD();

  unsigned long timeEnd = millis();
  delay(100 - (timeEnd - timeStart)); // wait 0.1 seconds

  

}
