// defining pins
const int trig = 11;            // HC-SR04 TRIG pin goes to arduino's digital pin 11
const int echo = 12;            // HC-SR04 ECHO pin goes to arduino's digital pin 12

// KOOKBOOK L9110S MOTORDRIVER
const int KookMotorA_pin1 = 2;  // MotorA pin A-1A goes to arduino's digital pin 2
const int KookMotorA_pin2 = 3;  // MotorA pin A-1B goes to arduino's digital pin 3
const int KookMotorB_pin1 = 4;  // MotorB pin B-1A goes to arduino's digital pin 4
const int KookMotorB_pin2 = 5; //  MotorB pin B-1B goes to arduino's digital pin 5

// TB6612 MOTORDRIVER
const int MotorA_pin1 = 6;  // Pin AIN1 connects to digital pin 6
const int MotorA_pin2 = 7;  // Pin AIN2 connects to digital pin 7
const int MotorB_pin1 = 8;  // Pin BIN1 connects to digital pin 8
const int MotorB_pin2 = 9;  // Pin BIN2 connects to digital pin 9
const int PWM = 10;         // Pins PWMA and PWMB both connect to digital pin 10

// HC-SR04 calculation variables
long time;
int distance;

void setup() {
  // Assigning HC-SR04 pins
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  // Assigning Motor Drivers pins
  // KOOKBOOK L9110S MOTOR DRIVER 
  pinMode(KookMotorA_pin1, OUTPUT);
  pinMode(KookMotorA_pin2, OUTPUT);
  pinMode(KookMotorB_pin1, OUTPUT);
  pinMode(KookMotorB_pin2, OUTPUT);

  // TB6112 Motor Driver
  pinMode(MotorA_pin1, OUTPUT);
  pinMode(MotorA_pin2, OUTPUT);
  pinMode(MotorB_pin1, OUTPUT);
  pinMode(MotorB_pin2, OUTPUT);
  pinMode(PWM, OUTPUT);

  // (REQUIRED) Start serial communication
  // With Arduino devices, they usual have a default baud rate of 9600
  Serial.begin(9600); 

}

void loop() {
  // Clear the trigger pin
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  // set the trigger pin to HIGH state for 10µs
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);

  // make echo pin return echo distance
  time = pulseIn(echo, HIGH);

  // calculate the distance in cm
  distance = time*0.034/2;

  // Output of HC-SR04 in cm
  Serial.print("Distance: ");
  Serial.println(distance); 
  
  // move forward
  while(distance >= 45 ) {
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    time = pulseIn(echo, HIGH);
    distance = time*0.034/2;
    Serial.print("Distance: ");
    Serial.println(distance);

    digitalWrite(KookMotorA_pin1, HIGH);
    digitalWrite(KookMotorA_pin2, LOW);
    digitalWrite(KookMotorB_pin1, LOW);
    digitalWrite(KookMotorB_pin2, HIGH);

    analogWrite(PWM, 160);
    digitalWrite(MotorA_pin1, HIGH);
    digitalWrite(MotorA_pin2, LOW);
    digitalWrite(MotorB_pin1, HIGH);
    digitalWrite(MotorB_pin2, LOW);

    if(distance < 45){
      digitalWrite(KookMotorA_pin1, LOW);
      digitalWrite(KookMotorA_pin2, LOW);
      digitalWrite(KookMotorB_pin1, LOW);
      digitalWrite(KookMotorB_pin2, LOW);

      analogWrite(PWM, 160);
      digitalWrite(MotorA_pin1, LOW);
      digitalWrite(MotorA_pin2, LOW);
      digitalWrite(MotorB_pin1, LOW);
      digitalWrite(MotorB_pin2, LOW);
    }
  }
  // turn RC until no blocking object
  while(distance < 45){
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    time = pulseIn(echo, HIGH);
    distance = time*0.034/2;
    Serial.print("Distance: ");
    Serial.println(distance);

    digitalWrite(KookMotorA_pin1, HIGH);
    digitalWrite(KookMotorA_pin2, LOW);
    digitalWrite(KookMotorB_pin1, HIGH);
    digitalWrite(KookMotorB_pin2, LOW);

    analogWrite(PWM, 255);
    digitalWrite(MotorA_pin1, HIGH);
    digitalWrite(MotorA_pin2, LOW);
    digitalWrite(MotorB_pin1, LOW);
    digitalWrite(MotorB_pin2, HIGH);

    if(distance > 44){
      digitalWrite(KookMotorA_pin1, LOW);
      digitalWrite(KookMotorA_pin2, LOW);
      digitalWrite(KookMotorB_pin1, LOW);
      digitalWrite(KookMotorB_pin2, LOW);

      analogWrite(PWM, 130);
      digitalWrite(MotorA_pin1, LOW);
      digitalWrite(MotorA_pin2, LOW);
      digitalWrite(MotorB_pin1, LOW);
      digitalWrite(MotorB_pin2, LOW);
      //break;
    }
  }
  
}
