/* Colocando os valores de frequência, canal de PWM, resolução e o pino de saída do PWM ligado ao servo
*/
const int freq = 50;
const int ledchannel = 0;
const int resolucao = 16;
const int pino = 13;
int valor;

/*Setup, ligando o serial e configurando o PWM do servo
*/
void setup(){
  ledcAttachChannel(pino, freq, resolucao, ledchannel);
  Serial.begin(115200);
}
/* Loop que faz o servo mover de 0° para 90° e depois para 180°
os valores de 0° (0.5 ms)e de 90° (1.5 ms) está certo, porém por limitações físicas do servo,
para 180° (2.5 ms) o valor é um pouco menor que o calculado (2.48 ms)
*/
void loop(){
  ledcWrite(pino, 1632);
  Serial.println("0°");
  delay(1000);

  ledcWrite(pino, 4912);
  Serial.println("90°");
  delay(1000);

  ledcWrite(pino, 8144);
  Serial.println("180°");
  delay(1000);
}
