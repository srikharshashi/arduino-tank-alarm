#include <LiquidCrystal.h>

int rs = 8;
int enable = 9;
int d4 = 4;
int d5 = 5;
int d6 = 6;
int d7 = 7;
int echoPin = 10;
int trigPin = 11;
long duration;
int distanceCm, distanceInch;
float depth = 30.0;
int buzzer1 = 12;
int buzzer2 = 3;
LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(buzzer1, OUTPUT);
  pinMode(buzzer2, OUTPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2;
  distanceCm = distanceCm +2;
  distanceInch = duration * 0.0133 / 2;
  float full = depth - distanceCm;
  float dist = (float)distanceCm;
  float percentfull = (full / depth) * 100.0;
  Serial.print("Distance: "); // Prints string "Distance" on the LCD
  Serial.println(distanceCm);
  Serial.print("Percent full : ");
  Serial.println(percentfull);
  if (percentfull > 70.0 && percentfull < 80)
  {
    digitalWrite(buzzer1, HIGH);
    delay(1000);
    digitalWrite(buzzer1, LOW);
    delay(500);

  }
  else if (percentfull > 80)
  {
    digitalWrite(buzzer1, HIGH);
    digitalWrite(buzzer2, HIGH);
    delay(1000);
    digitalWrite(buzzer1, LOW);
    digitalWrite(buzzer2, LOW);
    delay(500);

  }
  lcd.setCursor(0, 0); // Sets the location at which subsequent text written to the LCD will be displayed
  //Print the percentage of amount of tank full
  lcd.print("Percentage Full: "); // Prints string "Distance" on the LCD
  //  lcd.print(percentfull);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Depth: "); // Prints string "Distance" on the LCD
  lcd.print(distanceCm);
  lcd.print(" cm");
  delay(100);
  delay(10);
}
