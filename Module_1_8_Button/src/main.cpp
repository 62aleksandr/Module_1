#include <Arduino.h>

#define BUTTON_PIN 16

uint32_t pressCount = 0;

bool lastButtonState = HIGH;

void setup()
{
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop()
{
  bool currentButtonState = digitalRead(BUTTON_PIN);

  // Обнаружение нажатия
  if (lastButtonState == HIGH && currentButtonState == LOW)
  {
    pressCount++;

    Serial.print("Count = ");
    Serial.println(pressCount);
  }

  lastButtonState = currentButtonState;
  // delay(50); // Небольшая задержка для устранения дребезга кнопки
}