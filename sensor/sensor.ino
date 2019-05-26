 #include <ArduinoJson.h>

StaticJsonDocument<200> inputs;

// usonic sensor
int trig = 7;
int echo = 6;
int usmax = 3000;

// ldr sensor
int ldr = 0;

// temp sensor
int temp = 1;

// joystick
int x = 2;
int y = 3;

// button
int button = 8;

void setup() {
  Serial.begin(9600);
  usonicsetup();
  pinMode(8, INPUT);
}

void loop() {
  inputs["usonic"] = usonic_input();
  inputs["ldr"] = ldr_input();
  inputs["temp"] = temp_input();
  inputs["joyx"] = joyx_input();
  inputs["joyy"] = joyy_input();
  inputs["button"] = button_input();
  
  serializeJson(inputs, Serial); // send our JSON across serial
  Serial.println(""); // just a newline to help parsing python side
  delay(50);
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

//
// START TEMP
//
int temp_input() {
  return analogRead(temp);
}
//
// END TEMP
//

//
// START JOYSTICK
//
int joyx_input() {
  return analogRead(x) / 4 - 128;
}

int joyy_input() {
  return analogRead(y) / 4 - 128;
}
//
// END JOYSTICK
//

//
// START BUTTON
//
int button_input() {
  return digitalRead(button);
}
//
// END BUTTON
//
