/**********************/
/*
  Ronika_Made.ino - The main program for controlling trash can door.
  Author: Mojtaba Zare, Oct 11, 2020.
  Released into the public domain.
*/
/**********************/
#include <Servo.h>

// Create servo object to control a servo
Servo myservo;

const int pingPin = 13; // Ping Pin of Ultrasonic Sensor
const int echoPin = 12; // Echo Pin of Ultrasonic Sensor

void setup() {
  // put your setup code here, to run once:
  // Sets the pingPin as an Output
  pinMode(pingPin, OUTPUT);
  // Sets the echoPin as an Input
  pinMode(echoPin, INPUT);
  // Starting Serial Terminal
  Serial.begin(9600);
  // Attaches the servo on pin 10 to the servo object
  myservo.attach(10);
  delay(10);
  // Set servo to 45, this will preset the trash can door to close
  myservo.write(45);
  delay(1000);
  // Disable the servo
  myservo.detach();
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Reset distance to zero
  long distance = 0;
  for (int i = 0; i < 10; i++) {
    // Clears the pingPin
    digitalWrite(pingPin, LOW);
    delayMicroseconds(10);
    // Sets the pingPin on HIGH state for 10 micro seconds
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(10);
    // Clears the pingPin
    digitalWrite(pingPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    unsigned long duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance += duration / 59;
    // Wait a moment
    delay(5);
  }
  // Do so to average the measurements
  distance /= 10;

  // Check to see if distance is between 8 - 20 cm
  if (distance > 8 && distance < 20) {
    // Enable the servo on pin 10
    myservo.attach(10);
    // Set servo to 120, this will open the trash can door
    myservo.write(120);
    delay(3500);
    // Set servo to 45, this will close the trash can door
    myservo.write(45);
    delay(1000);
    // Disable the servo
    myservo.detach();
  }

  // Prints the distance on the Serial Monitor
  // !: it's an option, you can comment it
  Serial.print("Distance: ");
  Serial.println(distance);

  // Repeat the loop with a delay
  delay(10);
}