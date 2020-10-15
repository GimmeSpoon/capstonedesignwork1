int trig = 14;
int echo = 12;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  long duration, distance;
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = ((float)(340*duration)/1000)/2;
  Serial.print("Duration:");
  Serial.print(duration);
  Serial.print("\nDistance:");
  Serial.print(distance);
  Serial.println("mm\n");
  delay(500);
}
