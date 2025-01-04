#include <SoftwareSerial.h>

SoftwareSerial laaSerial(2, 3);  // RX, TX

void setup() {
  laaSerial.begin(115200);
  Serial.begin(9600);
}

void loop() {
  laaSerial.listen();
  String receivedString = "";
  int nCharsToRead = laaSerial.available();
  if (nCharsToRead > 0) {
    data += (char)laaSerial.read();
  };
  if ((nCharsToRead == 0 && receivedString != "")) return;

  Serial.println("received data is: " + String(data));
}