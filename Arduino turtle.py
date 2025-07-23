import turtle
import serial
import time

# Turtle Setting
t = turtle.Turtle()
t.shape("turtle")
turtle.bgcolor("skyblue")
t.fillcolor("blue")
t.shapesize(2,2,2)
t.pencolor("blue")
t.pensize(4)
t.penup()
t.goto(-400,0)
t.pendown()
# Arduino Serial Connect
try:
    ser = serial.Serial('COM4', 9600, timeout=1)
    time.sleep(2)  # 연결 안정화 대기
    print("시리얼 연결 완료")
except:
    print("시리얼 연결 실패")
    ser = None

# main loop
def listen_for_command():
    while True:
        if ser and ser.in_waiting > 0:
            data = ser.readline().decode().strip()
            print(f"받은 명령: {data}")
            if data == "전진":
                print("거북이 앞으로 100픽셀 전진합니다.")
                t.forward(800)  # 거북이 100픽셀 전진

listen_for_command()