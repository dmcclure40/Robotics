#include <sparki.h>

//            Lane #
//        | 0 | 1 | 2 |
//        |   |   |   |
//        |   |   |   |
//        |   |   |   |
          
// Start in the middle lane
int current_lane = 1;

bool check_right() {
  sparki.moveStop();
  delay(400);
  for (int angle = 90; angle > 60; angle--) {
    delay(100);
    sparki.servo(angle);
    delay(100);
    int cm = sparki.ping();
    Serial.println("Checking Right");
    Serial.println(cm);
    if (cm == -1) {continue;}
    if (cm < 20) {
      return true;
    }
    
  }
  return false;
}

bool check_left() {
  
  sparki.moveStop();
  delay(600);
  for (int angle = -90; angle < -60; angle++) {
    delay(100);
    sparki.servo(angle);
    delay(200);
    int cm = sparki.ping();
    Serial.println("Checking Left");
    Serial.println(cm);
    if (cm == -1) {continue;}
    if (cm < 20) {
      return true;
    }
  }
  return false;
  
}
void switch_lane_left() {
  // Start moving left
  sparki.motorRotate(MOTOR_LEFT, DIR_CCW, 20);
  sparki.motorRotate(MOTOR_RIGHT, DIR_CW, 100);
  delay(3000);

  sparki.moveForward(15);

  //start moving right
  sparki.motorRotate(MOTOR_LEFT, DIR_CCW, 100);
  sparki.motorRotate(MOTOR_RIGHT, DIR_CW, 20);
  delay(3000);
  
  current_lane--;
  main_loop();
  
}
void switch_lane_right() {
  // Start moving right
  sparki.motorRotate(MOTOR_LEFT, DIR_CCW, 100);
  sparki.motorRotate(MOTOR_RIGHT, DIR_CW, 20);
  delay(3000);

  sparki.moveForward(15);

  //start moving left
  sparki.motorRotate(MOTOR_LEFT, DIR_CCW, 20);
  sparki.motorRotate(MOTOR_RIGHT, DIR_CW, 100);
  delay(3000);
  
  current_lane++;
  main_loop();  
}

void main_loop() {
  //Serial.println("current lane: ");
  //Serial.println(current_lane);

  sparki.servo(0);
  int z_pos = sparki.ping();
  //Serial.println(z_pos);
  
  //start moving forward
  sparki.moveForward();
  if (z_pos <= 17) {    
    //sparki.moveForward();
    
    // In left lane
    if (current_lane == 0) {
      //check lane to right -> true if blocked
      if (check_right()) {
        sparki.moveStop();
        delay(1000);
        main_loop();
      }
      
      //otherwise change lanes
      sparki.moveStop();
      switch_lane_right();
    }

    // In right lane
    if (current_lane == 2){
      // Check lane to left -> true if blocked
      if (check_left()) {
        sparki.moveStop();
        delay(1000);
        main_loop();
      }
      
      //otherwise change lanes
      sparki.moveStop();
      switch_lane_left();
    }
    
    // In middle lane
    if (current_lane == 1) {
      // If both lanes are bolcked stop
      if (check_left()) {
        if (check_right()) {
          sparki.moveStop();
          delay(1000);
          main_loop();
        }
        sparki.moveStop();
        switch_lane_right();
        
      }
      sparki.moveStop();
      delay(1000);
      switch_lane_left();

    }
    
  }
  main_loop();
  
}

void setup() {
  // put your setup code here, to run once:
  sparki.servo(0);
  main_loop();

}

void loop() {
  // put your main code here, to run repeatedly:

}
