#include <Servo.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "CGC";
const char* password = "14141414";
const int servo_unlocked = 70;
const int servo_locked = 120;
const int servo_pin = 2; // D4
const int locked_led_pin = 13; //D7
const int unlocked_led_pin = 15; //D8

Servo servo;

void setup() {
  Serial.begin(9600);
  connectWifi();
  startServo();
  startLeds();
}

void startLeds() {
  pinMode(unlocked_led_pin, OUTPUT);
  pinMode(locked_led_pin, OUTPUT);
}

void startServo() {
  servo.attach(servo_pin);
  lockDoor();
}

void connectWifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    // Serial.print("Connecting to wifi");
  }
  // Serial.print("Connected!");
}

void loop() {
  checkServer();
}

void checkServer() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://doors.waska.cf/ka/check/etWvdVx1xGDS9xY");
    int httpCode = http.GET();
    if (httpCode > 0) {
      String response = http.getString();
      serverResponse(response);
    }
    http.end();
  }
  delay(1000);
}

void serverResponse(String response) {
  if (response == "1") {
    if (servo.read() != servo_unlocked) {
      unlockDoor();
      delay(1000);
    }
  } else {
    if (servo.read() != servo_locked) {
      lockDoor();
      delay(1000);
    }
  }
}

void unlockDoor() {
  //servo.write(servo_unlocked);
  for (int i = servo_locked; i >= servo_unlocked; i--) {
    servo.write(i);
    delay(10);
  }
  digitalWrite(locked_led_pin, LOW);
  digitalWrite(unlocked_led_pin, HIGH);
}

void lockDoor() {
  // servo.write(servo_locked);
  for (int i = servo_unlocked; i <= servo_locked; i++) {
    servo.write(i);
    delay(10);
  }
  digitalWrite(unlocked_led_pin, LOW);
  digitalWrite(locked_led_pin, HIGH);
}

