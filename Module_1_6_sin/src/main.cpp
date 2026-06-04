#include <Arduino.h>
#include <math.h>

#define WINDOW_SIZE 4 // Розмір вікна ковзного середнього

#define ALPHA 100 // коефіцієнт згладжування α = 100/255

const int NUM_SAMPLES = 50; // Кількість вимірювань для одного періоду синусоїди
const float VREF = 3.0f;    // Опорна напруга АЦП
int sample = 0;

int16_t func_sin(int sample);
int16_t movingAverage(int16_t x);
int16_t exponentialMovingAverage(int16_t x);

void setup()
{

  Serial.begin(115200);
  delay(1000); // Затримка для стабілізації серійного з'єднання
}

void loop()
{

  // Сигнал sin(x)
  int16_t adcValue = func_sin(sample);

  // Сигнал sin(x) + шуму (шум - випадкове число від -100 до 100)
  int16_t noisySignal = func_sin(sample) + random(-100, 101);

  // Сигнал після фільтрації ковзним середнім MA
  int16_t filterMA = movingAverage(noisySignal);

  // Сигнал після фільтрації експоненціальним середнім EMA
  int16_t filterEMA = exponentialMovingAverage(noisySignal);

  // Serial.print(adcValue);
  // Serial.print(" ");
  Serial.print(noisySignal);
  Serial.print(" ");
  Serial.print(filterMA);
  Serial.print(" ");
  Serial.println(filterEMA);

  sample = (sample + 1) % NUM_SAMPLES; // Збільшення зразка та обмеження до NUM_SAMPLES

  delay(100); // Затримка між зразками (100 мс)
}

// Функція сінуса
int16_t func_sin(int sample)
{

  // Дискретизація по часу
  float t = (2.0f * PI * sample) / NUM_SAMPLES;

  // Дискретизація по часу аналогового сигналу 0...2 В
  float Vin = 1.0f + 1.0f * sin(t);

  // Перетворення аналогової напруги Vin у 12-бітний код АЦП (0...4095)
  int16_t adcValue =
      (int16_t)round((Vin / VREF) * 4095.0f);

  return adcValue;
}

//  Функція фільтрації ковзним середнім MA
int16_t movingAverage(int16_t x)
{
  static int16_t buffer[WINDOW_SIZE]; // буфер значень
  static uint8_t index = 0;           // поточна позиція
  static int32_t sum = 0;             // сума вікна

  // відняти старе значення з суми
  sum -= buffer[index];

  // записати нове значення в буфер
  buffer[index] = x;

  // додати нове значення до суми
  sum += buffer[index];

  // перейти до наступного елемента циклічно
  index++;
  if (index >= WINDOW_SIZE)
    index = 0;

  // середнє значення
  return (int16_t)(sum / WINDOW_SIZE);
}

// Функція фільтрації експоненціальним середнім EMA
int16_t exponentialMovingAverage(int16_t x)
{
  static int32_t y_prev = 0;

  int32_t y = ((int32_t)ALPHA * x +
               (int32_t)(255 - ALPHA) * y_prev) /
              255;

  y_prev = y;

  return (int16_t)y;
}