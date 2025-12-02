int pot;

void setup() {
  Serial.begin(115200);  //Habilitar comunicação serial ESP32
  pinMode(13, INPUT);
}

void loop() {
  pot = analogRead(13);  //Leitura potenciometro pino 13
  Serial.println(pot);
  delay(500);  //500ms
}