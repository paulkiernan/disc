#include <Servo.h>

#define MIN_PULSE_LENGTH 1000
#define LOW_PULSE_LENGTH 1100
#define HIGH_PULSE_LENGTH 1200
#define MAX_PULSE_LENGTH 2000


Servo motor;
int motorPin = 8;
int buttonPin = 4;
boolean running = false;
boolean firstRun = true;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buttonPin, INPUT);
  motor.attach(motorPin, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);

  calibrate();
}

void loop() {

  if(running) {
    if (firstRun) {
      blinkStart();

      firstRun = false;
      accelerateEngineSmoothly();
    }

    runNormally();
  }
  else {
    stopEngine();
  }

  delay(500);
}

void calibrate() {
  motor.write(180);
  delay(13000);
  blink(1);

  motor.write(0);
  delay(10000);
  blink(2);

  running = true;
}

void accelerateEngineSmoothly() {
  int motorSpeed = MIN_PULSE_LENGTH + 50;

  while(motorSpeed < HIGH_PULSE_LENGTH) {
    motorSpeed = motorSpeed + 1;
    motor.writeMicroseconds(motorSpeed);
    delay(100);
  }
}

int runNormally() {
  // 1
  for (int i = 1; i <= 10; i++){
    if(!running) {
      return 0;
    }

    if (i == 1) {
      motor.writeMicroseconds(HIGH_PULSE_LENGTH);
    }
    delay(100);
  }

  // 2
  int motorSpeed = HIGH_PULSE_LENGTH;

  while(motorSpeed > LOW_PULSE_LENGTH) {
    if(!running) {
      return 0;
    }

    motorSpeed = motorSpeed - 1;
    motor.writeMicroseconds(motorSpeed);
    delay(100);
  }

  //3
  for (int i = 1; i <= 5; i++){
    if(!running) {
      return 0;
    }

    if (i == 1) {
      motor.writeMicroseconds(LOW_PULSE_LENGTH);
    }
    delay(100);
  }


  // 4
  motorSpeed = LOW_PULSE_LENGTH;

  while(motorSpeed < HIGH_PULSE_LENGTH) {
    if(!running) {
      return 0;
    }

    motorSpeed = motorSpeed + 1;
    motor.writeMicroseconds(motorSpeed);
    delay(75);
  }

  return 1;
}

void stopEngine() {
  motor.writeMicroseconds(MIN_PULSE_LENGTH);
  firstRun = true;

  blinkStop();
}

void blink(int count) {
  for (int i = 1; i <= count; i++){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
    digitalWrite(LED_BUILTIN, LOW);
    delay(250);
  }
}

void blinkStart() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
}

void blinkStop() {
  for (int i = 1; i <= 5; i++){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(25);
    digitalWrite(LED_BUILTIN, LOW);
    delay(25);
  }
}
