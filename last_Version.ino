
#include <Servo.h> //Including the servo library

Servo horizontal_servo; //Defining the horizontal servo motor
Servo vertical_servo; //Defining the vertical servo motor


int ldr_top = A0; //Correspondent anaolg pin number of LDR1
int ldr_bottom = A1; //Correspondent anaolg pin number of LDR2
int ldr_right = A2; //Correspondent anaolg pin number of LDR3
int ldr_left = A3; //Correspondent anaolg pin number of LDR4

int servopin_horizontal = 9; //Correspondent pin number of horizontal servo 
int servopin_vertical = 10; //Correspondent pin number of vertical servo

int sensitivity = 9;

void setup() {
   Serial.begin(9600);
   
   horizontal_servo.attach(servopin_horizontal); //Attaching the horizontal servo to a pin
   vertical_servo.attach(servopin_vertical); //Attaching the vertical servo to a pin
   
   horizontal_servo.write(90); //Setting the initial speed to 0
   vertical_servo.write(90); //Setting the initial speed to 0
  }

void loop() {
  
  int ldrA0 = analogRead(ldr_top); //Read the value from LDR connected to pin A0
  int ldrA1 = analogRead(ldr_bottom); //Read the value from LDR connected to pin A1
  int ldrA2 = analogRead(ldr_right); //Read the value from LDR connected to pin A2
  int ldrA3 = analogRead(ldr_left); //Read the value from LDR connected to pin A3
  
  //Measuring the ambient light intensity of the environment using serial monitor
  Serial.print("ldrA0: "); 
  Serial.println(ldrA0); 
  Serial.print("ldrA1: ");
  Serial.println(ldrA1);
  Serial.print("ldrA2: ");
  Serial.println(ldrA2); 
  Serial.print("ldrA3: ");
  Serial.println(ldrA3);
  
  //Declaring averages
  int avg_horizontal = (ldrA3 + ldrA2)/2;
  int avg_vertical = (ldrA0 + ldrA1)/2;
  int avg = (avg_horizontal + avg_vertical)/2;

  //Declaring differences
  int diff1_horizontal = abs(avg_horizontal - ldrA3);
  int diff2_horizontal = abs(avg_horizontal - ldrA2);

  int diff1_vertical = abs(avg_vertical - ldrA0);
  int diff2_vertical = abs(avg_vertical - ldrA1);

  //Declaring the speeds
  int horizontal_speed = abs(ldrA3-ldrA2)/20;
  int vertical_speed = abs(ldrA0-ldrA1)/10;
 
  
  //Controlling horizontal movement by making sure the servo 
  //rotates to left when the LDR on the left is exposed to a light
  //with higher intensity than the horizontal average light intensity
  //of left and right LDRs and the difference between
  //the left and right LDRs is greater than the sensitivity
  //and the horizontal average is higher than the average of all LDRs
  
  if((diff1_horizontal > sensitivity) && (avg_horizontal< ldrA3) && (avg_horizontal>avg)){ 
    horizontal_servo.write(90 + horizontal_speed); //Set rotation to counter-clockwise

  }
  
  //Controlling horizontal movement by making sure the servo 
  //rotates to right when the LDR on the right is exposed to a light
  //with higher intensity than the horizontal average light intensity
  //of left and right LDRs and the difference between
  //the right and left LDRs is greater than the error
  //and the horizontal average is higher than the average of all LDRs
  
  else if((diff2_horizontal > sensitivity) && (avg_horizontal<ldrA2) && (avg_horizontal>avg)){ 
    horizontal_servo.write(90 - horizontal_speed); //Set rotation to clockwise
  }
  else{
    horizontal_servo.write(90); ////Otherwise, there is no horizontal movement
  }

  //Controlling vertical movement by making sure the servo 
  //rotates upwards when the LDR on the top is exposed to a light
  //with higher intensity than the vertical average light intensity
  //of top and bottom LDRs and the difference between
  //the top and bottom LDRs is greater than the error
  //and the vertical average is higher than the average of all LDRs
  
  if((diff1_vertical >  sensitivity) && (avg_vertical< ldrA0) && (avg_vertical>avg)){
    vertical_servo.write(90 - vertical_speed); //Set rotation to clockwise
 
  }

  //Controlling vertical movement by making sure the servo 
  //rotates downwards when the LDR on the bottom is exposed to a light
  //with higher intensity than the vertical average light intensity
  //of bottom and top LDRs and the difference between
  //the bottom and top LDRs is greater than the error
  //and the vertical average is higher than the average of all LDRs
  
  else if((diff2_vertical > sensitivity) && (avg_vertical<ldrA1) && (avg_vertical>avg)){ 
    vertical_servo.write(90 + vertical_speed); //Set rotation to counter-clockwise

  }

  //Otherwise, there is no vertical movement 
  
  else{
    vertical_servo.write(90);  //Otherwise, there is no vertical movement 

   }

   //This algorithm also allows the solar tracker to keep 
   //no-movement condition when there system is exposed to an
   //additional light source at 90 degrees.
  
  delay(100);
  }
