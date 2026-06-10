#include <Arduino.h>

#define LED_PIN 17 // GPIO17 (LED)

#define BLINK_DELAY_MS 500

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop()
{
  digitalWrite(LED_PIN, HIGH);
  delay(BLINK_DELAY_MS);

  digitalWrite(LED_PIN, LOW);
  delay(BLINK_DELAY_MS);
}