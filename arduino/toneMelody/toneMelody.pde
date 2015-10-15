int red=8;
int yellow=9;
int green=10; 
int road[] = {3,4,5,6,7};
int buzzer = 11;
int freqred = 450;
int freqgre = 500;


void setup(){
  pinMode(red,OUTPUT);
  pinMode(yellow,OUTPUT);
  pinMode(green,OUTPUT);
  
  }

void loop(){
  carpass(400, 500);
  /*
  digitalWrite(red,HIGH);
  buzTone(freqred, 1000, 8000);
  digitalWrite(red,LOW);
  digitalWrite(green,HIGH);
  buzTone(freqgre, 250, 8000);
  digitalWrite(green,LOW);
  
  digitalWrite(yellow,HIGH);
  //buzTone(440, 1000, 3000);
  transition(freqgre, freqred, 250, 1000, 3000);
  digitalWrite(yellow,LOW);
  */
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
  
void carpass(int startF, int endF) {
      int dur = 2000, curTime = 0, startTime, curF = startF;
      
      while(curTime <= dur) {
        startTime = millis();
        tone(buzzer, curF);
        curF += 1;//(endF - startF)/(dur)*(millis() - startTime);
        curTime += millis() - startTime;
      }
}
