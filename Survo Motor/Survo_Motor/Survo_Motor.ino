#include <Servo.h>

const int buttonPin = 7;   // 버튼 핀
const int servoPin = 6;    // 서보 핀
Servo myservo;

bool readyToDetect = false;
bool buttonWasPressed = false;  // 이전에 눌렸는지 추적

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  myservo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  // 버튼이 HIGH(안눌림)이었던 적이 있다면 감지 시작
  if (buttonState == HIGH) {
    readyToDetect = true;
    buttonWasPressed = false;  // 다시 누를 준비
  }

  // 감지 준비되었고 버튼이 LOW로 눌리면 동작
  if (readyToDetect && buttonState == LOW && !buttonWasPressed) {
    buttonWasPressed = true;

    // 🌀 모터 10번 움직이기
    for (int i = 0; i < 10; i++) {
      myservo.write(0);
      delay(500);
      myservo.write(180);
      delay(500);
    }

    Serial.println("전진");
  }
}
