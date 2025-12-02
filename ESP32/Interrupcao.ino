//variaveis volatile podem ser usadas dentro da interrupcao
volatile bool flag = false;
volatile int seg = 0;

hw_timer_t *timer = NULL;

void IRAM_ATTR dispara() {
  flag = true;
}

void setup() {
  Serial.begin(115200);

  // timer a 1 MHz
  timer = timerBegin(1000000);

  //chama interrupcao
  timerAttachInterrupt(timer, &dispara);

  //dispara o timer a cada 1000000microseg(1seg)
  timerAlarm(timer, 1000000, true, 0);

  //inicializa timer
  timerStart(timer);
}

void loop() {
  if (flag) {
    flag = false;
    seg++;
    Serial.print("segundos: ");
    Serial.println(seg);
  }
}
