// include library
#include <ESP8266WiFi.h>
#include <Servo.h>
#define SERVO_PIN 5 // define servo pin
// set ESP8266 SSID and Password
const char WiFiPassword[] = "";
const char AP_NameChar[] = "SMART_TRASH" ;


String request = "";//save request variable
bool auto_state = false;

WiFiServer server(80);// set port server mode

Servo myservo;// creat servo objects

// HTML code
String html_1 = "<!DOCTYPE html><html lang='en'><head>  <meta charset='UTF-8'>  <meta http-equiv='X-UA-Compatible' content='IE=edge'>  <meta name='viewport' content='width=device-width, initial-scale=1.0'>  <title>سطل زباله هوشمند</title>";
String html_11 = "<style> .pageTitle-container{width: 100%;text-align: center; } .pageTitle-title{font-size: 35px;padding-top: 30px; color: rgb(48, 86, 129); } .pageButton-buttonContainer{text-align: center;} .pageButton-openButton{width: 110px;height: 110px;border-radius: 100%;border: 4px lightgreen solid;color: lightgreen;background: white;font-size: 20px;box-shadow: 0px 0px 8px lightgrey; } .pageButton-closeButton{width: 110px;height: 110px;border-radius: 100%;border: 4px #f44336 solid;color: #f44336;background: white;font-size: 20px;box-shadow: 0px 0px 8px lightgrey; } .toggle-button-cover{ display: flex; justify-content: center; width: 100%; height: 140px; box-sizing: border-box;}.button-cover{ height: 100px; margin: 20px; background-color: #fff; box-shadow: 0 10px 20px -8px #c5d6d6; border-radius: 4px;}.button-cover:before{ counter-increment: button-counter; content: counter(button-counter); position: absolute; right: 0; bottom: 0; color: #d7e3e3; font-size: 12px; line-height: 1; padding: 5px;}.button-cover, .knobs, .layer{ position: absolute; top: 0; right: 0; bottom: 0; left: 0;}.button{ position: relative; top: 50%; width: 115px; height: 48px; margin: -20px auto 0 auto; overflow: hidden;}.button.r, .button.r .layer{ border-radius: 100px;}.button.b2{ border-radius: 2px;}.checkbox{ position: relative; width: 100%; height: 100%; padding: 0; margin: 0; opacity: 0; cursor: pointer; z-index: 3;}.knobs{ z-index: 2;}.layer{ width: 100%; background-color: #ebf7fc; transition: 0.3s ease all; z-index: 1;}#button-1 .knobs:before{ padding-top: 10px; content: 'Auto'; position: absolute; top: 5px; left: 4px; width: 49px; height: 20px; color: #fff; font-size: 15px; text-align: center; line-height: 1; padding: 9px 4px; background-color: #03A9F4; border-radius: 20px; transition: 0.3s cubic-bezier(0.18, 0.89, 0.35, 1.15) all;}#button-1 .checkbox:checked + .knobs:before{ content: 'Man'; left: 54px; background-color: #f44336;}#button-1 .checkbox:checked ~ .layer{ background-color: #fcebeb;}#button-1 .knobs{  padding-top: 10px;}#button-1 .knobs, #button-1 .knobs:before, #button-1 .layer{ transition: 0.3s ease all;}  </style></head>";
String html_12 = "<body>  <div class='pageTitle-container'> <h4 class='pageTitle-title'>سطل زباله هوشمند</h4>  </div>  <div class='pageButton-buttonContainer'>  <form  >";
String html_2 = "<button type='submit' value='close' name='btn' class='pageButton-closeButton'>Close</button>";
String html_4 = "<div class='toggle-button-cover'><div class=''><div class='button r' id='button-1'><input type='checkbox' checked name='auto' class='checkbox'><div class='knobs'></div><div class='layer'></div></div></div></div></form></div></body></html>";

const int pingPin = 12; // Ping Pin of Ultrasonic Sensor
const int echoPin = 14; // Echo Pin of Ultrasonic Sensor

void setup()
{
  WiFi.softAP(AP_NameChar, WiFiPassword);//config AP Mode

  server.begin();// config server Mode

  // put your setup code here, to run once:
  // Sets the pingPin as an Output
  pinMode(pingPin, OUTPUT);
  // Sets the echoPin as an Input
  pinMode(echoPin, INPUT);
  // Starting Serial Terminal
  Serial.begin(9600);
  // Attaches the servo on pin 10 to the servo object
  myservo.attach(SERVO_PIN);
  delay(10);
  // Set servo to 45, this will preset the trash can door to close
  myservo.write(45);
  delay(1000);
  // Disable the servo
  myservo.detach();
  delay(1000);

} // void setup()



void loop()
{

  //check Mode auto or Manual
  if (auto_state == true) {
    Serial.println(auto_state);
    Auto_mode();
  }

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client)  {
    return;
  }

  // Read the first line of the request
  request = client.readStringUntil('\r');

  if  ( request.indexOf("auto") > 0 ) {

    html_4 = "<div class='toggle-button-cover'><div class=''><div class='button r' id='button-1'><input type='checkbox' checked name='auto' class='checkbox'><div class='knobs'></div><div class='layer'></div></div></div></div></form></div></body></html>";
    auto_state = false;
    Serial.print(auto_state);
  }
  else if ( request.indexOf("btn") > 0 && !(request.indexOf("auto") > 0)) {
    html_4 = "<div class='toggle-button-cover'><div class=''><div class='button r' id='button-1'><input type='checkbox' name='auto' class='checkbox'><div class='knobs'></div><div class='layer'></div></div></div></div></form></div></body></html>";
    auto_state = true;
    Serial.print(auto_state);

  }



  if (auto_state == false) {
    if       ( request.indexOf("open") > 0)  {
      html_2 = "<button type='submit' value='close' name='btn' class='pageButton-closeButton'>Close</button>";
      Manual_mode(120);

    }
    else if  ( request.indexOf("close") > 0) {
      html_2 = "<button type='submit' value='open' name='btn' class='pageButton-openButton'>Open</button>";
      Manual_mode(45);

    }
  }
// Published HTML code 
  client.flush();
  client.print( html_1 );
  client.print( html_11 );
  client.print( html_12 );
  client.print( html_2 );
  client.print( html_4);

  delay(5);

}

void Auto_mode() {

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
    myservo.attach(SERVO_PIN);
    // Set servo to 120, this will open the trash can door
    myservo.write(120);
    delay(3500);
    // Set servo to 45, this will close the trash can door
    myservo.write(45);
  }
}
void Manual_mode(int angle) {

  myservo.attach(SERVO_PIN);// set servo pin
  myservo.write(angle);//write servo angle
}
