#include <sparki.h>

  // Global variables
  float xI = 0;
  float yI = 0;
  float tI = 0;

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:

  // Record start time of loop
  unsigned long timeStart = millis();
  
  float xR = 0;             // m/s
  float tR = 0;             // rads/sec
  float dim = .084;         // m
  float speed = .02717;     // m/s
  float dt = 0.1;           // seconds
 
  int threshold = 500;
  int lineLeft   = sparki.lineLeft();   // measure the left IR sensor
  int lineCenter = sparki.lineCenter(); // measure the center IR sensor
  int lineRight  = sparki.lineRight();  // measure the right IR sensor
 
  if ( lineLeft < threshold ) // if line is below left line sensor
  {  
    sparki.moveLeft(); // turn left
    // Update position and speed of the Robot's coordinate frame
    xR = 0;
    tR = -2*(speed/dim);
  }
 
  if ( lineRight < threshold ) // if line is below right line sensor
  {  
    sparki.moveRight(); // turn right
    // Update position and speed of the Robot's coordinate frame
    xR = 0;
    tR = 2*speed/dim;
  }
 
  // if the center line sensor is the only one reading a line
  if ( (lineCenter < threshold) && (lineLeft > threshold) && (lineRight > threshold) )
  {
    sparki.moveForward(); // move forward
    // Update position and speed of the Robot's coordinate frame
    xR = speed;
    tR = 0;
  }  

  // Update Inertial Frame position based on odometry, using global variables
  xI = xI + cos(tI)*xR*dt; // m
  yI = yI + sin(tI)*xR*dt; // m
  tI = tI + tR*dt;         // rad

  // Print position and orientation to the screen
  sparki.clearLCD(); 
  
  sparki.print("xI: "); 
  sparki.println(xI, 4);
 
  sparki.print("yI: "); 
  sparki.println(yI, 4);
 
  sparki.print("thetaI(deg): "); 
  sparki.println(tI*(180/3.14), 2); // converted to degrees for ease of reading
 
  sparki.updateLCD();

  // Record end timer and then institue the 100ms delay
  unsigned long timeEnd = millis();
  delay(100 - (timeEnd - timeStart)); // wait 0.1 seconds

}
