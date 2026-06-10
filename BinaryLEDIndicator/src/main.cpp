#include <Arduino.h>

const int BITS = 4;
const int NUMBER_MAX = (1 << BITS) - 1;

int randomNum();
void binaryPrint(int num);

void setup()
{
  Serial.begin(115200);
  delay(1000); // Затримка для стабілізації серійного з'єднання

  // Ініціалізація генератора випадкових чисел
  randomSeed(micros());
}

void loop()
{
  int num = randomNum();

  Serial.print("Decimal = ");
  Serial.print(num);

  Serial.print("  Binary = ");
  binaryPrint(num);

  Serial.println();

  delay(5000);
}

int randomNum()
{
  // Випадкове число від 0 до 15
  return random(0, NUMBER_MAX + 1);
}

void binaryPrint(int num)
{
  // Перетворення в двійковий код
  for (int i = BITS - 1; i >= 0; i--)
  {
    Serial.print((num >> i) & 1);
  }
}
