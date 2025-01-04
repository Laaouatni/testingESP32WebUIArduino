#include <SoftwareSerial.h>

SoftwareSerial Serial2(2, 3);  // RX, TX

void setup() {
  Serial2.begin(115200);
  Serial.begin(115200);
}

void loop() {
  Serial2.listen();

  listenToNewSerialData(&myPrintln);
}

void myPrintln(String value) {
  Serial.println("received from esp32: " + value);
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