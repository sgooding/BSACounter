// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
volatile int counter = 0;
volatile bool update_display = false;
const byte interruptPin = 2;
const int buttonPin = A4;
int buttonState = LOW;

const int ledPin = A0;
int ledState = LOW;


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0, 1);

  lcd.print("space derby");
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin,HIGH);

  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,ledState);

  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), count, RISING);
  Serial.begin(38400);
}

void count()
{
  update_display = true;  
}

float global_counter = 0;
int rotations = 0;
int last_update = 0;

void loop() {

  if(update_display)
  {  
    // print the number of seconds since reset:
    if(global_counter >= 1.0)
    {

      rotations++;
      global_counter = 0.0;
      if((millis() - last_update) > 60)
      {
         
      lcd.setCursor(0, 0);
      lcd.print(rotations,DEC);
      last_update = millis();
      }

    }
    //Serial.println("click");
    update_display = false;
    global_counter += 1.0/19.0;
  }
  
   int reading = digitalRead(buttonPin);
   
   bool new_state = (reading != buttonState);
   //Serial.println(reading);
   if(new_state and reading == LOW)
   {
    global_counter = 0;
    rotations = 0;

    
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("space derby");
    lcd.setCursor(0, 0);
    lcd.print(0,DEC);
    Serial.println("LOW");
    buttonState = reading;
    
   }
   else if( new_state and reading == HIGH)
   {
    Serial.println("HIGH");
    buttonState = reading;
   }

   if( global_counter >= 0.0 and global_counter < 0.5 and ledState )
   {
    ledState = LOW;
    digitalWrite(ledPin, ledState);
    //Serial.print(global_counter);
    //Serial.print( " : " );
    //Serial.println("LED ON");
    
   } 
   if( global_counter >= 0.5 and not ledState)
   {
    ledState = HIGH;
    digitalWrite(ledPin, ledState);
    //Serial.print(global_counter);
    //Serial.print( " : " );
    //Serial.println("LED OFF");
   }
   
    
}

