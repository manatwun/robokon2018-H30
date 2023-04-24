/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

const int chattering_WT = 200;
const int double_Tap_WT = 2500;
const int mic_Active1 = 250;
//
const int mic_Active2 = 250;
//
const int PWM_val1 = 80;
const int PWM_val2 = 90;
const int IN_A1 = 2;
const int IN_APWM = 3;
const int IN_A2 = 4;
const int IN_B1 = 5;
const int IN_BPWM = 6;
const int IN_B2 = 7;
char LED_state = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  int counter = 0;
  
  pinMode(IN_A1, OUTPUT);
  pinMode(IN_APWM, OUTPUT);
  pinMode(IN_A2, OUTPUT);
  pinMode(IN_B1, OUTPUT);
  pinMode(IN_BPWM, OUTPUT);
  pinMode(IN_B2, OUTPUT);
  digitalWrite(IN_A1, LOW);
  digitalWrite(IN_APWM, LOW);
  digitalWrite(IN_A2, LOW);
  digitalWrite(IN_B1, LOW);
  digitalWrite(IN_BPWM, LOW);
  digitalWrite(IN_B2, LOW);
  
}

// the loop function runs over and over again forever
void loop() {
  if(analogRead(A0) <= mic_Active1){
    
     digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  
     delay(chattering_WT);                       // wait for a second
     for(int i=0 ; i<=double_Tap_WT ; i++){

     if(analogRead(A0) <= mic_Active2){
      LED_state = 1; 
      counter = 1500;
      break;
     }

     else{
      LED_state = 0;
      counter = 500;
     }
  }
  digitalWrite(LED_BUILTIN,LED_state);
  digitalWrite(IN_APMW,LOW);
  digitalWrite(IN_BPMW,LOW);
  digitalWrite(IN_A2, LED_state == 1 ? HIGH : LOW);
  digitalWrite(IN_A1, LED_state == 1 ? LOW : HIGH);
  digitalWrite(IN_B2, LED_state == 1 ? LOW : LOW);
  digitalWrite(IN_B1, LED_state == 1 ? HIGH : HIGH);
  analogWrite(IN_APWM,PWM_val1);
  analogWrite(IN_APWM,PWM_val2);
  delay(500);
  counter = 1500;
}

if (counter < 0){
  digitalWrite(IN_APWM,LOW);
  digitalWrite(IN_BPWM,LOW);
}
else if(counter < 1){
  digitalWrite(IN_APEM,LOW)
  digitalWrite(IN_BPEM,LOW)
  delay(500);
  counter --;
}
else{
  counter --;
}
}
  
  
  



  
  
  
     }
      counter
     }
}
