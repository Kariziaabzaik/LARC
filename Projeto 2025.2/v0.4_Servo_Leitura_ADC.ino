const int freq = 50;
const int ledchannel = 0;
const int resolucao = 16;
const int pino = 13;
int valor, dtc;

void setup(){
  ledcAttachChannel(pino, freq, resolucao, ledchannel);
  Serial.begin(115200);
  pinMode(12, INPUT);
}

void loop(){

  
    valor = analogRead(12); 
    Serial.println(valor);
  
    if (valor < 100){
      dtc = 1632;
    }else{
      if (valor > 4000){
        dtc = 8144;
      }else{
        dtc = 1632 + valor*1.67;
      }
    }
    ledcWrite(pino, dtc);
    Serial.println(dtc);
    delay(1000);
}
