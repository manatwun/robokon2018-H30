#include <PS3BT.h>
#include <usbhub.h>
#include <FlexiTimer2.h>
#include <TimerOne.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.

volatile int MR1 = 0;
volatile int MR2 = 0;
volatile int MR3 = 0;
volatile int FL = 0;
volatile int FR = 0;
volatile int RL = 0;
volatile int RR = 0;
volatile int FLB = 0;
volatile int FRB = 0;
volatile int RLB = 0;
volatile int RRB = 0;

volatile int FLCWD;
volatile int FRCWD;
volatile int RLCWD;
volatile int RRCWD;
volatile int FLCCWD;
volatile int FRCCWD;
volatile int RRCCWD;
volatile int RLCCWD;

volatile int FLCWDB;
volatile int FRCWDB;
volatile int RLCWDB;
volatile int RRCWDB;
volatile int FLCCWDB;
volatile int FRCCWDB;
volatile int RRCCWDB;
volatile int RLCCWDB;

volatile int counter1 = 0;
volatile int counter2 = 0;
volatile int counter3 = 0;
volatile int END = 0;

#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

#define FLCW 30 //前(front)左(left)のCW//
#define FLPWM 3
#define FLCCW 32

#define FRCW 38 //前(front)右(right)のCW//
#define FRPWM 5
#define FRCCW 40

#define RLCW 42 //後ろ(rear)左(left)のCW//
#define RLPWM 6
#define RLCCW 44

#define RRCW 46 //後ろ(rear)右(rightt)のCW//
#define RRPWM 7
#define RRCCW 48

#define M1CW 22
#define M1PWM 0
#define M1CCW 23

#define M2CW 25
#define M2PWM 1
#define M2CCW 24

#define M3CW 27
#define M3PWM 2
#define M3CCW 26

#define MRTV 150

#define EPIN1 4//19
#define EPIN2 3//20
#define EPIN3 2//21

#define AIR 34


USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so

/* You can create the instance of the class in two ways */
PS3BT PS3(&Btd); // This will just create the instance
//PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

bool printTemperature, printAngle;

