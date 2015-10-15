int red=8;
int yellow=9;
int green=10;
int buzzer = 11;

void setup(){
  pinMode(red,OUTPUT);
  pinMode(yellow,OUTPUT);
  pinMode(green,OUTPUT);
  }

void loop(){
  digitalWrite(red,HIGH);
  buzTone(440, 1000, 8000);
  digitalWrite(red,LOW);
  digitalWrite(green,HIGH);
  buzTone(500, 250, 8000);
  digitalWrite(green,LOW);
  digitalWrite(red,LOW);
  digitalWrite(yellow,HIGH);
  //buzTone(440, 1000, 3000);
  transition(500, 440, 250, 1000, 3000);
  digitalWrite(yellow,LOW);
}

void buzTone(int freq, int d, int dur) {
    unsigned long startTime, curTime = 0;
    
    while (curTime <= dur) {
      startTime = millis();
      tone(buzzer, freq);
      delay(d);
      noTone(buzzer);
      delay(d);
      curTime = curTime + millis() - startTime;
    }
}
    
void transition (int startF, int endF, int startD, int endD, int dur) {
   unsigned long begTime, curTime = 0;
   float curF = startF, d = startD;
    
    while (curTime <= dur) {
      begTime = millis();
      tone(buzzer, curF);
      delay(d);
      noTone(buzzer);
      delay(d);
      d += ((endD - startD)/((1.0)*dur))*(millis()-begTime);
      curF -= (startF-endF)/((1.0)*dur)*(millis()-begTime);
      curTime += millis() - begTime;
    }
}
  
  
