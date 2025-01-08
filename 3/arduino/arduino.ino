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
  // Serial.println("arduino isButtonClicked: " + String(isButtonClicked));
  digitalWrite(arduinoComponents.led, isButtonClicked || clientLedStatus);
  const int isLedOn = digitalRead(arduinoComponents.led);
  // Serial.println("valore led arduino: " + String(isLedOn));
  const bool canSendButtonData =
      isButtonClicked != wasButtonClicked;
      // && isLedOn != clientLedStatus;

  // Serial.println(canSendButtonData ? "✅ arduino può mandare il messaggio" : "❌ valore vecchio, non mando nessun json");

  if (canSendButtonData) {
    const String jsonResponse = "arduino:{'button':" + String(isButtonClicked) +
                                ",'isLedOn':" + String(isLedOn) + "}";

    Serial2.println(jsonResponse);
    Serial.println("➡️ arduino ha mandato al client il json: " + jsonResponse);
  };

  wasButtonClicked = isButtonClicked;
}

void myCallback(String esp32value) {
  Serial.println("⬅️ ho ricevuto un messaggio: " + esp32value);
  const int isClient = esp32value.indexOf("client") != -1;
  Serial.println(isClient ? "⬅️ è stato il client a mandare il messaggio: " + String(esp32value) : "⬅️ è stato probabilmente arduino a mandare il messaggio oppure il formato è diverso");
  if (!isClient) return;
  const int isLedOn = esp32value.indexOf("isLedOn:1") != -1;
  Serial.println("⬅️ valore led client: " + String(isLedOn));
  clientLedStatus = isLedOn;
};

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