#include <esp_now.h>
#include <WiFi.h>

typedef struct struct_message {
    int x;
    int y;
} struct_message;

struct_message myData;

int ledUnten = 6;
int ledOben = 7;
int ledLinks = 8;
int ledRechts = 9;

void OnDataRecv(const esp_now_recv_info * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("X: ");
  Serial.println(myData.x);
  Serial.print("Y: ");
  Serial.println(myData.y);

  if (myData.x > 1010) {
    digitalWrite(ledLinks, HIGH);
  } else {
    digitalWrite(ledLinks, LOW);
  }

  if (myData.x < 20) {
    digitalWrite(ledRechts, HIGH);
  } else {
    digitalWrite(ledRechts, LOW);
  }

  if (myData.y > 1010) {
    digitalWrite(ledOben, HIGH);
  } else {
    digitalWrite(ledOben, LOW);
  }

  if (myData.y < 20) {
    digitalWrite(ledUnten, HIGH);
  } else {
    digitalWrite(ledUnten, LOW);
  }
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_register_recv_cb(OnDataRecv);

  pinMode(ledUnten, OUTPUT);
  pinMode(ledOben, OUTPUT);
  pinMode(ledLinks, OUTPUT);
  pinMode(ledRechts, OUTPUT);
}

void loop() {

}
