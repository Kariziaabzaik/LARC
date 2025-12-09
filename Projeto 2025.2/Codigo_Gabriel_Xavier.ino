#include <Arduino.h>

// PINOS DA MESA RESISTIVA
const int X1 = 13;
const int X2 = 14;
const int Y1 = 27;
const int Y2 = 12;
const int pinADC_X = Y1;
const int pinADC_Y = X1;

// RESOLUCAO DA MESA (mm)
#define Xresolution 225.0 
#define Yresolution 173.0
#define Xmin 8.0
#define Xmax 217.0
#define Ymin 12.0
#define Ymax 152.0

// PWM PARA SERVOS
const int servoPinX = 33;
const int servoPinY = 15;
const int canalPWM_X = 0;
const int canalPWM_Y = 1;
const int freqPWM = 50;
const int resolucaoPWM = 16;
const int pwmMin = 1638;   // 0.5ms
const int pwmMax = 8192;   // 2.5ms
const int pwmNeutro = 4915;// 1.5ms

// PARAMETROS PID
float Kp = 7.0;
float Ki = 1.0;
float Kd = 4.0;
float N = 15.0;
float Ts = 0.02;

// COEFICIENTES CALCULADOS DO CONTROLADOR
float a0_i, a1_i;  // integrador
float c0_d, c1_d, d1_d; // derivador

// VARIAVEIS PID X - EIXO X
float erroX = 0, erroX_1 = 0; //erro e erro anterior de X
float somaIX = 0; //soma acumulativa da integral de X
float derivX_1 = 0; //derivada anterior de X
float uX = 0; //resultado do PID de X

// VARIAVEIS PID Y - EIXO Y
float erroY = 0, erroY_1 = 0; //erro e erro anterior de Y
float somaIY = 0; //soma acumulativa da integral de Y
float derivY_1 = 0; //derivada anterior de Y
float uY = 0; //resultado do PID de Y

// TEMPO DE CONTROLE 
unsigned long tempoAnterior = 0; //para temporizar o loop
const int Ts_ms = 20; //período de amostragem

// POSICAO DA ESFERA
float posX = 0, posY = 0;

// VARIAVEIS FILTRADAS - AÇÃO DERIVATIVA E POSIÇÃO
const float alpha = 0.386;  // fc = 5Hz, fs = 50Hz
float posX_filtrado = 0;
float posY_filtrado = 0;

// SETPOINT (CENTRO DA MESA) CALIBRADO
const float setX = 100.0;
const float setY = 75.0;

// FUNCAO DE LIMITACAO DA AÇÃO PWM 
int limitarPWM(float valor) {
  if (valor < pwmMin) return pwmMin;
  if (valor > pwmMax) return pwmMax;
  return (int)valor;
}

// FUNÇÃO DA LEITURA DA POSICAO 
void lerPosicao() {
  // Leitura X
  pinMode(Y1, INPUT); //por onde vamos ler a posição do eixo X da bola
  pinMode(Y2, OUTPUT_OPEN_DRAIN); digitalWrite(Y2, HIGH); 
  pinMode(X1, OUTPUT); digitalWrite(X1, HIGH);
  pinMode(X2, OUTPUT); digitalWrite(X2, LOW);
  delayMicroseconds(500);
  float leituraX = analogRead(pinADC_X); //lê a posição da bola
  leituraX = leituraX / (4096.0 / Xresolution); //converte a leitura para analógico, ou seja, em mm 
  float posX_raw = ((leituraX - Xmin) / (Xmax - Xmin)) * Xresolution; //normaliza a leitura para o valor em relação à Xresolution
  posX_filtrado = alpha * posX_raw + (1 - alpha) * posX_filtrado; //filtro para suavização de ruido
  posX = posX_filtrado; //setando para o próximo loop

  // Leitura Y
  pinMode(X1, INPUT); //por onde vamos ler a posição do eixo Y da bola
  pinMode(X2, OUTPUT_OPEN_DRAIN); digitalWrite(X2, HIGH);
  pinMode(Y1, OUTPUT); digitalWrite(Y1, HIGH);
  pinMode(Y2, OUTPUT); digitalWrite(Y2, LOW);
  delayMicroseconds(500);
  float leituraY = analogRead(pinADC_Y); //lê a posição da bola
  leituraY = leituraY / (4096.0 / Yresolution); //converte a leitura para analógico, ou seja, em mm 
  float posY_raw = ((leituraY - Ymin) / (Ymax - Ymin)) * Yresolution; //normaliza a leitura para o valor em relação à Yresolution
  posY_filtrado = alpha * posY_raw + (1 - alpha) * posY_filtrado; //filtro para suavização de ruido
  posY = posY_filtrado; //setando para o próximo loop
}

