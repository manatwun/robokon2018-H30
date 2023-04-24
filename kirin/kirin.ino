#include <PS3BT.h>
#include <usbhub.h>
#include <TimerOne.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.

volatile int LL = 0;
volatile int RR = 0;
volatile int LLB = 0;
volatile int RRB = 0;
volatile int SLSC = 0, SMSC = 0, SRSC = 0, SLLC = 0, SMLC = 0, SRLC = 0;


volatile int LLCWD;
volatile int RRCWD;
volatile int LLCCWD;
volatile int RRCCWD;

volatile int LLCWDB;
volatile int RRCWDB;
volatile int LLCCWDB;
volatile int RRCCWDB;

#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

//If you want to change {OUTPUT pin number}, you can change OUTPUT pin number under here.//

#define LLCW 46 //left tire pin//
#define LLPWM 7
#define LLCCW 48

#define RRCW 30 //right tire pin//
#define RRPWM 3
#define RRCCW 32

#define SLL 22
#define SLS 38
#define SML 5
#define SMS 40
#define SRL 42
#define SRS 44

//If you want to change {max duty cycle}, you can change max duty cycle under here.//

#define MAXPWM 220


USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so

/* You can create the instance of the class in two ways */
PS3BT PS3(&Btd); // This will just create the instance
//PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained RRom the dongle when running the sketch

bool printTemperature, printAngle;

void PWM() {
  if (LL < LLB) {
    LLB = LLB - 1;
    if (LLCWD == 1) {
      digitalWrite(LLCW, HIGH);
      digitalWrite(LLCCW, LOW);
    } else if (LLCWD == 0) {
      digitalWrite(LLCCW, HIGH);
      digitalWrite(LLCW, LOW);
    }
    if (LLCWDB != LLCWD) {
      LLB = 0;
      LL = 0;
    }
    if (LLB > MAXPWM) {
      LLB = MAXPWM;
    }
    LLCWDB = LLCWD;
    analogWrite(LLPWM, LLB);
  } else if (LL > LLB) {
    LLB = LLB + 1;
    if (LLCWD == 1) {
      digitalWrite(LLCW, HIGH);
      digitalWrite(LLCCW, LOW);
    } else if (LLCWD == 0) {
      digitalWrite(LLCCW, HIGH);
      digitalWrite(LLCW, LOW);
    }
    if (LLCWDB != LLCWD) {
      LLB = 0;
      LL = 0;
    }
    if (LLB > MAXPWM) {
      LLB = MAXPWM;
    }
    LLCWDB = LLCWD;
    if (LLB > MAXPWM) {
      LLB = MAXPWM;
    }
    analogWrite(LLPWM, LLB);
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
    if (RRB > MAXPWM) {
      RRB = MAXPWM;
    }
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
    if (RRB > MAXPWM) {
      LLB = MAXPWM;
    }
    RRCWDB = RRCWD;
    if (RRB > MAXPWM) {
      RRB = MAXPWM;
    }
    analogWrite(RRPWM, RRB);
  }
}

