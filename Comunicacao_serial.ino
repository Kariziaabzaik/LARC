/*
 * Este programa controla um pino de saída digital (GPIO 23) do ESP32 
 * através de comandos enviados pelo Serial Monitor (Monitor Serial).
 * * - Ao receber o caractere 'A' (maiúsculo), ele LIGA o pino 23 (define como HIGH).
 * - Ao receber o caractere 'a' (minúsculo), ele DESLIGA o pino 23 (define como LOW).
 */
char Dados; // Definição do tipo de variável

void setup() {
  Serial.begin(115200);   // Habilitar comunicação serial ESP32
  pinMode(23, OUTPUT);    // Habilitar pino 23 como saída
  
  Serial.println("ESP32 pronto. Envie 'A' para ligar ou 'a' para desligar o pino 23."); 
}

void loop() {
  // Verifica se há dados disponíveis para ler
  if (Serial.available() > 0) {
    
    // Lê o dado
    Dados = Serial.read(); 

    // Compara o dado lido
    if (Dados == 'A') {
      digitalWrite(23, HIGH);
      Serial.println("Pino 23 ativado");
    } 
    else if (Dados == 'a') {
      digitalWrite(23, LOW);
      Serial.println("Pino 23 desativado");
    }
  }
}