#include <Servo.h>
#include <AFMotor.h>

#define Echo A0
#define Trig A1
#define motor 10     // servo pin
#define Speed 170
#define spoint 103   // straight position

Servo servo;

// Motors from Adafruit Motor Shield
AF_DCMotor M1(1);
AF_DCMotor M2(2);
AF_DCMotor M3(3);
AF_DCMotor M4(4);

int distance;
int LeftDist;
int RightDist;

void setup() {
  Serial.begin(9600);

  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);

  servo.attach(motor);
  servo.write(spoint);    // center

  M1.setSpeed(Speed);
  M2.setSpeed(Speed);
  M3.setSpeed(Speed);
  M4.setSpeed(Speed);

  delay(500);
}

void loop() {

  distance = ultrasonic();
  Serial.print("Front: ");
  Serial.println(distance);

  if (distance <= 15) {    // Obstacle too close
    Stop();
    delay(200);

    backward();
    delay(300);
    Stop();
    delay(200);

    // CHECK LEFT
    LeftDist = leftScan();
    Serial.print("Left: ");
    Serial.println(LeftDist);

    servo.write(spoint);
    delay(300);

    // CHECK RIGHT
    RightDist = rightScan();
    Serial.print("Right: ");
    Serial.println(RightDist);

    servo.write(spoint);
    delay(300);

    // DECISION
    if (LeftDist > RightDist) {
      left();
      delay(500);
    } else {
      right();
      delay(500);
    }

    Stop();
  }
  else {
    forward();
  }
}

int ultrasonic() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(5);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  long t = pulseIn(Echo, HIGH);
  long cm = t / 29 / 2;
  return cm;
}

int leftScan() {
  servo.write(170);
  delay(500);
  return ultrasonic();
}

int rightScan() {
  servo.write(20);
  delay(500);
  return ultrasonic();
}

// MOTOR MOVEMENTS
void forward() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
}

void backward() {
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}

void right() {
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
}

void left() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}

void Stop() {
  M1.run(RELEASE);
  M2.run(RELEASE);
  M3.run(RELEASE);
  M4.run(RELEASE);
}