void setup() {
  Serial.begin(115200);
  TCCR1B = (TCCR1B & 0b11111000) | 0x02;
  TCCR2B = (TCCR2B & 0b11111000) | 0x02;
  TCCR3B = (TCCR3B & 0b11111000) | 0x02;
  TCCR4B = (TCCR4B & 0b11111000) | 0x02;
  TCCR5B = (TCCR5B & 0b11111000) | 0x02;

  pinMode(LLCW, OUTPUT);
  pinMode(LLCCW, OUTPUT);
  pinMode(RRCW, OUTPUT);
  pinMode(RRCCW, OUTPUT);
  pinMode(SLS, OUTPUT);
  pinMode(SLL, OUTPUT);
  pinMode(SMS, OUTPUT);
  pinMode(SML, OUTPUT);
  pinMode(SRS, OUTPUT);
  pinMode(SRL, OUTPUT);

  for (int c = 0; c < 20; c++) {

    digitalWrite(LLCCW, LOW);
    digitalWrite(RRCCW, LOW);
    digitalWrite(LLCW, HIGH);
    digitalWrite(RRCW, HIGH);

    delay(50);

    digitalWrite(LLCW, LOW);
    digitalWrite(RRCW, LOW);
    analogWrite(LLPWM, MAXPWM);
    analogWrite(RRPWM, MAXPWM);

    delay(50);

    analogWrite(LLPWM, 0);
    analogWrite(RRPWM, 0);
    digitalWrite(LLCCW, HIGH);
    digitalWrite(RRCCW, HIGH);
    delay(50);
  }
  digitalWrite(LLCCW, LOW);
  digitalWrite(RRCCW, LOW);

  delay(500);

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
  double xys, PWMX, PWMY, slope ;
  double turnL;
  double turnR;

  Usb.Task();
  double RY = 255 - (PS3.getAnalogHat(RightHatY));

  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    Timer1.resume();

    if  (PS3.getAnalogHat(RightHatX) > 137 || PS3.getAnalogHat(RightHatX) < 117 || RY > 137 || RY < 117) {

      if ( PS3.getAnalogHat(RightHatX) >= 128 && RY >= 128 ) {
        xys = (double)RY / PS3.getAnalogHat(RightHatX);
        if (xys <= 0.8) { //0 to pai/4//
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
          if (slope > MAXPWM) {
            slope = MAXPWM;
          }
          LL = slope;
          RR = slope;
          RRCWD = 0;
          LLCWD = 0;
          RRCCWD = 1;
          LLCCWD = 1;
        } else if (xys >= 1.2) { //pai/4 to pai/2//
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

          if (slope > MAXPWM) {
            slope = MAXPWM;
          }
          LL = slope;
          RR = slope;
          RRCWD = 0;
          LLCWD = 0;
          RRCCWD = 1;
          LLCCWD = 1;
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
        if (xys >= 1.2) { //pai/2 to 3pai/4//

          XY = (PWMX * PWMX) + (PWMY * PWMY);
          slope = sqrt(XY);

          if (slope > MAXPWM) {
            slope = MAXPWM;
          }

          LL = slope;
          RR = slope;
          RRCWD = 0;
          LLCWD = 0;
          RRCCWD = 1;
          LLCCWD = 1;
        } else if (xys < 0.8) { //3pai/4 to pai//

          XY = (PWMX * PWMX) + (PWMY * PWMY);
          slope = sqrt(XY);
          if (slope > MAXPWM) {
            slope = MAXPWM;
          }
          LL = slope;
          RR = slope;
          RRCWD = 0;
          LLCWD = 0;
          RRCCWD = 1;
          LLCCWD = 1;
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
        if (xys <= 0.8) { //pai to 5pai/4//

          XY = (PWMX * PWMX) + (PWMY * PWMY);
          slope = sqrt(XY);

          if (slope > MAXPWM) {
            slope = MAXPWM;
          }
          LL = slope;
          RR = slope;
          LLCWD = 1;
          RRCWD = 1;
          LLCCWD = 0;
          RRCCWD = 0;
        } else if (xys > 1.2) { //5pai/4 to 3pai/2//
          XY = (PWMX * PWMX) + (PWMY * PWMY);
          slope = sqrt(XY);

          if (slope > MAXPWM) {
            slope = MAXPWM;
          }
          LL = slope;
          RR = slope;
          RRCWD = 0;
          LLCWD = 0;
          RRCCWD = 1;
          LLCCWD = 1;
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
        if (xys >= 1.2) { //3pai/2 to 7pai/4//
          XY = (PWMX * PWMX) + (PWMY * PWMY);
          slope = sqrt(XY);

          if (slope > MAXPWM) {
            slope = MAXPWM;
          }
          LL = slope;
          RR = slope;
          LLCCWD = 0;
          RRCWD = 1;
          LLCWD = 1;
          RRCCWD = 0;
        } else if (xys < 0.8) { //7pai/4 to 2pai//
          XY = (PWMX * PWMX) + (PWMY * PWMY);
          slope = sqrt(XY);

          if (slope > MAXPWM) {
            slope = MAXPWM;
          }
          LL = slope;
          RR = slope;
          RRCWD = 1;
          LLCWD = 1;
          RRCCWD = 0;
          LLCCWD = 0;
        }
      }


    } else if (PS3.getAnalogButton(L2) && PS3.getAnalogButton(R2)) {
      if (PS3.getAnalogButton(L2) > PS3.getAnalogButton(R2)) {
        double turnL = (double)PS3.getAnalogButton(L2) - 19;
        if (turnL < 1) {
          turnL = 1;
        }
        turnL = turnL - turnR;
        if (turnL < 1) {
          turnL = 1;
        }
        if (turnL > MAXPWM) {
          turnL = MAXPWM;
        }
        RR = turnL;
        LL = turnL;
        LLCCWD = 1;
        LLCWD = 0;
        RRCWD = 1;
        RRCCWD = 0;
      } else if (PS3.getAnalogButton(L2) < PS3.getAnalogButton(R2)) {
        double turnR = (double)PS3.getAnalogButton(R2) - 19;
        if (turnR < 1) {
          turnR = 1;
        }
        turnR = turnR - turnL;
        if (turnR < 1) {
          turnR = 1;
        }
        if (turnR > MAXPWM) {
          turnR = MAXPWM;
        }
        LL = turnR;
        RR = turnR;
        RRCWD = 0;
        LLCWD = 1;
        RRCCWD = 1;
        LLCCWD = 0;
      } else {
        LL = 0;
        RR = 0;
        LLB = 0;
        RRB = 0;
        RRCWD = 0;
        LLCWD = 0;
        RRCCWD = 0;
        LLCCWD = 0;
      }
    } else if (PS3.getAnalogButton(L2)) {
      double turnL = (double)PS3.getAnalogButton(L2) - 19;
      if (turnL < 1) {
        turnL = 1;
      }
      RR = turnL;
      LL = turnL;
      LLCCWD = 1;
      LLCWD = 0;
      RRCWD = 1;
      RRCCWD = 0;
    } else if (PS3.getAnalogButton(R2)) {
      double turnR = (double)PS3.getAnalogButton(R2) - 19;
      if (turnR < 1) {
        turnR = 1;
      }
      LL = turnR;
      RR = turnR;
      LLCWD = 1;
      LLCCWD = 0;
      RRCWD = 0;
      RRCCWD = 1;
    } else if (PS3.getButtonClick(SELECT)) {
      if (SMSC == 0) {
        digitalWrite(SMS, HIGH);
        SMSC = 1;
      } else if (SMSC == 1) {
        digitalWrite(SMS, LOW);
        SMSC = 0;
      }
    } else if (PS3.getButtonClick(LEFT)) {
      if (SLLC == 0) {
        digitalWrite(SLL, HIGH);
        SLLC = 1;
      } else if (SLLC == 1) {
        digitalWrite(SLL, LOW);
        SLLC = 0;
      }
    } else if (PS3.getButtonClick(UP)) {
      
    }else if (PS3.getButtonClick(RIGHT)) {
      if (SRLC == 0) {
        digitalWrite(SRL, HIGH);
        SRLC = 1;
      } else if (SRLC == 1) {
        digitalWrite(SRL, LOW);
        SRLC = 0;
      }
    } else if (PS3.getButtonClick(SQUARE)) {
      if (SMLC == 0) {
        digitalWrite(SML, HIGH);
        SMLC = 1;
      } else if (SMLC == 1) {
        digitalWrite(SML, LOW);
        SMLC = 0;
      }
    } else if (PS3.getButtonClick(TRIANGLE)) {
      if (SLSC == 0) {
        digitalWrite(SLS, HIGH);
        SLSC = 1;
      } else if (SLSC == 1) {
        digitalWrite(SLS, LOW);
        SLSC = 0;
      }
    } else if (PS3.getButtonClick(CIRCLE)) {
      if (SRSC == 0) {
        digitalWrite(SRS, HIGH);
        SRSC = 1;
      } else if (SRSC == 1) {
        digitalWrite(SRS, LOW);
        SRSC = 0;
      }
    } else {
      digitalWrite(LLCW, LOW);
      digitalWrite(LLCCW, LOW);
      analogWrite(LLPWM, 0);
      digitalWrite(RRCW, LOW);
      digitalWrite(RRCCW, LOW);
      analogWrite(RRPWM, 0);
      LL = 0;
      RR = 0;
      LLB = 0;
      RRB = 0;
    }
    if (PS3.getButtonClick(PS)) {
      PS3.disconnect();
      digitalWrite(LLCW, LOW);
      digitalWrite(LLCCW, LOW);
      analogWrite(LLPWM, 0);
      digitalWrite(RRCW, LOW);
      digitalWrite(RRCCW, LOW);
      analogWrite(RRPWM, 0);
      Timer1.stop();
    }
  } else {
    LL = 0;
    RR = 0;
    LLB = 0;
    RRB = 0;
  }
}
