#include <ESP32Servo.h>

static const int servoPin = 23;

Servo servo;

int ang =0;
int angStep = 5;

int angMin =0;
int angMax = 180;

void setup() {
    Serial.begin(115200);
    servo.attach(servoPin);
}

void loop() {
    for(int ang = 0; ang <= angMax; ang +=angStep) {
        servo.write(ang);
        Serial.println(ang);
        delay(20);
    }

    for(int ang = 180; ang >= angMin; ang -=angStep) {
        servo.write(ang);
        Serial.println(ang);
        delay(20);
    }

}
