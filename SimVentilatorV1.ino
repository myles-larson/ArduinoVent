#include <Servo.h>

Servo theServo; //Creates our servo object

int ratePin = 0;    //Pin for rate control potentiometer (pot) will be Analog 0
int depthPin = 1;   //Pin for depth control pot will be Analog 1
int rate;           //Integer variable to hold our rate value
int depth;          //Integer variable to hold our depth value
int pos;            //Integer variable to track our servo's current position
int homePos = 90;   //Home position we want for the servo (will likely need to be found experimentally)

void setup() {
  theServo.attach(9);   //Attach the servo object to pin 9
  theServo.write(homePos); //Sets initial servo position to 90 degrees (will need to be changed to whatever the servo's home is)
}

void loop() {
  depth = analogRead(depthPin);         //Gets the value (position) from the potentiometer
  depth = map(depth, 0, 1023, 0, 180);  //Maps the range of values the pot can produce to the range of degrees for our servo

  /* Next we get the value of the other pot and subtracts it from 1023. If we use delay(milliseconds) to control the rate
   * turning the knob left will mean smaller delay times and faster rate. So, subtracting our ratePin value from the maximum
   * value of the pot gives us the opposite effect. When we trun the knob left, our delay increases and slows the plunger.
   * We may need to change the 1023 baseline to something a little higher if the system doesn't like a delay of 0 or below
   * a certain value.
   */
  rate = 1023 - analogRead(ratePin);

  //The range control still needs to tweaking
  for (pos = homePos; pos <= depth; pos++)   //Start at our home position and move by 1 degree until we reach our depth
  {
    theServo.write(pos);  //Move the servo
    delay(rate);          //Wait for "rate" number of milliseconds between servo moves to create our overall rate
  }
  
  for (pos = homePos; pos >= depth; pos--)  //Start at our home position and move by 1 degree until we reach the opposite of depth
  {
    theServo.write(pos);  //Move the servo
    delay(rate);          //Wait for "rate" number of milliseconds between servo moves to create our overall rate
    //The rate could also be adjusted by changing our pos change from 1 to something higher until the servo's max speed is reached
  }
}
