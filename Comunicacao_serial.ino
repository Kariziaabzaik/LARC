char Dados;  //Definição do tipo de variável

void setup() {
  Serial.begin(115200);  //Habilitar comunicação serial ESP32
  pinMode(19, OUTPUT);   //Habilitar pino 19 como saída
}

void loop() {
  Dados = Serial.read();  //Leitura da porta serial

  if (Dados == 'A')
    {
    digitalWrite(19, HIGH);
    Serial.println("Pino 19 ativado");
    }
  if (Dados == 'a')
    {
    digitalWrite(19, LOW);
    Serial.println("Pino 19 desativado");
    }
}
