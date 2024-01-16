// Include the LiquidCrystal_I2C library for the LCD display
#include <LiquidCrystal_I2C.h>

// Define pins for the ultrasonic sensor
const int trigPin = 9;
const int echoPin = 10;

// Define pins for the LEDs
const int led1 = 4;
const int led2 = 5;
const int led3 = 6;

// Define pin for the buzzer
const int buzzer = 3;

// Variables to store the duration and distance
long duration;
int distance;

// Initialize the LCD display with I2C address 0x27 and 16 columns and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Start serial communication at 9600 baud rate
  Serial.begin(9600);

  // Set the ultrasonic sensor pins as output and input respectively
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set the buzzer pin as output
  pinMode(buzzer, OUTPUT);

  // Initialize the LCD display
  lcd.init();
  // Turn on the backlight of the LCD
  lcd.backlight();

  // Set the LED pins as output
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() {
  // Trigger the ultrasonic sensor to send a pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the duration of the echo pulse
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance based on the duration of the echo
  distance = duration * 0.034 / 2;

  // If the distance is less than or equal to 10
  if (distance <= 10) {
    Serial.println("green");
    tone(buzzer, 1000); // Play a tone at 1000 Hz
    digitalWrite(led1, HIGH); // Turn on LED 1
    digitalWrite(led2, LOW); // Turn off LED 2
    digitalWrite(led3, LOW); // Turn off LED 3
  }

  // If the distance is between 10 and 25
  if (distance > 10 && distance < 25) {
    Serial.println("blue");
    tone(buzzer, 400); // Play a tone at 400 Hz
    digitalWrite(led1, LOW); // Turn off LED 1
    digitalWrite(led2, HIGH); // Turn on LED 2
    digitalWrite(led3, LOW); // Turn off LED 3
  }

  // If the distance is greater than or equal to 25
  if (distance >= 25) {
    Serial.println("red");
    noTone(buzzer); // Stop playing any tone
    digitalWrite(led1, LOW); // Turn off LED 1
    digitalWrite(led2, LOW); // Turn off LED 2
    digitalWrite(led3, HIGH); // Turn on LED 3
  }

  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  // Clear the LCD display
  lcd.clear();

  // Set the cursor to the first column, first row
  lcd.setCursor(0,0);
  lcd.print("Distance:");

  // Set the cursor to the first column, second row
  lcd.setCursor(0,1);
  lcd.print((int) distance); // Print the distance on the LCD

// Wait for 500 milliseconds before the next loop iteration
delay(500);
}
