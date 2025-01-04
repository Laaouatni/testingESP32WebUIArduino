#include <SoftwareSerial.h>

SoftwareSerial laaSerial(2, 3);  // RX, TX

void setup() { 
  laaSerial.begin(115200);
  Serial.begin(9600);
}

void loop() {
  laaSerial.listen();

  if(!laaSerial.available()) return; 
  const String data = laaSerial.readString();
  Serial.print("nuovi dati arrivati");
  Serial.println(data);
}