void PWM() {
  if (FL < FLB) {
    FLB = FLB - 1;
    if (FLCWD == 1) {
      digitalWrite(FLCW, HIGH);
      digitalWrite(FLCCW, LOW);
    } else if (FLCWD == 0) {
      digitalWrite(FLCCW, HIGH);
      digitalWrite(FLCW, LOW);
    }
    if (FLCWDB != FLCWD) {
      FLB = 0;
      FL = 0;
    }
    FLCWDB = FLCWD;
    analogWrite(FLPWM, FLB);
  } else if (FL > FLB) {
    FLB = FLB + 1;
    if (FLCWD == 1) {
      digitalWrite(FLCW, HIGH);
      digitalWrite(FLCCW, LOW);
    } else if (FLCWD == 0) {
      digitalWrite(FLCCW, HIGH);
      digitalWrite(FLCW, LOW);
    }
    if (FLCWDB != FLCWD) {
      FLB = 0;
      FL = 0;
    }
    FLCWDB = FLCWD;
    analogWrite(FLPWM, FLB);
  }
  if (FR < FRB) {
    FRB = FRB - 1;
    if (FRCWD == 1) {
      digitalWrite(FRCW, HIGH);
      digitalWrite(FRCCW, LOW);
    } else if (FRCWD == 0) {
      digitalWrite(FRCCW, HIGH);
      digitalWrite(FRCW, LOW);
    }
    if (FRCWDB != FRCWD) {
      FRB = 0;
      FR = 0;
    }
    FRCWDB = FRCWD;
    analogWrite(FRPWM, FRB);
  } else if (FR > FRB) {
    FRB = FRB + 1;
    if (FRCWD == 1) {
      digitalWrite(FRCW, HIGH);
      digitalWrite(FRCCW, LOW);
    } else if (FRCWD == 0) {
      digitalWrite(FRCCW, HIGH);
      digitalWrite(FRCW, LOW);
    }
    if (FRCWDB != FRCWD) {
      FRB = 0;
      FR = 0;
    }
    FRCWDB = FRCWD;
    analogWrite(FRPWM, FRB);
  }
  if (RL < RLB) {
    RLB = RLB - 1;
    if (RLCWD == 1) {
      digitalWrite(RLCW, HIGH);
      digitalWrite(RLCCW, LOW);
    } else if (RLCWD == 0) {
      digitalWrite(RLCCW, HIGH);
      digitalWrite(RLCW, LOW);
    }
    if (RLCWDB != RLCWD) {
      RLB = 0;
      RL = 0;
    }
    RLCWDB = RLCWD;
    analogWrite(RLPWM, RLB);
  } else if (RL > RLB) {
    RLB = RLB + 1;
    if (RLCWD == 1) {
      digitalWrite(RLCW, HIGH);
      digitalWrite(RLCCW, LOW);
    } else if (RLCWD == 0) {
      digitalWrite(RLCCW, HIGH);
      digitalWrite(RLCW, LOW);
    }
    if (RLCWDB != RLCWD) {
      RLB = 0;
      RL = 0;
    }
    RLCWDB = RLCWD;
    analogWrite(RLPWM, RLB);
  } else if (RL > RLB) {
    RLB = RLB + 1;
    if (RLCWD == 1) {
      digitalWrite(RLCW, HIGH);
      digitalWrite(RLCCW, LOW);
    } else if (RLCWD == 0) {
      digitalWrite(RLCCW, HIGH);
      digitalWrite(RLCW, LOW);
    }
    if (RLCWDB != RLCWD) {
      RLB = 0;
      RL = 0;
    }
    RLCWDB = RLCWD;
    analogWrite(RLPWM, RLB);
  }
  if (RR < RRB) {
    RRB = RRB - 1;
    if (RRCWD == 1) {
      digitalWrite(RRCW, HIGH);
      digitalWrite(RRCCW, LOW);
    } else if (RRCWD == 0) {
      digitalWrite(RRCCW, HIGH);
      digitalWrite(RRCW, LOW);
    }
    if (RRCWDB != RRCWD) {
      RRB = 0;
      RR = 0;
    }
    RRCWDB = RRCWD;
    analogWrite(RRPWM, RRB);
  } else if (RR > RRB) {
    RRB = RRB + 1;
    if (RRCWD == 1) {
      digitalWrite(RRCW, HIGH);
      digitalWrite(RRCCW, LOW);
    } else if (RRCWD == 0) {
      digitalWrite(RRCCW, HIGH);
      digitalWrite(RRCW, LOW);
    }
    if (RRCWDB != RRCWD) {
      RRB = 0;
      RR = 0;
    }
    RRCWDB = RRCWD;
    analogWrite(RRPWM, RRB);
  } else if (RR > RRB) {
    RRB = RRB + 1;
    if (RRCWD == 1) {
      digitalWrite(RRCW, HIGH);
      digitalWrite(RRCCW, LOW);
    } else if (RRCWD == 0) {
      digitalWrite(RRCW, HIGH);
      digitalWrite(RRCW, LOW);
    }
    if (RRCWDB != RRCWD) {
      RRB = 0;
      RR = 0;
    }
    RRCWDB = RRCWD;
    analogWrite(RRPWM, RRB);
  }

}
void shot() {
  if (counter1 + 10 < counter2 && counter1 + 10 < counter3) {
    MR2 = MR2 + 1;
    MR3 = MR3 + 1;
    analogWrite(M1PWM, MR1);
    analogWrite(M2PWM, MR2);
    analogWrite(M3PWM, MR3);
  } else if (counter1 - 10 > counter2 && counter1 + 10 < counter3) {
    MR2 = MR2 - 1;
    MR3 = MR3 + 1;
    analogWrite(M1PWM, MR1);
    analogWrite(M2PWM, MR2);
    analogWrite(M3PWM, MR3);
  } else if (counter1 - 10 > counter2 && counter1 - 10 > counter3) {
    MR2 = MR2 - 1;
    MR3 = MR2 - 1;
    analogWrite(M1PWM, MR1);
    analogWrite(M2PWM, MR2);
    analogWrite(M3PWM, MR3);
  } else if (counter1 + 10 < counter2 && counter1 - 10 > counter3) {
    MR2 = MR2 + 1;
    MR3 = MR3 - 1;
    analogWrite(M1PWM, MR1);
    analogWrite(M2PWM, MR2);
    analogWrite(M3PWM, MR3);
  } else if (counter1 + 10 > counter2 && counter1 - 10 < counter2 && counter1 + 10 < counter3 ) {
    MR3 = MR3 - 1;
    analogWrite(M1PWM, MR1);
    analogWrite(M2PWM, MR2);
    analogWrite(M3PWM, MR3);
  } else if (counter1 + 10 > counter2 && counter1 - 10 < counter2 && counter1 - 10 > counter3 ) {
    MR3 = MR3 + 1;
    analogWrite(M1PWM, MR1);
    analogWrite(M2PWM, MR2);
    analogWrite(M3PWM, MR3);
  } else if (counter1 + 10 > counter3 && counter1 - 10 < counter3 && counter1 + 10 < counter2 ) {
    MR2 = MR2 - 1;
    analogWrite(M1PWM, MR1);
    analogWrite(M2PWM, MR2);
    analogWrite(M3PWM, MR3);
  } else if (counter1 + 10 > counter3 && counter1 - 10 < counter3 && counter1 - 10 > counter2 ) {
    MR2 = MR2 + 1;
    analogWrite(M1PWM, MR1);
    analogWrite(M2PWM, MR2);
    analogWrite(M3PWM, MR3);
  } else {
    END = 1;
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(EPIN1, INPUT);
  pinMode(EPIN2, INPUT);
  pinMode(EPIN3, INPUT);


  FlexiTimer2::set(5, shot);



  TCCR2B = (TCCR2B & 0b11111000) | 0x02;
  TCCR3B = (TCCR3B & 0b11111000) | 0x02;
  TCCR4B = (TCCR4B & 0b11111000) | 0x02;

  pinMode(FLCW, OUTPUT);
  pinMode(FLCCW, OUTPUT);
  pinMode(FRCW, OUTPUT);
  pinMode(FRCCW, OUTPUT);
  pinMode(RLCW, OUTPUT);
  pinMode(RLCCW, OUTPUT);
  pinMode(RRCW, OUTPUT);
  pinMode(RRCCW, OUTPUT);

  for (int c = 0; c < 20; c++) {

    digitalWrite(FLCCW, LOW);
    digitalWrite(FRCCW, LOW);
    digitalWrite(RLCCW, LOW);
    digitalWrite(RRCCW, LOW);
    digitalWrite(FLCW, HIGH);
    digitalWrite(FRCW, HIGH);
    digitalWrite(RLCW, HIGH);
    digitalWrite(RRCW, HIGH);
    delay(50);

    digitalWrite(FLCW, LOW);
    digitalWrite(FRCW, LOW);
    digitalWrite(RLCW, LOW);
    digitalWrite(RRCW, LOW);
    analogWrite(FLPWM, 240);
    analogWrite(FRPWM, 240);
    analogWrite(RLPWM, 240);
    analogWrite(RRPWM, 240);

    delay(50);

    analogWrite(FLPWM, 0);
    analogWrite(FRPWM, 0);
    analogWrite(RLPWM, 0);
    analogWrite(RRPWM, 0);
    digitalWrite(FLCCW, HIGH);
    digitalWrite(FRCCW, HIGH);
    digitalWrite(RLCCW, HIGH);
    digitalWrite(RRCCW, HIGH);
    delay(50);
  }



  digitalWrite(RLCCW, LOW);
  digitalWrite(RRCCW, LOW);
  digitalWrite(FLCCW, LOW);
  digitalWrite(FRCCW, LOW);

  delay(1000);

  Timer1.initialize(1800);
  Timer1.attachInterrupt(PWM);
  Timer1.stop();
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));

}
void loop() {

  unsigned long int XY;
  int i;
  double xys, PWMX, PWMY, slope, xpy;
  double speedy, speedx;

  Usb.Task();

  double LY = 255 - (PS3.getAnalogHat(LeftHatY));
  double RY = 255 - (PS3.getAnalogHat(RightHatY));

  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    Timer1.resume();

    if  (PS3.getAnalogHat(RightHatX) > 137 || PS3.getAnalogHat(RightHatX) < 117 || RY > 137 || RY < 117) {

      if ( PS3.getAnalogHat(RightHatX) >= 128 && RY >= 128 ) {
        xys = (double)RY / PS3.getAnalogHat(RightHatX);
        if (0.8 < xys && 1.2 > xys) {
          if (0.8 < xys ) {

            FL = 0;
            FR = 0;
            RL = 0;
            RR = 0;
            FLCWD = 1;
            RRCWD = 1;
            FRCCWD = 1;
            RLCCWD = 1;
            FLCCWD = 0;
            RRCCWD = 0;
            FRCWD = 0;
            RLCWD = 0;
          } else if (1.2 > xys) {
            FL = 0;
            FR = 0;
            RL = 0;
            RR = 0;
            FLCWD = 1;
            RRCWD = 1;
            FRCWD = 1;
            RLCWD = 1;
            FLCCWD = 0;
            RRCCWD = 0;
            FRCCWD = 0;
            RLCCWD = 0;
          }
        }
        if (xys <= 0.8) { //0　～　π/4まで//
          PWMX = (PS3.getAnalogHat(RightHatX) - 127) * 2 - 19;
          PWMY = (RY - 127) * 2 - 19;
          if (PWMX < 1) {
            PWMX = 1;
          }
          if (PWMY < 1) {
            PWMY = 1;
          }
          XY = (PWMX * PWMX) + (PWMY * PWMY);
          slope = sqrt(XY);
          if (slope > 236) {
            slope = 236;
          }
          FL = slope;
          FR = slope;
          RL = slope;
          RR = slope;

          FLCWD = 1;
          RRCWD = 1;
          FRCCWD = 1;
          RLCCWD = 1;
          FLCCWD = 0;
          RRCCWD = 0;
          FRCWD = 0;
          RLCWD = 0;
        } else if (xys >= 1.2) { ///π/4　～　π/2//
          PWMX =  (PS3.getAnalogHat(RightHatX) - 127) * 2 - 19;
          PWMY = (RY - 127) * 2 - 19;
          if (PWMX < 1) {
            PWMX = 1;
          }
          if (PWMY < 1) {
            PWMY = 1;
          }

          XY = (PWMX * PWMX) + (PWMY * PWMY);
          slope = sqrt(XY);

          if (slope > 236) {
            slope = 236;
          }
          FL = slope;
          FR = slope;
          RL = slope;
          RR = slope;
          FLCWD = 1;
          RRCWD = 1;
          FRCWD = 1;
          RLCWD = 1;
          FLCCWD = 0;
          RRCCWD = 0;
          FRCCWD = 0;
          RLCCWD = 0;
        }

      }

      if ( PS3.getAnalogHat(RightHatX) <= 127 && RY >= 128 ) {
        PWMX = (127 - PS3.getAnalogHat(RightHatX)) * 2 - 19;
        PWMY = (RY - 127) * 2 - 19;
        if (PWMX < 1) {
          PWMX = 1;
        }
        if (PWMY < 1) {
          PWMY = 1;
        }
        xys = (double)PWMY / PWMX;
        if (0.8 < xys && 1.2 > xys) {
          if (0.8 < xys ) {
            FL = 0;
            FR = 0;
            RL = 0;
            RR = 0;
            FLCWD = 1;
            RRCWD = 1;
            FRCWD = 1;
            RLCWD = 1;
            FLCCWD = 0;
            RRCCWD = 0;
            FRCCWD = 0;
            RLCCWD = 0;
          } else if (1.2 > xys) {
            FL = 0;
            FR = 0;
            RL = 0;
            RR = 0;
            FLCCWD = 1;
            RRCCWD = 1;
            FRCWD = 1;
            RLCWD = 1;
            RRCWD = 0;
            FLCWD = 0;
            FRCCWD = 0;
            RLCCWD = 0;
          }
        }
        if (xys >= 1.2) { //π/2　～　3π/4まで//

          XY = (PWMX * PWMX) + (PWMY * PWMY);
          slope = sqrt(XY);

          if (slope > 236) {
            slope = 236;
          }

          FL = slope;
          FR = slope;
          RL = slope;
          RR = slope;
          FLCWD = 1;
          RRCWD = 1;
          FRCWD = 1;
          RLCWD = 1;
          FLCCWD = 0;
          RRCCWD = 0;
          FRCCWD = 0;
          RLCCWD = 0;
        } else if (xys < 0.8) { ///3π/4　～　π//

          XY = (PWMX * PWMX) + (PWMY * PWMY);
          slope = sqrt(XY);

          if (slope > 236) {
            slope = 236;
          }
          FLCCWD = 1;
          RRCCWD = 1;
          FRCWD = 1;
          RLCWD = 1;
          FLCWD = 0;
          RRCWD = 0;
          FRCCWD = 0;
          RLCCWD = 0;
        }
      }

      if ( PS3.getAnalogHat(RightHatX) <= 127 && RY <= 127 ) {
        PWMX = (127 - PS3.getAnalogHat(RightHatX)) * 2 - 19;
        PWMY = (127 - RY) * 2 - 19;
        if (PWMX < 1) {
          PWMX = 1;
        }
        if (PWMY < 1) {
          PWMY = 1;
        }
        xys = (double)PWMY / PWMX;

        if (0.8 < xys && 1.2 > xys) {
          if (0.8 < xys ) {
            FL = 0;
            FR = 0;
            RL = 0;
            RR = 0;
            FLCCWD = 1;
            RRCCWD = 1;
            FRCWD = 1;
            RLCWD = 1;
            RRCWD = 0;
            FLCWD = 0;
            FRCCWD = 0;
            RLCCWD = 0;
          } else if (1.2 > xys) {
            FL = 0;
            FR = 0;
            RL = 0;
            RR = 0;
            FLCCWD = 1;
            RRCCWD = 1;
            FRCCWD = 1;
            RLCCWD = 1;
            FLCWD = 0;
            RRCWD = 0;
            FRCWD = 0;
            RLCWD = 0;
          }
        }
        if (xys <= 0.8) { //π　～　5π/4まで//

          XY = (PWMX * PWMX) + (PWMY * PWMY);
          slope = sqrt(XY);

          if (slope > 236) {
            slope = 236;
          }
          FL = slope;
          FR = slope;
          RL = slope;
          RR = slope;
          FLCCWD = 1;
          RRCCWD = 1;
          FRCWD = 1;
          RLCWD = 1;
          RRCWD = 0;
          FLCWD = 0;
          FRCCWD = 0;
          RLCCWD = 0;
        } else if (xys > 1.2) { ///5π/4　～　3π/2//


          XY = (PWMX * PWMX) + (PWMY * PWMY);
          slope = sqrt(XY);

          if (slope > 236) {
            slope = 236;
          }
          FL = slope;
          FR = slope;
          RL = slope;
          RR = slope;
          FLCCWD = 1;
          RRCCWD = 1;
          FRCCWD = 1;
          RLCCWD = 1;
          RRCWD = 0;
          FLCWD = 0;
          FRCWD = 0;
          RLCWD = 0;
        }
      }
      if ( PS3.getAnalogHat(RightHatX) >= 128 && RY <= 127 ) {
        PWMX = (PS3.getAnalogHat(RightHatX) - 127) * 2 - 19;
        PWMY = (127 - RY) * 2 - 19;
        if (PWMX < 1) {
          PWMX = 1;
        }
        if (PWMY < 1) {
          PWMY = 1;
        }
        xys = (double)PWMY / PWMX;
        if (0.8 < xys && 1.2 > xys) {
          if (0.8 < xys ) {
            FL = 0;
            FR = 0;
            RL = 0;
            RR = 0;
            FLCCWD = 1;
            RRCCWD = 1;
            FRCCWD = 1;
            RLCCWD = 1;
            RLCCWD = 1;
            FLCWD = 0;
            RRCWD = 0;
            FRCWD = 0;
            RLCWD = 0;
          } else if (1.2 > xys) {
            FL = 0;
            FR = 0;
            RL = 0;
            RR = 0;
            FLCWD = 1;
            RRCWD = 1;
            FRCCWD = 1;
            RLCCWD = 1;
            FLCCWD = 0;
            RRCCWD = 0;
            FRCWD = 0;
            RLCWD = 0;
          }
        }
        if (xys >= 1.2) { //3π/2　～　7π/4まで//

          XY = (PWMX * PWMX) + (PWMY * PWMY);
          slope = sqrt(XY);

          if (slope > 236) {
            slope = 236;
          }
          FL = slope;
          FR = slope;
          RL = slope;
          RR = slope;
          FLCCWD = 1;
          RRCCWD = 1;
          FRCCWD = 1;
          RLCCWD = 1;
          FLCWD = 0;
          RRCWD = 0;
          FRCWD = 0;
          RLCWD = 0;
        } else if (xys < 0.8) { ///7π/4　～　2π//

          XY = (PWMX * PWMX) + (PWMY * PWMY);
          slope = sqrt(XY);

          if (slope > 236) {
            slope = 236;
          }

          FL = slope;
          FR = slope;
          RL = slope;
          RR = slope;
          FLCWD = 1;
          RRCWD = 1;
          FRCCWD = 1;
          RLCCWD = 1;
          FLCCWD = 0;
          RRCCWD = 0;
          FRCWD = 0;
          RLCWD = 0;
        }
      }

    } else if (PS3.getAnalogHat(LeftHatX) > 137 || PS3.getAnalogHat(LeftHatX) < 117 || LY > 137 || LY < 117) {


      if ( PS3.getAnalogHat(LeftHatX) >= 128 && LY >= 128 ) {
        xys = (double)LY / PS3.getAnalogHat(LeftHatX);
        if (xys <= 1) { //0　～　π/4まで//
          PWMX =  (PS3.getAnalogHat(LeftHatX) - 127) * 2 - 19;
          PWMY = (LY - 127) * 2 - 19;
          if (PWMX < 1) {
            PWMX = 1;
          }
          if (PWMY < 1) {
            PWMY = 1;
          }

          XY = (PWMX * PWMX) + (PWMY * PWMY);
          slope = sqrt(XY);
          speedx = slope;
          if (speedx < 1) {
            speedx = 1;
          } else if (speedx > 236) {
            speedx = 236;
          }

          xpy = PWMY / PWMX;
          xpy = 1.00 - xpy;
          speedy = slope * xpy;
          if (speedy < 1) {
            speedy = 1;
          } else if (speedy > 236) {
            speedy = 236;
          }
          FL = speedx;
          RR = speedx;
          FR = speedy;
          RL = speedy;
          speedx = (int)speedx;
          speedy = (int)speedy;
          FLCWD = 1;
          RRCWD = 1;
          FRCCWD = 1;
          RLCCWD = 1;
          FLCCWD = 0;
          RRCCWD = 0;
          FRCWD = 0;
          RLCWD = 0;
        } else if (xys > 1) { ///π/4　～　π/2//
          PWMX =  (PS3.getAnalogHat(LeftHatX) - 127) * 2 - 19;
          PWMY = (LY - 127) * 2 - 19;
          if (PWMX < 1) {
            PWMX = 1;
          }
          if (PWMY < 1) {
            PWMY = 1;
          }

          XY = (PWMX * PWMX) + (PWMY * PWMY);
          slope = sqrt(XY);
          speedx = slope;
          if (speedx < 1) {
            speedx = 1;
          } else if (speedx > 236) {
            speedx = 236;
          }

          xpy = PWMY / PWMX;
          xpy = xpy - 1.0;
          speedy = slope * xpy;
          if (speedy < 1) {
            speedy = 1;
          } else if (speedy > 236) {
            speedy = 236;
          }

          FL = speedx;
          RR = speedx;
          FR = speedy;
          RL = speedy;

          speedx = (int)speedx;
          speedy = (int)speedy;
          FLCWD = 1;
          RRCWD = 1;
          FRCWD = 1;
          RLCWD = 1;
          FLCCWD = 0;
          RRCCWD = 0;
          FRCCWD = 0;
          RLCCWD = 0;
        }
      }
      if ( PS3.getAnalogHat(LeftHatX) <= 127 && LY >= 128 ) {
        PWMX = (127 - PS3.getAnalogHat(LeftHatX)) * 2 - 19;
        PWMY = (LY - 127) * 2 - 19;
        if (PWMX < 1) {
          PWMX = 1;
        }
        if (PWMY < 1) {
          PWMY = 1;
        }
        xys = (double)PWMY / PWMX;
        if (xys >= 1) { //π/2　～　3π/4まで//

          XY = (PWMX * PWMX) + (PWMY * PWMY);
          slope = sqrt(XY);
          speedx = slope;
          if (speedx < 1) {
            speedx = 1;
          } else if (speedx > 236) {
            speedx = 236;
          }

          xpy = PWMY / PWMX;
          xpy = xpy - 1.0;
          speedy = slope * xpy;
          if (speedy < 1) {
            speedy = 1;
          } else if (speedy > 236) {
            speedy = 236;
          }

          FR = speedx;
          RL = speedx;
          FL = speedy;
          RR = speedy;

          speedx = (int)speedx;
          speedy = (int)speedy;
          FLCWD = 1;
          RRCWD = 1;
          FRCWD = 1;
          RLCWD = 1;
          FLCCWD = 0;
          RRCCWD = 0;
          FRCCWD = 0;
          RLCCWD = 0;
        } else if (xys < 1) { ///3π/2　～　π//

          XY = (PWMX * PWMX) + (PWMY * PWMY);
          slope = sqrt(XY);
          speedx = slope;
          if (speedx < 1) {
            speedx = 1;
          } else if (speedx > 236) {
            speedx = 236;
          }

          xpy = PWMY / PWMX;
          xpy = 1.00 - xpy;
          speedy = slope * xpy;
          if (speedy < 1) {
            speedy = 1;
          } else if (speedy > 236) {
            speedy = 236;
          }

          FR = speedx;
          RL = speedx;
          FL = speedy;
          RR = speedy;

          speedx = (int)speedx;
          speedy = (int)speedy;
          FRCWD = 1;
          RLCWD = 1;
          FLCCWD = 1;
          RRCCWD = 1;
          FRCCWD = 0;
          RLCCWD = 0;
          FLCWD = 0;
          RRCWD = 0;
        }
      }

      if ( PS3.getAnalogHat(LeftHatX) <= 127 && LY <= 127 ) {
        PWMX = (127 - PS3.getAnalogHat(LeftHatX)) * 2 - 19;
        PWMY = (127 - LY) * 2 - 19;
        if (PWMX < 1) {
          PWMX = 1;
        }
        if (PWMY < 1) {
          PWMY = 1;
        }
        xys = (double)PWMY / PWMX;

        if (xys < 1) { //π　～　5π/4まで//

          XY = (PWMX * PWMX) + (PWMY * PWMY);
          slope = sqrt(XY);
          speedx = slope;
          if (speedx < 1) {
            speedx = 1;
          } else if (speedx > 236) {
            speedx = 236;
          }

          xpy = PWMY / PWMX;
          xpy = 1.0 - xpy;
          speedy = slope * xpy;
          if (speedy < 1) {
            speedy = 1;
          } else if (speedy > 236) {
            speedy = 236;
          }

          FL = speedx;
          RR = speedx;
          FR = speedy;
          RL = speedy;

          speedx = (int)speedx;
          speedy = (int)speedy;
          FLCCWD = 1;
          FRCWD = 1;
          RLCWD = 1;
          RRCCWD = 1;
          FLCWD = 0;
          FRCCWD = 0;
          RRCWD = 0;
          RLCCWD = 0;

        } else if (xys >= 1) { //5π/4　～　3π/2//

          XY = (PWMX * PWMX) + (PWMY * PWMY);
          slope = sqrt(XY);
          speedx = slope;
          if (speedx < 1) {
            speedx = 1;
          } else if (speedx > 236) {
            speedx = 236;
          }

          xpy = PWMY / PWMX;
          xpy = xpy - 1.0;
          speedy = slope * xpy;
          if (speedy < 1) {
            speedy = 1;
          } else if (speedy > 236) {
            speedy = 236;
          }

          FL = speedx;
          RR = speedx;
          FR = speedy;
          RL = speedy;


          speedx = (int)speedx;
          speedy = (int)speedy;
          FLCCWD = 1;
          RRCCWD = 1;
          FRCCWD = 1;
          RLCCWD = 1;
          FLCWD = 0;
          RRCWD = 0;
          FRCWD = 0;
          RLCWD = 0;
        }
      }

      if ( PS3.getAnalogHat(LeftHatX) >= 128 && LY <= 127 ) {
        PWMX = (PS3.getAnalogHat(LeftHatX) - 128) * 2 - 19;
        PWMY = (127 - LY) * 2 - 19;
        if (PWMX <= 1) {
          PWMX = 1;
        }
        if (PWMY < 1) {
          PWMY = 1;
        }
        xys = (double)PWMY / PWMX;
        if (xys > 1) { //3π/2　～　7π/4πまで//



          XY = (PWMX * PWMX) + (PWMY * PWMY);
          slope = sqrt(XY);
          speedx = slope;
          if (speedx < 1) {
            speedx = 1;
          } else if (speedx > 236) {
            speedx = 236;
          }

          xpy = PWMY / PWMX;

          xpy = xpy - 1.0;
          speedy = slope * xpy;
          if (speedy < 1) {
            speedy = 1;
          } else if (speedy > 236) {
            speedy = 236;
          }

          FR = speedx;
          RL = speedx;
          FL = speedy;
          RR = speedy;

          speedx = (int)speedx;
          speedy = (int)speedy;

          FRCCWD = 1;
          FLCCWD = 1;
          RLCCWD = 1;
          RRCCWD = 1;
          RRCWD = 0;
          FRCWD = 0;
          FLCWD = 0;
          RLCWD = 0;

        } else if (xys < 1) { //7π/4　～　2π//

          XY = (PWMX * PWMX) + (PWMY * PWMY);
          slope = sqrt(XY);
          speedx = slope;
          if (speedx < 1) {
            speedx = 1;
          } else if (speedx > 236) {
            speedx = 236;
          }

          xpy = PWMY / PWMX;
          xpy = 1.0 - xpy;
          speedy = slope * xpy;
          if (speedy < 1) {
            speedy = 1;
          } else if (speedy > 236) {
            speedy = 236;
          }

          FR = speedx;
          RL = speedx;
          FL = speedy;
          RR = speedy;

          speedx = (int)speedx;
          speedy = (int)speedy;
          FRCCWD = 1;
          RLCCWD = 1;
          FLCWD = 1;
          RRCWD = 1;
          FLCCWD = 0;
          RRCCWD = 0;
          FRCWD = 0;
          RLCWD = 0;
        }
      }
    } else if (PS3.getAnalogButton(L2)) {
      double turnL = (double)PS3.getAnalogButton(L2) - 19;
      if (turnL < 1) {
        turnL = 1;
      }

      FR = turnL;
      RL = turnL;
      FL = turnL;
      RR = turnL;
      FLCCWD = 1;
      FLCWD = 0;
      FRCWD = 1;
      FRCCWD = 0;
      RLCCWD = 1;
      RLCWD = 0;
      RRCWD = 1;
      RRCCWD = 0;
    } else if (PS3.getAnalogButton(R2)) {
      double turnR = (double)PS3.getAnalogButton(R2) - 19;
      if (turnR < 1) {
        turnR = 1;
      }
      FL = turnR;
      FR = turnR;
      RL = turnR;
      RR = turnR;

      FLCWD = 1;
      FLCCWD = 0;
      FRCWD = 0;
      FRCCWD = 1;
      RLCWD = 1;
      RLCCWD = 0;
      RRCWD = 0;
      RRCCWD = 1;
    } else {
      digitalWrite(FLCW,LOW);
      digitalWrite(FLCCW,LOW);
      analogWrite(FLPWM,0);
      digitalWrite(FRCW,LOW);
      digitalWrite(FRCCW,LOW);
      analogWrite(FRPWM,0);
      digitalWrite(RLCW,LOW);
      digitalWrite(RLCCW,LOW);
      analogWrite(RLPWM,0);
      digitalWrite(RRCW,LOW);
      digitalWrite(RRCCW,LOW);
      analogWrite(RRPWM,0);
      FL = 0;
      FR = 0;
      RL = 0;
      RR = 0;
      FLB = 0;
      FRB = 0;
      RLB = 0;
      RRB = 0;
    }


    // Analog button values can be read from almost all buttons//


    if (PS3.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS3.disconnect();
      digitalWrite(FLCW,LOW);
      digitalWrite(FLCCW,LOW);
      analogWrite(FLPWM,0);
      digitalWrite(FRCW,LOW);
      digitalWrite(FRCCW,LOW);
      analogWrite(FRPWM,0);
      digitalWrite(RLCW,LOW);
      digitalWrite(RLCCW,LOW);
      analogWrite(RLPWM,0);
      digitalWrite(RRCW,LOW);
      digitalWrite(RRCCW,LOW);
      analogWrite(RRPWM,0);
      Timer1.stop();

    }
    else {

      if (PS3.getButtonClick(L1)) {
        digitalWrite(M1CW, LOW);
        digitalWrite(M2CW, LOW);
        digitalWrite(M3CW, LOW);
        analogWrite(M1PWM, 0);
        analogWrite(M2PWM, 0);
        analogWrite(M3PWM, 0);
        digitalWrite(AIR, LOW);
        PS3.setLedOff();
      }
      if (PS3.getButtonClick(L3))
        Serial.print(F("\r\nL3"));
      if (PS3.getButtonClick(R1)) {
        PS3.setLedOn(LED1);
        MR1 = MRTV;
        MR2 = MRTV;
        MR3 = MRTV;
        for (i = 1; i < MRTV; i++) {
          digitalWrite(M1CW, HIGH);
          digitalWrite(M2CW, HIGH);
          digitalWrite(M3CW, HIGH);
          analogWrite(M1PWM, i);
          analogWrite(M2PWM, i);
          analogWrite(M3PWM, i);
          delay(4);
        }
        PS3.setLedOn(LED2);
        attachInterrupt(EPIN1, ENC1, RISING);
        attachInterrupt(EPIN2, ENC2, RISING);
        attachInterrupt(EPIN3, ENC3, RISING);
        while (END == 0) {
          FlexiTimer2::start();
        }
        PS3.setLedOn(LED3);
        digitalWrite(AIR, HIGH);
        delay(1000);
        PS3.setLedOn(LED4);
        FlexiTimer2::stop();
      }
      if (PS3.getButtonClick(R3))
        Serial.print(F("\r\nR3"));

      if (PS3.getButtonClick(SELECT)) {
        Serial.print(F("\r\nSelect - "));
        PS3.printStatusString();
      }
      if (PS3.getButtonClick(START)) {
        printAngle = !printAngle;
      }
    }
  } else {
    FL = 0;
    FR = 0;
    RL = 0;
    RR = 0;
    FLB = 0;
    FRB = 0;
    RLB = 0;
    RRB = 0;
  }

}

void ENC1() {
  counter1++;
}

void ENC2() {
  counter2++;
}

void ENC3() {
  counter3++;
}
