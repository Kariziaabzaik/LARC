const int freq = 50;
const int ledchannel1 = 0;
const int ledchannel2 = 1;
const int resolucao = 16;
const int pino1 = 13;
const int pino2 = 23;
int valor1, valor2, dtc1, dtc2;
volatile bool flag = false;
String texto;

hw_timer_t *timer = NULL;

void IRAM_ATTR dispara() {
  flag = true;
  valor1 = analogRead(12); 
}

void setup(){
  ledcAttachChannel(pino1, freq, resolucao, ledchannel1);
  ledcAttachChannel(pino2, freq, resolucao, ledchannel2);  
  Serial.begin(115200);
  pinMode(12, INPUT);

  timer = timerBegin(1000000);
  timerAttachInterrupt(timer, &dispara);
  timerAlarm(timer, 100000, true, 0);
  timerStart(timer);
}

void loop(){

  if(Serial.available()>0){
    texto = Serial.readStringUntil('\n');
    valor2 = texto.toInt();
    dtc2 = 1632 + valor2*36.1778;
    ledcWrite(pino2, dtc2);
  }

  if(flag){
    flag = false;
    if (valor1 < 100){
      dtc1 = 1632;
    }else{
      if (valor1 > 4000){
        dtc1 = 8144;
      }else{
        dtc1 = 1632 + valor1*1.67;
      }
    }
    ledcWrite(pino1, dtc1);
  }
}
