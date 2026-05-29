#include <Arduino.h>

// Connect an LED to digital pin 16:
// LED anode -> 220Ω resistor -> Pin 16
// LED cathode -> GND

#define LED_PIN 16 // LED connected to pin 16

void setup()
{
  Serial.begin(115200); // Start serial communication at 115200 baud rate

  // Initialize the LED pin as an output
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  // Blink the LED: 500ms ON, 500ms OFF
  digitalWrite(LED_PIN, HIGH); // turn LED on
  Serial.println("LED is ON");
  delay(500);                 // wait 500 milliseconds
  digitalWrite(LED_PIN, LOW); // turn LED off
  Serial.println("LED is OFF");
  delay(500); // wait 500 milliseconds
}
