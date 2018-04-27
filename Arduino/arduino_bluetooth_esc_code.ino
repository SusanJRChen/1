#include <Time.h>
#include <Servo.h>
#define MIN_PULSE_LENGTH 1000
#define MAX_PULSE_LENGTH 2000
#define PANIC_TIMER 1000
#define PANIC_PULSE 1500
#define PIN_ONE 4
#define PIN_TWO 5
#define PIN_THREE 6
#define EMPTY_INPUT 0
#define NO_INPUT -1
Servo MOTOR_ONE, MOTOR_TWO, MOTOR_THREE;
int inputDirection = EMPTY_INPUT;
int inputPulse = MIN_PULSE_LENGTH;
time_t startingTime;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  MOTOR_ONE.attach(PIN_ONE, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
  MOTOR_TWO.attach(PIN_TWO, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
  MOTOR_THREE.attach(PIN_THREE, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
  startingTime = time(NULL);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0) {
    if (inputDirection == EMPTY_INPUT || inputDirection == NO_INPUT) {
      inputDirection = Serial.read();
      continue;
    }
    inputPulse = inputPulse * 10 + Serial.read();
  }
  if (inputDirection == NO_INPUT) {
    setEscPulse(inputPulse);
    startingTime = time(NULL);
    inputPulse = 0;
    inputDirection = NO_INPUT;
  }
  double elapsedTime = difftime(time(NULL), startingTime);
  if (elapsedTime > PANIC_TIMER) {
    panicDoSomething();
  }
}

void setEscPulse(int inputPulse) {
  MOTOR_ONE.writeMicroseconds(inputPulse);
  MOTOR_TWO.writeMicroseconds(inputPulse);
  MOTOR_THREE.writeMicroseconds(inputPulse);
}

void panicDoSomething() {
  MOTOR_ONE.writeMicroseconds(PANIC_PULSE);
  MOTOR_TWO.writeMicroseconds(PANIC_PULSE);
  MOTOR_THREE.writeMicroseconds(PANIC_PULSE);
}

