#include <Servo.h>

Servo myservo;

void setup() {
  myservo.attach(6);  // 서보 모터 제어 핀
}

void loop() {
  for (int angle = 0; angle <= 180; angle++) {
    myservo.write(angle);    // angle 각도로 회전
    delay(0.5);               // 잠깐 대기
  }

  for (int angle = 180; angle >= 0; angle--) {
    myservo.write(angle);    // angle 각도로 회전
    delay(0.5);               // 잠깐 대기
  }
}
