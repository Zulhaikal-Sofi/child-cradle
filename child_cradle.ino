#include <SoftwareSerial.h>
#include <Servo.h>
Servo myservo;
SoftwareSerial BTserial(10, 11); // RX | TX

int soundsensor = 2;
int vibrateSensor = 3;
int soundval, vibval;
int state = 0;
int BluetoothData;
int angle = 0;
int speakerPin = 8;
int servomotor = 12;
int numTones = 62;
int tones[] = {587, 784, 880, 988, 988, 988, 988, 988, 988, 988, 932, 988, 784, 784, 784, 784, 784, 784, 784, 880, 988, 1047, 1047, 1319, 1319, 1319, 1319, 1175, 1047, 988, 988, 988, 784, 880, 988, 1047, 1047, 1319, 1319, 1319, 1319, 1175, 1047, 988, 988, 784, 784, 784, 784, 880, 988, 988, 988, 1047, 880, 880, 880, 988, 784, 784, 784, 784};
//            You are my sunshine
char c = ' ';
int x = 1;
String s, kk;
int val;
int tempPin = A0;
int stat = 0;
int stata = 0;
int a;
int d;
char b = ' ';


void setup() {


  Serial.begin(9600);
  Serial.println("Arduino is ready");
  pinMode(soundsensor, INPUT);
  pinMode(vibrateSensor, INPUT);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  BTserial.begin(9600);

}

void loop() {



  soundval = digitalRead(soundsensor);
  vibval = digitalRead(vibrateSensor);
  temp_sensor();


  if (soundval == HIGH) {

    Serial.println("nangis");
    BTserial.print("A");
    BTserial.flush();
    buaian();

  }
  else if (vibval == HIGH) {

    Serial.println("Bergerak");
    BTserial.print("B");
    BTserial.flush();
    buaian();

  }





  if (BTserial.available()) {
    c = BTserial.read();
    Serial.write(c);
    b = c;

    if (c == '\r' || c == '\n') {
      s = "";
    }

    else {
      s = s + c;

      s = "";
      return;

    }

  }

  if (b == 'M') {
    Serial.println();
    Serial.print("music on");
    Serial.println();
    if (stat == 1) {
      stat = 0;
    }
    else {
      stat = 1;
    }
  }
  else if ( b == 'G') {
    Serial.println();
    stat = 0;
    a = 30;
    noTone(speakerPin);
    a = 0;
  }
  else {
    noTone(speakerPin);
  }

  if (stat == 1) {
    speaker();
  }
  else {
    noTone(speakerPin);
  }
  if (b == 'N') {
    Serial.println();
    Serial.print("motor on");
    Serial.println();
    if (stata == 1) {
      stata = 0;
    }
    else {
      stata = 1;
    }
  }
  else if ( b == 'F') {
    Serial.println();
    stata = 0;
    d = 30;
    noTone(speakerPin);
    d = 0;
  }

  if (stata == 1) {
    motor_on();
  }
  else {
    noTone(speakerPin);

  }
}

void motor_on() {

  if (d < 30) {
    BTserial.print("D");
    BTserial.flush();
    for (int i = 0; i < numTones; i++)
    {
      noTone(speakerPin);

      int y = x % 2;
      if (y == 0) {
        myservo.write(0);

      }
      if (y == 1) {
        myservo.write(20);

      }

      x++;
      delay(300);


    }

    d++;
    Serial.println();
    Serial.print(d);
    Serial.println();
  }
}
void speaker() {

  if (a < 30) {
    delay(1000);
    BTserial.print("E");
    BTserial.flush();
    for (int i = 0; i < numTones; i++) {
      tone(speakerPin, tones[i]);
      delay(300);

    }
    a++;
    noTone(speakerPin);
    Serial.println();
    Serial.print(a);
    Serial.println();
  }

}


void temp_sensor() {
  val = analogRead(tempPin);
  float mv = ( val / 1024.0) * 4200;
  float cel = mv / 10;


  Serial.print("TEMPRATURE = ");
  Serial.print(cel);


  BTserial.print(cel);
  BTserial.print("*C");
  BTserial.flush();
  Serial.println();
  delay(1000);

}

void buaian() {


  for (int i = 0; i < numTones; i++)
  {
    tone(speakerPin, tones[i]);
    int y = x % 2;
    if (y == 0) {
      myservo.write(0);

    }
    if (y == 1) {
      myservo.write(20);

    }

    x++;
    delay(300);

  }
  noTone(speakerPin);
}
