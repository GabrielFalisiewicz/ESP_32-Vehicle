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

void setup() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  ledcSetup(channel_A, freq, resoultion);
  ledcSetup(channel_B, freq, resoultion);
  ledcAttachPin(PWM_A, channel_A);
  ledcAttachPin(PWM_B, channel_B);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(AIN1, 0);
  digitalWrite(AIN2, 1);
  digitalWrite(BIN1, 1);
  digitalWrite(BIN2, 0);
  ledcWrite(channel_A, 250);
  ledcWrite(channel_B, 250);
}
