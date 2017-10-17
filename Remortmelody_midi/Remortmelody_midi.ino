//from here display define;
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
//display  settings end from xyzjoystick define;

#define Xpin A1
#define Ypin A2
#define Zpin 4
// joystick end from touch sensor define;
#define touch 2
//touch end from sound define;
#define meloPin 12
#define c2 65
#define c2s 69
#define d2 73
#define d2s 77
#define e2 82
#define f2 87
#define f2s 92
#define g2 98
#define g2s 103
#define a2 110
#define a2s 116
#define b2 123
#define c3 130
#define c3s 138

#define d3 146
#define d3s 155
#define e3 164
#define f3 174
#define f3s 185
#define g3 196
#define g3s 207
#define a3 220
#define a3s 233
#define b3 246

#define c4 261
#define c4s 277
#define d4 293
#define d4s 311
#define e4 329
#define f4 349
#define f4s 369
#define g4 392
#define g4s 415
#define a4 440
#define a4s 466
#define b4 493
#define c5 523
#define c5s 554

#define d5 587
#define d5s 622
#define e5 659
#define f5 698
#define f5s 739
#define g5 783
#define g5s 830
#define a5 880
#define a5s 932
#define b5 987


#define c6 1046
#define c6s 1108
#define d6 1174
#define d6s 1244
#define e6 1318
#define f6 1396
#define f6s 1479
#define g6 1567
#define g6s 1661
#define a6 1760
#define a6s 1864
#define b6 1975
#define c7 2093
#define c7s 2217
//sound end from super sound receive define;
#define ehPin 6
#define trPin 7
//define end


int dispstat, melostat;
double Duration = 0;
double Distance = 0;

