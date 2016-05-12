#include <sparki.h>
  
  float xI = 0;
  float yI = 0;
  float tI = 0;
  float tnot = 0;


void setup() {
  // put your setup code here, to run once:
  

}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long timeStart = millis();
  
  float xR = 0;
  float tR = 0;
  float dim = .085; //        m
  float speed = .02717; //    m/s
  int threshold = 500;
  float xItemp = 0;
  float yItemp = 0;
  float tItemp = 0;
  
 
  int lineLeft   = sparki.lineLeft();   // measure the left IR sensor
  int lineCenter = sparki.lineCenter(); // measure the center IR sensor
  int lineRight  = sparki.lineRight();  // measure the right IR sensor
 
  if ( lineLeft < threshold ) // if line is below left line sensor
  {  
    sparki.moveLeft(); // turn left
    xR = speed/2;
    tR = -1*(speed/dim);
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
  float dt = 0.1; //seconds

  xItemp = xI + cos(tItemp)*xR*dt; //cm
  yItemp = yI + sin(tItemp)*xR*dt; //cm
  tItemp = tI + tR*dt;

  xI = xItemp;
  yI = yItemp;
  tI = tItemp;
  
  
  //xI = xI + cos(tnot)*xR*dt;
  //yI = yI + sin(tnot)*xR*dt;
  //tI = tI + tR*dt;
  
  //tnot = atan2(yItemp, xItemp);

  sparki.clearLCD(); // wipe the screen
 
  sparki.print("xI: "); // show left line sensor on screen
  sparki.println(xI, 4);
 
  sparki.print("yI: "); // show center line sensor on screen
  sparki.println(yI, 4);
 
  sparki.print("thetaI(deg): "); // show right line sensor on screen
  sparki.println(tItemp*(180/3.14), 4);
 
  sparki.updateLCD();

  unsigned long timeEnd = millis();
  delay(100 - (timeEnd - timeStart)); // wait 0.1 seconds

  

}
