#include <Time.h>


const int UP = 1;
const int DOWN = 0;
const int EMPTY_INPUT = -1;
const int NO_INPUT = -2;
int inputDirection = EMPTY_INPUT;
int inputPWM = 0;
int MOTOR_ONE_PIN = 3;
int MOTOR_TWO_PIN = 5;
int MOTOR_THREE_PIN = 6;
time_t startingTime;
int PANIC_TIMER = 1000; //needs to be adjusted
int PANIC_PWM = 100; //needs to be adjusted
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(MOTOR_ONE_PIN, OUTPUT);
  pinMode(MOTOR_TWO_PIN, OUTPUT);
  pinMode(MOTOR_THREE_PIN, OUTPUT);
  startingTime = time(NULL);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0) {
    if (inputDirection == EMPTY_INPUT || inputDirection == NO_INPUT) {
      inputDirection = Serial.read();
      continue;
    }
    inputPWM = inputPWM * 10 + Serial.read();
  }
  if (inputDirection == NO_INPUT) {
    setMotorPwm(inputPWM);
    startingTime = time(NULL);
    inputPWM = 0;
    inputDirection = NO_INPUT;
  }
  double elapsedTime = difftime(time(NULL), startingTime);
  if (elapsedTime > PANIC_TIMER) {
    panicDoSomething();
  }
  setMotorPwm(PANIC_PWM);
}

void setMotorPwm(int input) {
  analogWrite(MOTOR_ONE_PIN, input);
  analogWrite(MOTOR_TWO_PIN, input);
  analogWrite(MOTOR_THREE_PIN, input);
}

void panicDoSomething() {
  analogWrite(MOTOR_ONE_PIN, PANIC_PWM);
  analogWrite(MOTOR_TWO_PIN, PANIC_PWM);
  analogWrite(MOTOR_THREE_PIN, PANIC_PWM);
}


