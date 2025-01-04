#include <SoftwareSerial.h>

SoftwareSerial laaSerial(2, 3);  // RX, TX

void setup() { laaSerial.begin(115200); }

void loop() {
  laaSerial.listen();
  if (!laaSerial.isListening()) return;

  const String data = laaSerial.readString();
  laaSerial.println(data);
}