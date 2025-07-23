# 🧾 Servo 버튼 제어 및 Turtle 연동 프로젝트

## 📌 프로젝트 목적

버튼을 누르면 서보 모터가 4번 작동하고,  
동시에 PC의 Turtle 그래픽 거북이가 앞으로 전진하는 동작을 구현합니다.

---

## 🛠 시스템 구성 요약

| 구성 요소         | 설명                                                       |
|------------------|------------------------------------------------------------|
| **아두이노 UNO** | 버튼 신호 감지, 서보 모터 제어, `"전진"` 시리얼 메시지 전송 |
| **서보 모터**    | 버튼 누를 때 4회 회전 동작 수행 (0도 ↔ 180도)              |
| **물리 버튼**    | 눌리면 LOW 신호 발생 (INPUT_PULLUP 방식)                   |
| **Python (Thonny)** | `"전진"` 메시지를 수신하면 Turtle 거북이 전진             |
| **turtle 거북이** | 그래픽으로 움직이는 GUI 거북이 (800픽셀 이동)             |

---

## 🔄 시스템 동작 흐름

[ 버튼 누름 ]
↓
[ 아두이노 → 서보 모터 4회 작동 ]
↓
[ 아두이노 → "전진" 메시지 전송 (Serial) ]
↓
[ Python(Thonny) 수신 ]
↓
[ 거북이 800픽셀 전진 ]

arduino
복사
편집

---

## 🔧 1. 아두이노 코드 (`arduino_servo_button.ino`)

```cpp
#include <Servo.h>

const int buttonPin = 7;     // 버튼 핀
const int servoPin = 6;      // 서보 핀
Servo myservo;

bool readyToDetect = false;
bool buttonWasPressed = false;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);   // 풀업 설정
  myservo.attach(servoPin);           // 서보 연결
  Serial.begin(9600);                 // 시리얼 통신 시작
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    readyToDetect = true;
    buttonWasPressed = false;
  }

  if (readyToDetect && buttonState == LOW && !buttonWasPressed) {
    buttonWasPressed = true;

    // 서보 모터 4번 작동
    for (int i = 0; i < 4; i++) {
      myservo.write(0);
      delay(500);
      myservo.write(180);
      delay(500);
    }

    // PC로 전진 명령 전송
    Serial.println("전진");
  }
}
🐍 2. Python 코드 (turtle_move.py)
python
복사
편집
import turtle
import serial
import time

# 터틀 설정
t = turtle.Turtle()
t.shape("turtle")
turtle.bgcolor("skyblue")
t.fillcolor("blue")
t.shapesize(2, 2, 2)
t.pencolor("blue")
t.pensize(4)
t.penup()
t.goto(-400, 0)
t.pendown()

# 아두이노 시리얼 연결
try:
    ser = serial.Serial('COM4', 9600, timeout=1)
    time.sleep(2)
    print("시리얼 연결 완료")
except:
    print("시리얼 연결 실패")
    ser = None

# 명령 수신 루프
def listen_for_command():
    while True:
        if ser and ser.in_waiting > 0:
            data = ser.readline().decode().strip()
            print(f"받은 명령: {data}")
            if data == "전진":
                print("거북이 앞으로 800픽셀 전진합니다.")
                t.forward(800)

listen_for_command()
✅ 실행 순서
아두이노 코드 업로드

버튼, 서보, 시리얼 포트 확인

Python 코드 실행 (Thonny에서)

"시리얼 연결 완료" 메시지 확인

버튼 누르기

서보가 4회 작동

"전진" 메시지 전송

거북이 800픽셀 전진

💡 참고 사항
버튼은 INPUT_PULLUP으로 설정되었기 때문에 누르면 LOW 상태가 됩니다.

Python 코드는 아두이노로부터 "전진" 문자열을 받으면 거북이가 전진합니다.

시리얼 포트(COM4)는 환경에 맞게 변경해 주세요.

거북이 전진 거리는 t.forward(800)에서 조절 가능합니다.

