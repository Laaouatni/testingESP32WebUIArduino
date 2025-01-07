#include <SoftwareSerial.h>

SoftwareSerial Serial2(2, 3);  // RX, TX

bool wasButtonClicked = false;

void setup() {
  Serial2.begin(9600);
  Serial.begin(9600);

  pinMode(5, OUTPUT);
  pinMode(8, INPUT);
}

void loop() {
  listenToNewSerialData(&myCallback);

  const int isButtonClicked = digitalRead(8);
  if(isButtonClicked != wasButtonClicked) {
    Serial2.println("$digitalRead(8)=" + String(isButtonClicked));
  };
  digitalWrite(5, isButtonClicked);

  wasButtonClicked = isButtonClicked;
}

void myCallback(String esp32value) {
  Serial.println("received from esp32: " + esp32value);
}

String listenToNewSerialData(void (*myCallback)(String)) {
  static String receivedString;

  while (Serial2.available() > 0) {
    const char thisChar = Serial2.read();
    const bool isLastChar = thisChar == '\n';

    if (!isLastChar) {
      receivedString += thisChar;
      continue;
    };

    myCallback(receivedString);
    receivedString = "";
  };

  return "";
};