#include <ArduinoJson.h>

StaticJsonDocument<200> inputs;

// usonic sensor
int trig = 7;
int echo = 6;
int usmax = 3000;

// ldr sensor
int ldr = 0;

void setup() {
  Serial.begin(9600);
  usonicsetup();
  pinMode(13, OUTPUT);
}

void loop() {
  inputs["usonic"] = usonic_input();
  inputs["ldr"] = ldr_input();
  
  serializeJson(inputs, Serial); // send our JSON across serial
  Serial.println(""); // just a newline to help parsing python side
  delay(100);
}

//
// START USONIC
//
void usonicsetup() {
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
}

long usonic(long utimeout) {
  long b;
  if (digitalRead(echo) == HIGH) return 0;
  digitalWrite(trig, HIGH);
  delay(1);
  digitalWrite(trig, LOW);
  
  long utimer = micros();
  while ( (digitalRead(echo) == LOW) && ((micros() - utimer) < 1000) ) { }

  utimer = micros();
  while ( (digitalRead(echo) == HIGH) && ((micros() - utimer) < utimeout) ) { }

  b = micros() - utimer;
  if (b == 0) b = utimeout;
  return b;
}

int usonic_input() {
  int d;
  d = usonic(11600) / 58;
  // usonic sensor will sometimes randomly throw out 0 or 200 so we
  // just ignore them with the following if statement
  if (d < 100 && d > 0) return 1;
  else return 0;
}
//
// END USONIC
//

//
// START LDR
//
int ldr_input() {
  return analogRead(ldr);
}
//
// END LDR
//