// FUNÇÃO PARA CALCULO DOS COEFICIENTES - CONTROLADOR PID
void calcularCoeficientes() {
  a0_i = (Ki * Ts) / 2.0; //coeficientes da parte da integral do PID
  a1_i = a0_i;

  float den = N * Ts + 2.0; //coeficientes da parte da derivada do PID
  c0_d = (2.0 * Kd * N) / den;
  c1_d = -c0_d;
  d1_d = (2.0 - N * Ts) / den;
}

// SETUP (INICIALIZAÇÃO)
void setup() {
  Serial.begin(115200);

  ledcSetup(canalPWM_X, freqPWM, resolucaoPWM); //setando PWM do eixo X
  ledcAttachPin(servoPinX, canalPWM_X);
  ledcSetup(canalPWM_Y, freqPWM, resolucaoPWM); //setando PWM do eixo Y
  ledcAttachPin(servoPinY, canalPWM_Y);

  ledcWrite(canalPWM_X, pwmNeutro); //leva ambos para o neutro
  ledcWrite(canalPWM_Y, pwmNeutro);

  calcularCoeficientes(); //calcula os coeficientes do PID

  Serial.println("tempo_ms,posX,setX,posY,setY");
}

// LOOP PRINCIPAL
void loop() {
  // CALCULO DO TEMPO DE AMOSTRAGEM
  if (millis() - tempoAnterior >= Ts_ms) { //garante que o loop ocorra a cada 20ms
    tempoAnterior = millis(); //prepara o loop seguinte

    lerPosicao(); // LEITURA DA POSIÇÃO

    // CALCULO DO ERRO
    erroX = setX - posX;
    erroY = setY - posY;

    // PID X 
    float P_X = Kp * erroX; //parte proporcional
    somaIX += a0_i * erroX + a1_i * erroX_1; //parte da integral
    float D_X = c0_d * erroX + c1_d * erroX_1 + d1_d * derivX_1; //parte da derivada

    uX = P_X + somaIX + D_X; //soma do PID

    erroX_1 = erroX; //prepara o loop seguinte
    derivX_1 = D_X;

    int pwmX = limitarPWM(pwmNeutro + uX); // AÇÃO DE CONTROLE
    ledcWrite(canalPWM_X, pwmX); //envia para o servomotor

    // PID Y 
    float P_Y = Kp * erroY; //parte proporcional
    somaIY += a0_i * erroY + a1_i * erroY_1; //parte da integral
    float D_Y = c0_d * erroY + c1_d * erroY_1 + d1_d * derivY_1; //parte da derivada

    uY = P_Y + somaIY + D_Y; //soma do PID

    erroY_1 = erroY; //prepara o loop seguinte
    derivY_1 = D_Y;

    int pwmY = limitarPWM(pwmNeutro + uY); // AÇÃO DE CONTROLE
    ledcWrite(canalPWM_Y, pwmY); //envia para o servomotor

    // EXPORTACAO SERIAL CSV
    Serial.print(millis()); Serial.print(",");
    Serial.print(posX, 3); Serial.print(",");
    Serial.print(setX, 3); Serial.print(",");
    Serial.print(posY, 3); Serial.print(",");
    Serial.println(setY, 3);
  }
}
