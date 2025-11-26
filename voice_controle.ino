#include <AFMotor.h>

#define Speed 170

// Motors
AF_DCMotor M1(1);
AF_DCMotor M2(2);
AF_DCMotor M3(3);
AF_DCMotor M4(4);

char value;

void setup() {
  Serial.begin(9600);

  M1.setSpeed(Speed);
  M2.setSpeed(Speed);
  M3.setSpeed(Speed);
  M4.setSpeed(Speed);

  Stop();  // motors off initially
}

void loop() {
  voiceControl();
}

void voiceControl() {
  if (Serial.available()) {
    value = Serial.read();
    Serial.println(value);  // debug
  }

  if (value == '^') {
    forward();
  }
  else if (value == '-') {
    backward();
  }
  else if (value == '<') {
    left();
  }
  else if (value == '>') {
    right();
  }
  else if (value == '*') {
    Stop();
  }
}

// Movement
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

void left() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}

void right() {
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
}

void Stop() {
  M1.run(RELEASE);
  M2.run(RELEASE);
  M3.run(RELEASE);
  M4.run(RELEASE);
}
