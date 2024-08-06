// C++ code
//
#include <LiquidCrystal.h> //Library 

// Initialize the LCD with the appropriate pins in the Arduino board
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // pins arranged according to the wiring

char bluetooth;
const int buzzerPin = 10;


void setup()
{
  
  lcd.begin(16, 2);  // Initialize the LCD: specify the columns and rows
  lcd.print("Powering On!"); // Display a message
  delay(2000); // Wait for 2 seconds
  lcd.clear(); // Clear the screen
  pinMode(8, OUTPUT);
  pinMode(9, INPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
 
  Serial.begin(9600);
}

void loop()
{
  //Ultrasonic Distance Sensor Trigger
  digitalWrite(8, LOW);
  digitalWrite(8, HIGH);  
  digitalWrite(8, LOW);
  
  int duration = pulseIn(9, HIGH);
  int distance = duration*0.034/2;
  
  Serial.print("The Distance is: ");
  Serial.println(distance);
 
  
   if(distance > 100 && bluetooth != 'x' )
  {
   lcd.setCursor(1,0);
   lcd.print("PARKING EMPTY");
   lcd.setCursor(4,1);
   digitalWrite(12, HIGH);
   digitalWrite(11, LOW);
   }
  
 if(distance < 100 && bluetooth != 'x' )
  {
   digitalWrite(12, LOW);
   digitalWrite(11, HIGH);
   tone(buzzerPin, 1000, 500);
   delay(1000);
   lcd.setCursor(1,0);
   lcd.print("PARKING IS");
   lcd.setCursor(4,1);
   lcd.print("OCCUPIED   ");

  }
  
  //Object removal is confirmed through bluetooth
   if(Serial.available()>0 )
  {
  
    bluetooth = Serial.read();
     if(bluetooth=='x')
     {
       lcd.setCursor(1,0);
       lcd.print("CAR SECURE");
       lcd.setCursor(4,1);
       digitalWrite(11, HIGH);
       //delay(1);
       digitalWrite(12, LOW);
       noTone(10); 
       delay(1000);  
     }


  } 
}
