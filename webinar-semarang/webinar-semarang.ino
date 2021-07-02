#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"

//configurasi wifi dan blynk
char auth[] = "5M19usXSgimxmQHjhEUzjtAmloGfK_4O"; //Auth Token Blynk
char ssid[] = "SSID"; //SSID atau nama WIFI yang dihubungkan
char pass[] = "password"; //Password Wifi



//configurasi dht
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
//inisialisasi blynktimer untuk multitasking
BlynkTimer timer;

void sendSensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V1, t); //suhu virtual 1
  Blynk.virtualWrite(V2, h); //kelembaban virtual 2
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  dht.begin();

  //untuk multitasking mengambil dan mengirim data suhu ke aplikasi
  timer.setInterval(1000L, sendSensor);

  //  deklarasi pin relay sebagai output
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  /*  set untuk relay dalam posisi mati
      karena relay itu low trigger jadi menggunakan logic terbalik
      HIGH = mati LOW = hidup
  */
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
}
void loop() {
  Blynk.run();
  timer.run();
}
