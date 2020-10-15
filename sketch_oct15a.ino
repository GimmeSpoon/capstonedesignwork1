int red=23;
int blue=21;
int yellow=13;
int Trig = 33;
int Echo = 34;
void setup() {
  Serial.begin(115200);
  pinMode(yellow, OUTPUT);
  pinMode(blue, OUTPUT);
  ledcAttachPin(red, 0);
  ledcSetup(0,5000,10);
  pinMode(Trig,OUTPUT);
  pinMode(Echo, INPUT);
}

static bool yOn = false;
static bool moving = false;
static unsigned long elapsedTime = 0;
static unsigned long interval = 0;
static unsigned long last_position = 200;

void loop() {
  static unsigned long duration, distance;
  static unsigned long Time;
  
  Time = millis() - elapsedTime;
  elapsedTime += Time;
  
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  duration = pulseIn(Echo, HIGH);
  distance = 17*duration/1000;

  printf("Distance : %d\n", distance);
  
  if(distance>200){
    last_position = 200;
    ledcWrite(0,0);
    digitalWrite(blue,LOW);
    if( yOn ){
      digitalWrite(yellow, HIGH);
      if( interval < 300 ){
        interval += Time;
      }
      else{
        interval = 0;
        yOn = false;
      }
    }
    else{
      digitalWrite(yellow, LOW);
      if( interval < 700 ){
        interval += Time;
      }
      else{
        interval = 0;
        yOn = true;
      }
    }
  }
  else{
    digitalWrite(yellow, LOW);
    if(moving){
      digitalWrite(blue, HIGH);
      if(interval < 1000){
        interval += Time;
      }
      else{
        moving = false;
        interval = 0;
      }
    }
    else{
      digitalWrite(blue,LOW);
      if(last_position > distance && last_position - distance > 10 ){
        interval = 0; moving = true; last_position = distance;
      }
      else if( distance > last_position && distance-last_position > 10 ){
        interval = 0; moving = true; last_position = distance;
      }
    }
    ledcWrite(0, 1024 - min(1024, (int)(distance*5)));
  }
}
