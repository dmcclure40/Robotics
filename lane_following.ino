#include <Wire.h>
#include <ZX_Sensor.h>
#include <sparki.h>

bool left_lane = false;
bool center_lane = true;
bool right_lane = false;

bool check_right();
bool check_left();
void switch_lane_left();
void switch_lane_right();


void setup() {
  // put your setup code here, to run once:

}



void loop() {
  // put your main code here, to run repeatedly:

  if (xz < threshold) {
    // In left lane
    if (left_lane) {
      //check lane to right -> true if blocked
      if (check_right) {
        //stop
      }
      //otherwise chsange lanes
      switch_lane_right();
    }

    // In right lane
    if (right_lane){
      // Check lane to left -> true if blocked
      if (check_left) {
      //stop
      }
      //otherwise chsange lanes
      switch_lane_left();
    }
    
    // In middle lane
    // Check lane to left -> true if blocked
    if (check_left) {
      // If both lanes are bolcked stop
      if (check_right) {
        //stop
      }
      //otherwise right lane is free
      switch_lane_right();
    }
    //otherwise left lane is free
    switch_lane_left();
    
  }

}
