#include <SoftwareSerial.h>

SoftwareSerial laaSerial(2, 3);  // RX, TX

void setup() {
  laaSerial.begin(115200);
  Serial.begin(115200);
}

void loop() {
  laaSerial.listen();
  Serial.print(laaSerial.readStringUntil('\n'));
  // String receivedString = "";
  // int nCharsToRead = laaSerial.available();
  // if (nCharsToRead > 0) {
  //   receivedString += (char)laaSerial.read();
  //   Serial.println("nCharsToRead: " + String(receivedString));
  // };
  // if (!(nCharsToRead == 0 && receivedString != "")) return;

  // Serial.println("received data is: " + String(receivedString));
}