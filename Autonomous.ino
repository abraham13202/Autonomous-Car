char t;
#define echoPinL 2 // attach pin D2 Arduino to pin Echo of HC-SR04 #define trigPinL 3 //attach pin D3 Arduino to pin Trig of HC-SR04 #define echoPinR 4 // attach pin D4 Arduino to pin Echo of HC-SR04 #define trigPinR 5 //attach pin D5 Arduino to pin Trig of HC-SR04 #define echoPinB 6 // attach pin D6 Arduino to pin Echo of HC-SR04 #define trigPinB 7 //attach pin D7 Arduino to pin Trig of HC-SR04 #define echoPinF 8 // attach pin D8 Arduino to pin Echo of HC-SR04 #define trigPinF 9 //attach pin D9 Arduino to pin Trig of HC-SR04

// defines variables
long duration1; // variable for the duration of sound wave travel int distance1; // variable for the distance measurement

long duration2; // variable for the duration of sound wave travel int distance2; // variable for the distance measurement

long duration3; // variable for the duration of sound wave travel int distance3; // variable for the distance measurement

long duration0; // variable for the duration of sound wave travel int distance0; // variable for the distance measurement



void setup() {
  pinMode(trigPinF, OUTPUT); // Sets the trigPinF as an OUTPUT pinMode(echoPinF, INPUT); // Sets the echoPinF as an INPUT pinMode(trigPinL, OUTPUT); // Sets the trigPinL as an OUTPUT pinMode(echoPinL, INPUT); // Sets the echoPinL as an INPUT pinMode(trigPinR, OUTPUT); // Sets the trigPinR as an OUTPUT pinMode(echoPinR, INPUT); // Sets the echoPinR as an INPUT pinMode(trigPinB, OUTPUT); // Sets the trigPinB as an OUTPUT pinMode(echoPinB, INPUT); // Sets the echoPinB as an INPUT pinMode(13,OUTPUT);		//left motors forward pinMode(12,OUTPUT);		//left motors reverse pinMode(11,OUTPUT);		//right motors forward pinMode(10,OUTPUT);		//right motors reverse pinMode(9,OUTPUT);	//Led
  Serial.begin(9600);

}


void _stop() {
  digitalWrite(13, LOW); digitalWrite(12, LOW); digitalWrite(11, LOW); digitalWrite(10, LOW);
}

void forward() {
  digitalWrite(11, LOW); digitalWrite(13, LOW); digitalWrite(12, HIGH); digitalWrite(10, HIGH);
}
void backward() {
  digitalWrite(13, HIGH); digitalWrite(11, HIGH);
}
void left() {
  digitalWrite(11, LOW); digitalWrite(12, LOW); digitalWrite(10, LOW); digitalWrite(13, HIGH); delay(0);
}
void right() {
  digitalWrite(13, LOW); digitalWrite(12, LOW); digitalWrite(10, LOW); digitalWrite(11, HIGH); delay(0);
}



void autonomousMode() {
  // Serial.print("\nDistL: ");
  // Serial.print(distance1);
  // Serial.print("\nDistR: ");
  // Serial.print(distance2);
  if (distance0 > 8 && distance1 > 10 && distance2 > 10 && distance3 > 10) {
    forward();
    Serial.println("\nforward\n");

  }
  else if (distance1 < 10 && distance2 > 10) {
    left();
    Serial.println("\nright\n");

  }
  else if (distance2 < 10 && distance1 > 10) {
    right();
    Serial.println("\nleft\n");

  }
  else if (distance1 < 10 && distance2 < 10 && distance3 > 10) {
    backward();
    Serial.println("\nback\n");

  }
  else if (distance0 < 8 || distance1 < 10 && distance2 < 10 && distance3 < 10) {
    _stop();

    Serial.println("\nstop\n");
  }
}



void loop() {
  digitalWrite(trigPinF, LOW); delayMicroseconds(2); digitalWrite(trigPinF, HIGH); delayMicroseconds(10); digitalWrite(trigPinF, LOW);
  duration0 = pulseIn(echoPinF, HIGH);
  distance0 = duration0 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)


  digitalWrite(trigPinL, LOW); delayMicroseconds(2); digitalWrite(trigPinL, HIGH); delayMicroseconds(10); digitalWrite(trigPinL, LOW); duration1 = pulseIn(echoPinL, HIGH);
  distance1 = duration1 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)


  digitalWrite(trigPinR, LOW); delayMicroseconds(2);

  digitalWrite(trigPinR, HIGH); delayMicroseconds(10); digitalWrite(trigPinR, LOW); duration2 = pulseIn(echoPinR, HIGH); distance2 = duration2 * 0.034 / 2;

  digitalWrite(trigPinB, LOW); delayMicroseconds(2); digitalWrite(trigPinB, HIGH); delayMicroseconds(10); digitalWrite(trigPinB, LOW); duration3 = pulseIn(echoPinB, HIGH); distance3 = duration3 * 0.034 / 2;

  // Serial.print("\nDistL: ");
  // Serial.print(distance1);
  // Serial.print("\nDistR: ");
  // Serial.print(distance2);
  // Serial.print("\nDistB: ");
  // Serial.print(distance3);


  if (Serial.available()) {
    t = Serial.read(); Serial.println(t);

  }


  if (t != 'A') {
    _stop();
    if (distance0 > 8 && distance1 > 8 && distance2 > 8 && distance3 > 10) {
      if (t == 'F') {	//move forward(all motors rotate in forward direction) forward();
      }
      else if (t == 'B') {	//move reverse (all motors rotate in reverse direction) backward();
      }
      else if (t == 'L') {	//turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
        right();

      }
      else if (t == 'R') {	//turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
        left();

      }
      else if (t == 'S') {	//STOP (all motors stop)
        _stop();

      }
    }

    else {
      if (distance3 > 10 && t == 'B') {

        backward();
      }

      else if (distance0 > 8 && distance1 > 8 && distance2 > 8 && t == 'F') {
        forward();
      }
      else {
        _stop();

      }
    }
  }

  else if (t == 'A') {
    autonomousMode();
  }
  delay(5);
}
