#define ENB 5
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define ENA 6

void setup() {
  Serial.begin(9600);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(13, INPUT);
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
}

void pullUp() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);  //go forward
}

void lower() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stop() {
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}
void pour() {
  pullUp();
  delay(1000);
  lower();
  delay(750);
  stop();
  delay(1000);
}
void loop() {
  Serial.print(digitalRead(13));
  if (digitalRead(13) == 1) {
    pour();
  }
}
