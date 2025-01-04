#include <SoftwareSerial.h>

SoftwareSerial laaSerial(2, 3);  // RX, TX

void setup() {
  laaSerial.begin(115200);
  Serial.begin(115200);
}

void loop() {
  laaSerial.listen();
  
  listenToNewSerialData(&myPrintln);
  listenToNewSerialData(&myPrintln);
}

void myPrintln(String value) {
  Serial.println("received from esp32: " + value);
}

String listenToNewSerialData(void (*myCallback)(String)) {
  static String receivedString;

  while (laaSerial.available() > 0) {
    const char thisChar = laaSerial.read();
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