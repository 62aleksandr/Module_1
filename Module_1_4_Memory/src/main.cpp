#include <Arduino.h>

uint8_t *bigBuffer;

void printMemoryInfo()
{
  Serial.println("\n=== ESP32-S3 memory info ===");

  // SRAM / heap
  Serial.printf("Heap total: %.2f MB\n", ESP.getHeapSize() / 1048576.0f);
  Serial.printf("Heap free:  %.2f MB\n", ESP.getFreeHeap() / 1048576.0f);

  Serial.println("==========");
  // PSRAM
  if (ESP.getPsramSize() > 0)
  {
    Serial.printf("PSRAM total: %.2f MB\n", ESP.getPsramSize() / 1048576.0f);
    Serial.printf("PSRAM free:  %.2f MB\n", ESP.getFreePsram() / 1048576.0f);
  }
  else
  {
    Serial.println("PSRAM not available or not enabled");
  }

  Serial.println("==========");
  // Flash / sketch space
  Serial.printf("Sketch size: %.2f MB\n", ESP.getSketchSize() / 1048576.0f);
  Serial.printf("Free sketch space: %.2f MB\n", ESP.getFreeSketchSpace() / 1048576.0f);
  Serial.printf("Flash size: %.2f MB\n", ESP.getFlashChipSize() / 1048576.0f);

  Serial.println("===========================");
}

void setup()
{
  Serial.begin(115200);
  delay(1000);

  printMemoryInfo();

  bigBuffer = (uint8_t *)ps_malloc(1024 * 1024 * 4); // 4 MB

  if (bigBuffer == nullptr)
  {
    Serial.println("\nПам'ять не виділина!");
  }
  else
  {
    Serial.println("\n4 MB PSRAM виділено");
  }

  printMemoryInfo();

  free(bigBuffer); // Не забуваємо звільняти
  Serial.println("\nПам'ять звільнено!");

  printMemoryInfo();
}

void loop()
{
  delay(5000);
}