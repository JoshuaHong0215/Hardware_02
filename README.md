# 🧾 Servo 버튼 제어 및 Turtle 연동 프로젝트

## 📌 프로젝트 목적

**버튼을 누르면 서보 모터가 4번 작동하고, 동시에 PC의 터틀 거북이가 앞으로 전진하는 동작을 구현한다.**

아두이노에서 물리 버튼을 통해 `"전진"` 시리얼 신호를 보내고, Python(Thonny)에서 이를 수신하여 거북이를 전진시키는 구조입니다.

---

## 🛠 시스템 구성 요약

| 구성 요소         | 설명                                                       |
|------------------|------------------------------------------------------------|
| **아두이노 UNO** | 버튼 신호 감지, 서보 모터 제어, `"전진"` 시리얼 메시지 전송 |
| **서보 모터**    | 버튼 누를 때 4회 회전 동작 수행 (0도 ↔ 180도)              |
| **물리 버튼**    | 눌리면 LOW 신호 발생                                        |
| **Python**       | `"전진"` 메시지를 수신하면 거북이 전진                       |
| **turtle 거북이** | 그래픽으로 움직이는 GUI 거북이 (800픽셀 이동)               |

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

## 🔧 1. 아두이노 코드

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
🐍 2. Python(Thonny) 코드
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

버튼과 서보, 시리얼 연결 확인

Python(Thonny) 코드 실행

"시리얼 연결 완료" 메시지 출력 확인

버튼 누르기

서보가 4회 작동 후 "전진" 명령 전송

터틀 거북이가 800픽셀 전진

💡 참고 사항
버튼은 INPUT_PULLUP 방식이므로 눌렸을 때 LOW 상태가 됩니다.

Python 코드는 아두이노로부터 "전진"이라는 문자열을 수신하면 실행됩니다.

COM 포트 번호(COM4)는 PC마다 다를 수 있으며 환경에 맞게 설정하세요.

거북이 이동 거리는 t.forward() 값으로 조절 가능합니다.

📁 파일 구조 예시
bash
복사
편집
📂 ServoTurtleProject
├── arduino_servo_button.ino      # 아두이노 코드
├── turtle_move.py                # Thonny에서 실행할 Python 코드
└── README.md                     # 설명 파일 (이 문서)
go
복사
편집

위 내용을 복사해서 `.md` 파일로 저장하시면 됩니다.  
예: `README.md` 라는 파일로 저장한 후 GitHub 등에 업로드하면 자동으로 예쁘게 렌더링됩니다.

필요하시면 `.ino`, `.py`, `.md`까지 함께 묶어서 zip 파일로 구성해드릴 수도 있습니다.








ChatGPT에게 묻기
