#define trigPin 9
#define echoPin 10
#define ledAutoGreen 3
#define ledAutoRed 4
#define ledWalkGreen 5
#define ledWalkRed 6
#define buzzer 7

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledAutoGreen, OUTPUT);
  pinMode(ledAutoRed, OUTPUT);
  pinMode(ledWalkGreen, OUTPUT);
  pinMode(ledWalkRed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  if (distance < 100) {
    // Peatón detectado
    digitalWrite(ledAutoGreen, LOW);
    digitalWrite(ledAutoRed, HIGH);
    digitalWrite(ledWalkGreen, HIGH);
    digitalWrite(ledWalkRed, LOW);
    digitalWrite(buzzer, HIGH);
    delay(10000); // tiempo para cruce seguro

    // Restablecer
    digitalWrite(buzzer, LOW);
    digitalWrite(ledAutoGreen, HIGH);
    digitalWrite(ledAutoRed, LOW);
    digitalWrite(ledWalkGreen, LOW);
    digitalWrite(ledWalkRed, HIGH);
  } else {
    // Tráfico normal
    digitalWrite(ledAutoGreen, HIGH);
    digitalWrite(ledAutoRed, LOW);
    digitalWrite(ledWalkGreen, LOW);
    digitalWrite(ledWalkRed, HIGH);
    digitalWrite(buzzer, LOW);
  }
  delay(500);
}
