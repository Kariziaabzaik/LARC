/*
 * Este programa lê continuamente o valor de um sensor analógico 
 * (como um potenciômetro) conectado ao pino 34 do ESP32.
 * O valor lido (que varia de 0 a 4095) é enviado para o 
 * Serial Monitor (Monitor Serial) do computador a cada 500ms.
 */

int Dados;

void setup() {
  Serial.begin(115200);  //Habilitar comunicação serial ESP32
}

void loop() {
  Dados = analogRead(34);  //Leitura potenciometro pino 34
  Serial.println(Dados);
  delay(500);  //500ms
}
