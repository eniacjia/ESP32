
/* ESP32 - Board Information
  Testing the major functions of the ESP32 board

  * DJ@20260109: First draft
*/
#include <WiFi.h>
#include <esp_system.h>

void setup() {
  //=== CONFIG#1 Communication with Serial Port
  Serial.begin(115200);
  delay(1000);

  test_get_esp_chip_infomation();
  test_wifi(0);
  test_esp32_memory_info();
}

void loop() {

  //test_wifi(1);

  delay(5000);

}

void test_get_esp_chip_infomation()
{

/* The true ESP32 chip ID is essentially its MAC address.
This sketch provides an alternate chip ID that matches
the output of the ESP.getChipId() function on ESP8266
(i.e. a 32-bit integer matching the last 3 bytes of
the MAC address. This is less unique than the
MAC address chip ID, but is helpful when you need
an identifier that can be no more than a 32-bit integer
(like for switch...case).

created 2020-06-07 by cweinhofer
with help from Cicicok */

  uint32_t chipId = 0;
  for (int i = 0; i < 17; i = i + 8) {
      chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
    }
  Serial.println();
  Serial.println("=== ESP32 Board Information ===");
  Serial.printf("ESP32 Chip model = %s Rev %d\n", ESP.getChipModel(), ESP.getChipRevision());
  Serial.printf("This chip has %d cores\n", ESP.getChipCores());
  Serial.print("Chip ID: ");
  Serial.println(chipId);

}

void test_wifi(int mode) {
  //Serial.begin(115200);
  //delay(1000);

  // WIFI Info
  const char* ssid     = "PIGGY2023";
  const char* password = "0123456789";

  if (mode == 0) {

    Serial.println();
    Serial.println("=== ESP32 WiFi Connection Test ===");
    Serial.print("Connecting to: ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    // Try to connect for up to 10 seconds
    int retries = 0;
    while (WiFi.status() != WL_CONNECTED && retries < 20) {
      delay(500);
      Serial.print(".");
      retries++;
    }

    Serial.println();

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("WiFi connected!");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());

      Serial.print("Signal strength (RSSI): ");
      Serial.println(WiFi.RSSI());
    } else {
      Serial.println("Failed to connect to WiFi.");
    }
  }
else if (mode == 1) {
    // --- Display WiFi status ---
    Serial.println("=== WiFi Status Mode ===");

    Serial.print("Status: ");
    Serial.println(WiFi.status());

    Serial.print("RSSI: ");
    Serial.println(WiFi.RSSI());
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  }

}



void test_esp32_memory_info() {

  Serial.println("=== ESP32 Memory Information ===");

  // --- Heap RAM ---
  Serial.print("Total heap: ");
  Serial.println(ESP.getHeapSize());

  Serial.print("Free heap: ");
  Serial.println(ESP.getFreeHeap());

  Serial.print("Min free heap: ");
  Serial.println(ESP.getMinFreeHeap());

  Serial.print("Max alloc heap: ");
  Serial.println(ESP.getMaxAllocHeap());

  // --- PSRAM ---
  Serial.print("PSRAM available: ");
  Serial.println(psramFound() ? "YES" : "NO");

  if (psramFound()) {
    Serial.print("PSRAM size: ");
    Serial.println(ESP.getPsramSize());

    Serial.print("Free PSRAM: ");
    Serial.println(ESP.getFreePsram());
  }

  // --- Flash ---
  Serial.print("Flash size: ");
  Serial.println(ESP.getFlashChipSize());

  Serial.print("Sketch size: ");
  Serial.println(ESP.getSketchSize());

  Serial.print("Free sketch space: ");
  Serial.println(ESP.getFreeSketchSpace());

  // --- Chip info ---
  Serial.print("Chip model: ");
  Serial.println(ESP.getChipModel());

  Serial.print("Chip revision: ");
  Serial.println(ESP.getChipRevision());

  Serial.print("CPU frequency (MHz): ");
  Serial.println(ESP.getCpuFreqMHz());
}
