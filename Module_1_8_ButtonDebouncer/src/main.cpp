#include <Arduino.h>

#define BUTTON_PIN 16

// Лічильник натискань кнопки
uint32_t pressCount = 0;

// Поточний стабільний стан кнопки
bool stableState = HIGH;

// Попереднє миттєве значення кнопки
bool lastReading = HIGH;

// Час останньої зміни стану
unsigned long t0 = 0;

// Час антидребезгу (мс)
const uint32_t FILTER_TIME = 30;

void setup()
{
  Serial.begin(115200);

  // Кнопка підключена до GND
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop()
{
  // Зчитування поточного стану кнопки
  bool currentReading = digitalRead(BUTTON_PIN);

  // Якщо стан змінився — запускаємо таймер
  if (currentReading != lastReading)
  {
    t0 = millis();
  }

  // Якщо стан не змінювався FILTER_TIME мс,
  // вважаємо його стабільним
  if ((millis() - t0) > FILTER_TIME)
  {
    // Виявлено новий стабільний стан
    if (currentReading != stableState)
    {
      stableState = currentReading;

      // Фіксуємо натискання (HIGH -> LOW)
      if (stableState == LOW)
      {
        pressCount++;

        Serial.print("Count = ");
        Serial.println(pressCount);
      }
    }
  }

  // Запам'ятовуємо останнє зчитування кнопки
  lastReading = currentReading;
}