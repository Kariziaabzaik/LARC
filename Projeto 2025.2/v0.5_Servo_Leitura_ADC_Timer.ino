const int freq = 50;
const int ledchannel = 0;
const int resolucao = 16;
const int pino = 13;
int valor, dtc;
volatile bool flag = false;

hw_timer_t *timer = NULL;

void IRAM_ATTR dispara() {
  flag = true;
  valor = analogRead(12); 
  Serial.println(valor);
}

void setup(){
  ledcAttachChannel(pino, freq, resolucao, ledchannel);
  Serial.begin(115200);
  pinMode(12, INPUT);

  timer = timerBegin(1000000);
  timerAttachInterrupt(timer, &dispara);
  timerAlarm(timer, 100000, true, 0);
  timerStart(timer);
}

void loop(){

  if(flag){
    flag = false;
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
  }
}
