/*
Documentation:
Date: 4/16/25
Names: Abas Ismael, Artsiom Baranovich
Student ID numbers: 5975230, 5834715
Course number: CSE 1012
Term: Spring 2025
Lab/assignment number: Thursday Team 1 Final Project 
Short Program Description: Takes in input from joystick and moves two servos accordingly
References/Code Citations:
1. https://arduinogetstarted.com/tutorials/arduino-joystick
2. https://www.instructables.com/Arduino-Marble-Maze-Labyrinth/
*/


// Initalize Servos
#include <Servo.h>
Servo servoX;
Servo servoY;


// Initialize Pins
int xServoPin = 16;
int yServoPin = 15;


// Initialize X and Y Pos (Based on mounting)
int xPos = 95;
int yPos = 30;


// Joystick pin definitions
const int VERT = 26;  // Analog (check board)
const int HORIZ = 27; // Analog (check board)


const int delayTime = 0;


void setup() {
  // Attach Servos
   servoX.attach(xServoPin, 540, 2400);
   servoY.attach(yServoPin, 540, 2400);
   Serial.begin(9600);
   // Write Inital Positions
   servoX.write(xPos);
   servoY.write(yPos);
}




void loop() {
   int x = analogRead(HORIZ); // Read Horizontal Joystick movement (0-1023)
   int y = analogRead(VERT); // Read Vertical Joystick Movement   (0-1023)
 
  // This block slowly increments xServo towards new position from joystick input


  // Tolerance for being at rest is between (500-600) out of 1023
   if (x > 600 || x < 500) {
    int prevX = xPos;
    // Map joystick range (0-1023) to x-axis servo increment (0-40)
    int xInc = map(x, 0, 1023, 0, 40);
    xPos = 115- xInc; // Flipped Servo When Mounting, so joystick value is flipped by a factor
    // Checks whether new xPos is before or after prevX
    if (xPos > prevX) {
        // If after xPos is after, Slowly move towards new position
        for (int i = prevX; i < xPos; i+=5) {
          servoX.write(i);
          delay(delayTime);
      }
    } else {
        // Otherwise Slowly Move backwards
        for (int i = prevX; i > xPos; i-=5) {
          servoX.write(i);
          delay(delayTime);
      }
    }
    // If Servo is at rest, reset to inital position, assuming its not already there
   } else if (xPos != 95) {
    xPos = 95;
    servoX.write(95);
   }


   // This block slowly increments yServo towards new position from joystick input


  // Tolerance for being at rest is between (500-600) out of 1023
   if (y > 600 || y< 500) {
    int prevY = yPos;
    // Map joystick input (0-1023) to servo range (15,45)
    yPos = map(y, 0, 1023, 15, 45);
    // Checks whether new yPos is before or after prevY
    if (yPos > prevY) {
      // if yPos is after curr Pos, slowly move towards new Position,
        for (int i = prevY; i < yPos; i+=5) {
          servoY.write(i);
          delay(delayTime);
      }
    } else {
      // Otherwise, slowly move backward
        for (int i = prevY; i > yPos; i-=5) {
          servoY.write(i);
          delay(delayTime);
      }
    }
   } else if (yPos !=30) {
    yPos = 30;
    servoY.write(30);
   }
 


   // Display joystick values
   Serial.print("Vertical: "); Serial.print(y);
   Serial.print(" | Horizontal: "); Serial.print(x);


   // Display Servo Values
   Serial.print(" | Servo xPosition: "); Serial.print(xPos);
  Serial.print(" | Servo yPosition: "); Serial.println(yPos);


   delay(100); // Stabilization delay
}
