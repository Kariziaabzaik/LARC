
const int freq = 50
const int ledchannel = 0
const int resolucao = 16
const int pino = 13

void setup(){
  ledcSetup(ledchannel, freq, resolucao);
  ledcAttachPin(pino, ledchannel);
}

void loop(){
  ledcWrite(ledchannel, 4915);
  delay(1000);

  ledcWrite(ledchannel, 1638);
  delay(1000);

  ledcWrite(ledchannel, 8192);
  delay(1000);
}
