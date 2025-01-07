#include <SoftwareSerial.h>
SoftwareSerial Serial2(2, 3);  // RX, TX

struct ArduinoComponents {
  const int led = 7;
  const int button = 5;
} arduinoComponents;

void setup() {
  Serial2.begin(9600);
  Serial.begin(9600);

  pinMode(arduinoComponents.led, OUTPUT);
  pinMode(arduinoComponents.button, INPUT);
}

bool wasButtonClicked = false;
bool clientLedStatus = false;

void loop() {
  listenToNewSerialData(&myCallback);

  const int isButtonClicked = digitalRead(arduinoComponents.button);
  digitalWrite(arduinoComponents.led, isButtonClicked || clientLedStatus);
  const int isLedOn = digitalRead(arduinoComponents.led);
  const bool canSendButtonData =
      isButtonClicked != wasButtonClicked || isLedOn != clientLedStatus;

  if (canSendButtonData) {
    Serial2.println(String("{'button':")
                        .concat(String(isButtonClicked))
                        .concat(",'isLedOn':")
                        .concat(String(isLedOn))
                        .concat("}"));
  };

  wasButtonClicked = isButtonClicked;
}

void myCallback(String esp32value) {}

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