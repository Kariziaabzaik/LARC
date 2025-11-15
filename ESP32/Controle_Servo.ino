/*
 * Controle de Servo Motor com ESP32
 * Este código faz um servo motor varrer continuamente
 * de 0 a 180 graus e depois retornar de 180 a 0 graus.
 */
#include <ESP32Servo.h>

static const int servoPin = 23;

Servo servo;

int ang =0;
int angStep = 5;

int angMin =0;
int angMax = 180;

void setup() {
    Serial.begin(115200);
    servo.setPeriodHertz(50); // Configura a frequência do sinal PWM para 50Hz
    servo.attach(servoPin);
}

void loop() {
    // Inicia um loop 'for' que vai de 'angMin' (0) até 'angMax' (180)
    for(int ang = 0; ang <= angMax; ang +=angStep) {
        servo.write(ang);
        Serial.println(ang);
        delay(20);
    }
    
    // --- Segundo movimento: de 180 para 0 graus ---
    for(int ang = 180; ang >= angMin; ang -=angStep) {
        servo.write(ang);
        Serial.println(ang);
        delay(20);
    }

}
