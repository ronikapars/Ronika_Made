/****************************************************************/
/*
  Ronika_Made.ino - The main program for controlling
  light with clapping.
  Author: Mojtaba Zare, Ronika Co. Ltd., Oct 24, 2020.
  Released into the public domain.
*/
/****************************************************************/

int micPin = A0;          // pin that the mic is attached to
int micValue1 = 0;        // variables to store mic values
int micValue2 = 0;        // variables to store mic values
int led = 2;             // pin that the led is attached to
boolean lightOn = false;  // two state variable

void setup() {
  // put your setup code here, to run once:
  // Set led pin as OUTPUT
  pinMode(led, OUTPUT);

  // Set micPin pin as INPUT
  pinMode(micPin, INPUT);

  // Starting Serial Terminal
  Serial.begin(112500);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Read microphone pin voltage
  micValue1 = analogRead(micPin);
  Serial.print("Mic Value 1: ");
  Serial.print(micValue1); // print out micValue1
  Serial.print("\tMic Value 2: ");
  // Wait a moment
  delay(2);
  // Read microphone pin voltage
  micValue2 = analogRead(micPin);
  Serial.println(micValue2); // print out micValue2

  // Check to see if there is any difference between the two measurements
  if (micValue1 - micValue2 > 50 || micValue2 - micValue1 > 50) {
    lightOn = !lightOn; // Toggle lightOn state
    delay(500); // Wait a little
    digitalWrite(led, lightOn); // Write the state to the pin
  }
}