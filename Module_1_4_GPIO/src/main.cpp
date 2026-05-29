#include <Arduino.h>

#define BUTTON_PIN 0 // GPIO0 (button, use INPUT_PULLUP)
#define LED_PIN 16   // GPIO16 (LED)

#define DEBOUNCE_MS 20
#define BLINK_DELAY_MS 500

void setup()
{
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop()
{
  if (digitalRead(BUTTON_PIN) == LOW)
  {
    digitalWrite(LED_PIN, HIGH);
    delay(BLINK_DELAY_MS);

    digitalWrite(LED_PIN, LOW);
    delay(BLINK_DELAY_MS);
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
  }

  delay(DEBOUNCE_MS); // simple debounce
}