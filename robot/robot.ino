#include "WiFi.h"
#include "WiFiUdp.h"

//Buzzer  
const int BUZ_Pin = 10;

//Piny prowadzące do mostka H dla silników N20-BT39
const int PWM_A = 14;
const int PWM_B = 15;

//Koniguracja sygnałów PWM
const int freq = 8000; // 8k na sekunde
const int resoultion = 8; // wartość max do 255 [j]

const int channel_A = 0;
const int channel_B = 2;

//Piny sterujące motoru A mostka H
const int AIN1 = 5;
const int AIN2 = 4;

//Piny sterujące motoru B mostka H
const int BIN1 = 8;
const int BIN2 = 7;

//Konfiguracja danych WiFi
const char* ssid = "vehicle_wifi_01";
const char* password = "ZAQ!2wsx";
const int channel = 6;
const int max_users = 1;
const bool hidden_ssid = false;
const int expower = 20; //dBm;

//Dane adresowe
IPAddress local_IP(192, 168, 5, 2);
IPAddress gateway(192, 168, 5, 1);
IPAddress sub(255, 255, 255, 0);

//Ustawienia UDP
const int updPort_channel_a = 1234;
const int udpPort_channel_b = 5678;
WiFiUDP udp_a;
WiFiUDP udp_b;
char messsage[255];

//Wartości 
int value_a = 0;
int value_b = 0;

void setup() {
  Serial.begin(115200);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(BUZ_Pin, OUTPUT);
  ledcSetup(channel_A, freq, resoultion);
  ledcSetup(channel_B, freq, resoultion);
  ledcAttachPin(PWM_A, channel_A);
  ledcAttachPin(PWM_B, channel_B);
  WiFi.softAP(ssid, password, channel, hidden_ssid, max_users);
  WiFi.softAPConfig(local_IP, gateway, sub);
  WiFi.setTxPower((wifi_power_t)expower);
  Serial.println("Adress IP: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  int size_message = udp_a.parsePacket();
  if(size_message){
      udp_a.read(messsage, 255);
      int tmp = int(messsage);
      value_a = map(tmp, 0, 4095, 0, 255);
  }

  size_message = udp_b.parsePacket();
  if(size_message){
      udp_b.read(messsage, 255);
      int tmp = int(messsage);
      value_b = map(tmp, 0, 4095, 0, 255);
  }

  //Sterowanie do mostka 
  digitalWrite(AIN1, 0);
  digitalWrite(AIN2, 1);
  digitalWrite(BIN1, 1);
  digitalWrite(BIN2, 0);
  ledcWrite(channel_A, value_a);
  ledcWrite(channel_B, value_b);
}

void WiFiEvent(WiFiEvent_t event){
  switch(event){
    case ARDUINO_EVENT_WIFI_AP_STACONNECTED:
      digitalWrtie(BUZ_Pin, 1);
      delay(1000);
      digitalWrite(BUZ_Pin, 0);
    break;
  }
}
