#include <Ultrasonic.h>

// ---------------------------------------------------------------- //
// Arduino Ultrasoninc Sensor HC-SR04
// Re-writed by Arbi Abdul Jabbaar
// Using Arduino IDE 1.8.7
// Using HC-SR04 Module
// Tested on 17 September 2019
// ---------------------------------------------------------------- //

//#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
//#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04
//
//// defines variables
// long duration; // variable for the duration of sound wave travel
// int distance; // variable for the distance measurement
//
// void setup() {
//   pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
//   pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
//   Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
//   Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
//   Serial.println("with Arduino UNO R3");
// }
// void loop() {
//   // Clears the trigPin condition
//   digitalWrite(trigPin, LOW);
//   delayMicroseconds(2);
//   // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
//   digitalWrite(trigPin, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trigPin, LOW);
//   // Reads the echoPin, returns the sound wave travel time in microseconds
//   duration = pulseIn(echoPin, HIGH);
//   // Calculating the distance
//   distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
//   // Displays the distance on the Serial Monitor
//   Serial.print("Distance: ");
//   Serial.print(distance);
//   Serial.println(" cm");
// }

#define POWER_PIN 7
#define SIGNAL_PIN A5
#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 // attach pin D3 Arduino to pin Trig of HC-SR04

long duration; // variable for the duration of sound wave travel
int distance;  // variable for the distance measurement
int value = 0; // variable to store the sensor value
char temp[50];

void setup()
{
    Serial.begin(9600);
    pinMode(POWER_PIN, OUTPUT);   // configure D7 pin as an OUTPUT
    digitalWrite(POWER_PIN, LOW); // turn the sensor OFF
    pinMode(trigPin, OUTPUT);     // Sets the trigPin as an OUTPUT
    pinMode(echoPin, INPUT);      // Sets the echoPin as an INPUT
}

void loop()
{
    String data = "";
    // Clears the trigPin condition
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    // Displays item status
    if (distance > 10)
    {
        data.concat("0 ");
    }
    else
        data.concat("1 ");

    digitalWrite(POWER_PIN, HIGH);  // turn the sensor ON
    delay(10);                      // wait 10 milliseconds
    value = analogRead(SIGNAL_PIN); // read the analog value from sensor
    digitalWrite(POWER_PIN, LOW);   // turn the sensor OFF

    //  Serial.println(value);

    value -= 200;
    float calculate = value * 100 / 120;
    if (calculate > 100)
    {
        data.concat(100.00);
    }
    else if (calculate > 0)
    {
        data.concat(calculate);
    }
    else
    {
        data.concat("0");
    }
    Serial.println(data);

    delay(1000);
}