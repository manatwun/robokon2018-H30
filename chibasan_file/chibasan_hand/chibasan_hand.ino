const int chattering_WT = 200;
const int double_Tap_WT = 2500; 
const int mic_Active1 = 5;
const int mic_Active2 = 5;
const int PWM_val1 =80;
const int PWM_val2 = 90;
const int IN_A1 = 2;
const int IN_APWM = 3;
const int IN_A2 = 4;
const int IN_B1 = 5;
const int IN_BPWM = 6;
const int IN_B2 = 7;
char LED_state = 0;
unsigned int counter = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
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

void loop() {
  if(analogRead(A0) <= mic_Active1){

    digitalWrite(LED_BUILTIN, HIGH);

    delay(chattering_WT);
    for(int i=0 ; i<=double_Tap_WT ; i++){

      if(analogRead(A0) <= mic_Active2){
        break;
      }
      else{
        LED_state = 0;
        counter = 1500;
      }
    }
  digitalWrite(LED_BUILTIN, LED_state);
  digitalWrite(IN_APWM, LOW);
  digitalWrite(IN_BPWM, LOW);
  digitalWrite(IN_A2, LED_state == 1 ? HIGH : LOW);
  digitalWrite(IN_A1, LED_state == 1 ? LOW : HIGH);
  digitalWrite(IN_B2, LED_state == 1 ? LOW : LOW);
  digitalWrite(IN_A1, LED_state == 1 ? HIGH : HIGH);
  digitalWrite(IN_APWM, PWM_val1);
  digitalWrite(IN_BPWM, PWM_val2);
  delay(10000);//タイヤ駆動時間//
  counter = 1500;
}
if (counter < 0){
  digitalWrite(IN_APWM, LOW);
  digitalWrite(IN_BPWM, LOW);
}
else if(counter < 1){
   digitalWrite(IN_APWM, LOW);
   digitalWrite(IN_BPWM, LOW);
   delay(500);
    counter --;
  }
  else{
    counter --;
  }
}
