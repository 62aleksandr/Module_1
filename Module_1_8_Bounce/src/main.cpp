#include <Arduino.h>
#include <Bounce2.h>

#define BUTTON_PIN 16

// Лічильник натискань кнопки
uint32_t pressCount = 0;

// Об'єкт антидребезгу Bounce2
Bounce button = Bounce();

void setup()
{
  Serial.begin(115200);

  // Налаштування кнопки з підтягуванням
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Прив'язка Bounce2 до піна
  button.attach(BUTTON_PIN);

  // Час антидребезгу (30 мс як у тебе)
  button.interval(30);
}

void loop()
{
  // Оновлення стану кнопки
  button.update();

  // Подія: натискання (перехід HIGH -> LOW)
  if (button.fell())
  {
    pressCount++;

    Serial.print("Count = ");
    Serial.println(pressCount);
  }
}