void setup() {
  // put your setup code here, to run once:
  dispstat = 1;

  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  pinMode(Xpin, INPUT);
  pinMode(Ypin, INPUT);
  pinMode(Zpin, INPUT_PULLUP);
  pinMode(touch, INPUT);
  pinMode(meloPin, INPUT);
  pinMode(ehPin, INPUT);
  pinMode(trPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = digitalRead(touch);
  setDist();
  //  setJoystat(); do not use this;
  setMelo();
  if (dispstat != 0) {
    rendDisp();
    display.display();
  }

  if (value == HIGH) {
//    sound();
    sendmidi();
  }
  else {
    noTone(meloPin);
    sendnomidi();
  }
  //  delay(50);
}
void setMelo() {
  //setting the melo(C to upC)
  if (Distance >= 5 && Distance <= 10.5) {
    melostat = 1;
    dispstat = 1;

  }
  if (Distance >= 10.6 && Distance <= 15.5) {
    melostat = 2;
    dispstat = 1;

  }
  if (Distance >= 15.6 && Distance <= 20.5) {
    melostat = 3;
    dispstat = 1;

  }
  if (Distance >= 20.6 && Distance <= 25.5) {
    melostat = 4;
    dispstat = 1;

  }
  if (Distance >= 25.6 && Distance <= 30.5) {
    melostat = 5;
    dispstat = 1;

  }
  if (Distance >= 30.6 && Distance <= 35.5) {
    melostat = 6;
    dispstat = 1;

  }
  if (Distance >= 35.6 && Distance <= 40.5) {
    melostat = 7;
    dispstat = 1;

  }
  if (Distance >= 40.6 && Distance <= 45.5 ) {
    melostat = 8;
    dispstat = 1;

  }
  if (Distance >= 45.6 || Distance <= 4) {
    dispstat = 1;
  }
}


void setDist() {
  //checking the distance(cm);

  digitalWrite(trPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trPin, LOW);
  Duration = pulseIn(ehPin, HIGH);
  if (Duration > 0) {
    Duration = Duration / 2;
    Distance = Duration * 340 * 100 / 1000000;


  }
}

void rendDisp() {
  //rendering the display

  //melody print;
  display.clearDisplay();
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  if (analogRead(Xpin) > 600 && analogRead(Ypin) < 600) {
    if (melostat == 1 || melostat == 8) display.println("C");
    if (melostat == 2) display.println("B");
    if (melostat == 3) display.println("A");
    if (melostat == 4) display.println("G");
    if (melostat == 5) display.println("F");
    if (melostat == 6) display.println("E");
    if (melostat == 7) display.println("D");
  }
  else if (analogRead(Xpin) < 400 && analogRead(Ypin) > 400) {
    if (melostat == 1 || melostat == 8) display.println("C");
    if (melostat == 2) display.println("B");
    if (melostat == 3) display.println("A");
    if (melostat == 4) display.println("G");
    if (melostat == 5) display.println("F");
    if (melostat == 6) display.println("E");
    if (melostat == 7) display.println("D");
  }
  else {
    if (melostat == 1 || melostat == 8) display.println("C");
    if (melostat == 2) display.println("D");
    if (melostat == 3) display.println("E");
    if (melostat == 4) display.println("F");
    if (melostat == 5) display.println("G");
    if (melostat == 6) display.println("A");
    if (melostat == 7) display.println("B");
  }

  //stats print
  if (Distance >= 46 || Distance <= 4) {
    display.setCursor(30, 0);
    display.setTextSize(1);
    display.println("Over or low");
  }
  if (analogRead(Xpin) >= 600 && analogRead(Ypin) >= 600) {
    display.setCursor(30, 8);
    display.setTextSize(1);
    display.println("UP2");
  }
  if (analogRead(Xpin) <= 400 && analogRead(Ypin) <= 400) {
    display.setCursor(30, 16);
    display.setTextSize(1);
    display.println("DOWN2");
  }
  if (analogRead(Xpin) > 600 && analogRead(Ypin) < 600) {
    display.setCursor(30, 8);
    display.setTextSize(1);
    display.println("UP");
  }
  if (analogRead(Xpin) < 400 && analogRead(Ypin) > 400) {
    display.setCursor(30, 16);
    display.setTextSize(1);
    display.println("DOWN");
  }

  if (digitalRead(Zpin) == LOW) {
    display.setCursor(30, 24);
    display.setTextSize(1);
    display.println("#");
  }

  display.display();

  dispstat = 0;
}

void sound() {
  //play the melody (and this selecting the octave and sharp melody)
  if (analogRead(Xpin) >= 600 && analogRead(Ypin) >= 600) {

    if (digitalRead(Zpin) == LOW) {
      if (melostat == 1)tone(meloPin, c6s);
      if (melostat == 2)tone(meloPin, d6s);
      if (melostat == 3)tone(meloPin, e6);
      if (melostat == 4)tone(meloPin, f6s);
      if (melostat == 5)tone(meloPin, g6s);
      if (melostat == 6)tone(meloPin, a6s);
      if (melostat == 7)tone(meloPin, b6);
      if (melostat == 8)tone(meloPin, c7s);
    } else {
      if (melostat == 1)tone(meloPin, c6);
      if (melostat == 2)tone(meloPin, d6);
      if (melostat == 3)tone(meloPin, e6);
      if (melostat == 4)tone(meloPin, f6);
      if (melostat == 5)tone(meloPin, g6);
      if (melostat == 6)tone(meloPin, a6);
      if (melostat == 7)tone(meloPin, b6);
      if (melostat == 8)tone(meloPin, c7);
    }
  }
  if (analogRead(Xpin) <= 400 && analogRead(Ypin) <= 400) {

    if (digitalRead(Zpin) == LOW) {
      if (melostat == 1)tone(meloPin, c2s);
      if (melostat == 2)tone(meloPin, d2s);
      if (melostat == 3)tone(meloPin, e2);
      if (melostat == 4)tone(meloPin, f2s);
      if (melostat == 5)tone(meloPin, g2s);
      if (melostat == 6)tone(meloPin, a2s);
      if (melostat == 7)tone(meloPin, b2);
      if (melostat == 8)tone(meloPin, c3s);
    } else {
      if (melostat == 1)tone(meloPin, c2);
      if (melostat == 2)tone(meloPin, d2);
      if (melostat == 3)tone(meloPin, e2);
      if (melostat == 4)tone(meloPin, f2);
      if (melostat == 5)tone(meloPin, g2);
      if (melostat == 6)tone(meloPin, a2);
      if (melostat == 7)tone(meloPin, b2);
      if (melostat == 8)tone(meloPin, c3);
    }
  }
  if (analogRead(Xpin) > 400 && analogRead(Ypin) < 600) {

    if (digitalRead(Zpin) == LOW) {
      if (melostat == 1)tone(meloPin, c6s);
      if (melostat == 2)tone(meloPin, b5);
      if (melostat == 3)tone(meloPin, a5s);
      if (melostat == 4)tone(meloPin, g5s);
      if (melostat == 5)tone(meloPin, f5s);
      if (melostat == 6)tone(meloPin, e5);
      if (melostat == 7)tone(meloPin, d5s);
      if (melostat == 8)tone(meloPin, c5s);
    } else {
      if (melostat == 1)tone(meloPin, c6);
      if (melostat == 2)tone(meloPin, b5);
      if (melostat == 3)tone(meloPin, a5);
      if (melostat == 4)tone(meloPin, g5);
      if (melostat == 5)tone(meloPin, f5);
      if (melostat == 6)tone(meloPin, e5);
      if (melostat == 7)tone(meloPin, d5);
      if (melostat == 8)tone(meloPin, c5);
    }
  }
  if (analogRead(Xpin) < 600 && analogRead(Ypin) > 600) {

    if (digitalRead(Zpin) == LOW) {
      if (melostat == 1)tone(meloPin, c4s);
      if (melostat == 2)tone(meloPin, b3);
      if (melostat == 3)tone(meloPin, a3s);
      if (melostat == 4)tone(meloPin, g3s);
      if (melostat == 5)tone(meloPin, f3s);
      if (melostat == 6)tone(meloPin, e3);
      if (melostat == 7)tone(meloPin, d3s);
      if (melostat == 8)tone(meloPin, c3s);
    } else {
      if (melostat == 1)tone(meloPin, c4);
      if (melostat == 2)tone(meloPin, b3);
      if (melostat == 3)tone(meloPin, a3);
      if (melostat == 4)tone(meloPin, g3);
      if (melostat == 5)tone(meloPin, f3);
      if (melostat == 6)tone(meloPin, e3);
      if (melostat == 7)tone(meloPin, d3);
      if (melostat == 8)tone(meloPin, c3);
    }
  }
   if (analogRead(Xpin) <= 599 && analogRead(Xpin) >= 401 && analogRead(Ypin) <= 599 && analogRead(Ypin) >= 401 ) {
   
    if (digitalRead(Zpin) == LOW) {
      if (melostat == 1)tone(meloPin, c4s);
      if (melostat == 2)tone(meloPin, d4s);
      if (melostat == 3)tone(meloPin, e4);
      if (melostat == 4)tone(meloPin, f4s);
      if (melostat == 5)tone(meloPin, g4s);
      if (melostat == 6)tone(meloPin, a4s);
      if (melostat == 7)tone(meloPin, b4);
      if (melostat == 8)tone(meloPin, c5s);
    } else {
      if (melostat == 1)tone(meloPin, c4);
      if (melostat == 2)tone(meloPin, d4);
      if (melostat == 3)tone(meloPin, e4);
      if (melostat == 4)tone(meloPin, f4);
      if (melostat == 5)tone(meloPin, g4);
      if (melostat == 6)tone(meloPin, a4);
      if (melostat == 7)tone(meloPin, b4);
      if (melostat == 8)tone(meloPin, c5);
    }
  }

  
}

void sendmidi() {
  //play the melody (and this selecting the octave and sharp melody)
  if (analogRead(Xpin) >= 600 && analogRead(Ypin) >= 600) {

    if (digitalRead(Zpin) == LOW) {
      if (melostat == 1)tone(meloPin, c6s);
      if (melostat == 2)tone(meloPin, d6s);
      if (melostat == 3)tone(meloPin, e6);
      if (melostat == 4)tone(meloPin, f6s);
      if (melostat == 5)tone(meloPin, g6s);
      if (melostat == 6)tone(meloPin, a6s);
      if (melostat == 7)tone(meloPin, b6);
      if (melostat == 8)tone(meloPin, c7s);
    } else {
      if (melostat == 1)tone(meloPin, c6);
      if (melostat == 2)tone(meloPin, d6);
      if (melostat == 3)tone(meloPin, e6);
      if (melostat == 4)tone(meloPin, f6);
      if (melostat == 5)tone(meloPin, g6);
      if (melostat == 6)tone(meloPin, a6);
      if (melostat == 7)tone(meloPin, b6);
      if (melostat == 8)tone(meloPin, c7);
    }
  }
  if (analogRead(Xpin) <= 400 && analogRead(Ypin) <= 400) {

    if (digitalRead(Zpin) == LOW) {
      if (melostat == 1)tone(meloPin, c2s);
      if (melostat == 2)tone(meloPin, d2s);
      if (melostat == 3)tone(meloPin, e2);
      if (melostat == 4)tone(meloPin, f2s);
      if (melostat == 5)tone(meloPin, g2s);
      if (melostat == 6)tone(meloPin, a2s);
      if (melostat == 7)tone(meloPin, b2);
      if (melostat == 8)tone(meloPin, c3s);
    } else {
      if (melostat == 1)tone(meloPin, c2);
      if (melostat == 2)tone(meloPin, d2);
      if (melostat == 3)tone(meloPin, e2);
      if (melostat == 4)tone(meloPin, f2);
      if (melostat == 5)tone(meloPin, g2);
      if (melostat == 6)tone(meloPin, a2);
      if (melostat == 7)tone(meloPin, b2);
      if (melostat == 8)tone(meloPin, c3);
    }
  }
  if (analogRead(Xpin) > 400 && analogRead(Ypin) < 600) {

    if (digitalRead(Zpin) == LOW) {
      if (melostat == 1)tone(meloPin, c6s);
      if (melostat == 2)tone(meloPin, b5);
      if (melostat == 3)tone(meloPin, a5s);
      if (melostat == 4)tone(meloPin, g5s);
      if (melostat == 5)tone(meloPin, f5s);
      if (melostat == 6)tone(meloPin, e5);
      if (melostat == 7)tone(meloPin, d5s);
      if (melostat == 8)tone(meloPin, c5s);
    } else {
      if (melostat == 1)tone(meloPin, c6);
      if (melostat == 2)tone(meloPin, b5);
      if (melostat == 3)tone(meloPin, a5);
      if (melostat == 4)tone(meloPin, g5);
      if (melostat == 5)tone(meloPin, f5);
      if (melostat == 6)tone(meloPin, e5);
      if (melostat == 7)tone(meloPin, d5);
      if (melostat == 8)tone(meloPin, c5);
    }
  }
  if (analogRead(Xpin) < 600 && analogRead(Ypin) > 600) {

    if (digitalRead(Zpin) == LOW) {
      if (melostat == 1)tone(meloPin, c4s);
      if (melostat == 2)tone(meloPin, b3);
      if (melostat == 3)tone(meloPin, a3s);
      if (melostat == 4)tone(meloPin, g3s);
      if (melostat == 5)tone(meloPin, f3s);
      if (melostat == 6)tone(meloPin, e3);
      if (melostat == 7)tone(meloPin, d3s);
      if (melostat == 8)tone(meloPin, c3s);
    } else {
      if (melostat == 1)tone(meloPin, c4);
      if (melostat == 2)tone(meloPin, b3);
      if (melostat == 3)tone(meloPin, a3);
      if (melostat == 4)tone(meloPin, g3);
      if (melostat == 5)tone(meloPin, f3);
      if (melostat == 6)tone(meloPin, e3);
      if (melostat == 7)tone(meloPin, d3);
      if (melostat == 8)tone(meloPin, c3);
    }
  }

  if (analogRead(Xpin) <= 599 && analogRead(Xpin) >= 401 && analogRead(Ypin) <= 599 && analogRead(Ypin) >= 401 ) {

    if (digitalRead(Zpin) == LOW) {
      if (melostat == 1)Serial.write(51);
      if (melostat == 2)Serial.write(53);
      if (melostat == 3)Serial.write(54);
      if (melostat == 4)Serial.write(56);
      if (melostat == 5)Serial.write(58);
      if (melostat == 6)Serial.write(60);
      if (melostat == 7)Serial.write(61);
      if (melostat == 8)Serial.write(63);
    } else {
      if (melostat == 1)Serial.write(50);
      if (melostat == 2)Serial.write(52);
      if (melostat == 3)Serial.write(54);
      if (melostat == 4)Serial.write(55);
      if (melostat == 5)Serial.write(57);
      if (melostat == 6)Serial.write(59);
      if (melostat == 7)Serial.write(61);
      if (melostat == 8)Serial.write(62);
    }
  }
}
void sendnomidi() {
  Serial.write(0);
}








