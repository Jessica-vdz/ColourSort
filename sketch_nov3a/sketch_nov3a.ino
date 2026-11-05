#include <Servo.h>
#include <Arduino_APDS9960.h>

Servo detect;
Servo doorRed;
Servo doorBlue;
Servo doorGreen;

int r, g, b;
int led = 6;
int button = 7;

bool started = false;
int buttonState = HIGH;
int lastButtonState = HIGH;

void setup() {
  Serial.begin(9600);

  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  if (!APDS.begin()) {
    Serial.println("APDS error!");
    while (1);
  }
  detect.attach(2);
  doorRed.attach(3);
  doorBlue.attach(4);
  doorGreen.attach(5);

  detect.write(0);
  doorRed.write(0);
  doorBlue.write(0);
  doorGreen.write(0);
}

void loop() {
  buttonState = digitalRead(button);
  digitalWrite(led, HIGH);

  if (buttonState == LOW && lastButtonState == HIGH && !started) {
      Serial.println("loop started");

    if (APDS.colorAvailable()) {
      APDS.readColor(r, g, b);
      openDoor();
      delay(5000);

      closeDoor();
      delay(1000);

    } else {
      started = false;
    }

    Serial.println("Programma afgelopen");
  }

  lastButtonState = buttonState;
}

void openDoor() {
  if (r > g && r > b) {
    Serial.println("RODE DEUR: OPEN");
    doorRed.write(90);

  } else if (g > r && g > b) {
    Serial.println("GROENE DEUR: OPEN");
    doorGreen.write(90);
  } else if (b > r && b > g) {
    Serial.println("BLAUWE DEUR: OPEN");
    doorBlue.write(90);

  }
  detect.write(45);
}

void closeDoor() {
  detect.write(0);
  doorRed.write(0);
  doorBlue.write(0);
  doorGreen.write(0);
  started = false;

}
