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
