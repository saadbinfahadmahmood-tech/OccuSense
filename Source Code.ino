#include <TM1637Display.h> 

#define CLK 21 
#define DIO 22 
TM1637Display display(CLK, DIO); 

#define IR1 34 
#define IR2 35 
#define RED_LED 26 
#define GREEN_LED 27 

const int ROOM_LIMIT = 5; 
int studentCount = 0; 
int state = 0; 

unsigned long timeoutStart = 0; 
const unsigned long TIMEOUT = 2000; 

void updateDashboard(); // Function prototype

void setup() 
{ 
  Serial.begin(115200); 
  pinMode(IR1, INPUT); 
  pinMode(IR2, INPUT); 
  pinMode(RED_LED, OUTPUT); 
  pinMode(GREEN_LED, OUTPUT); 

  display.setBrightness(7); 
  display.showNumberDec(0, true); 
  updateDashboard();
} 

void loop() 
{ 
  bool sensor1 = digitalRead(IR1); 
  bool sensor2 = digitalRead(IR2); 

  switch(state) 
  { 
    case 0: 
      if(sensor1 == LOW) 
      { 
        state = 1; 
        timeoutStart = millis(); 
      } 
      else if(sensor2 == LOW) 
      { 
        state = 2; 
        timeoutStart = millis(); 
      } 
      break; 

    case 1: // Entry sequence started (IR1 triggered first)
      if(sensor2 == LOW) 
      { 
        studentCount++; 
        if(studentCount > 99) studentCount = 99; 

        display.showNumberDec(studentCount, true); 
        Serial.println("ENTRY"); 
        updateDashboard(); 
        
        delay(500); // Debounce / pass-through pause
        state = 0; 
      } 
      else if(millis() - timeoutStart > TIMEOUT) 
      { 
        state = 0; // Reset if person turns back
      } 
      break; 

    case 2: // Exit sequence started (IR2 triggered first)
      if(sensor1 == LOW) 
      { 
        if(studentCount > 0) studentCount--; 

        display.showNumberDec(studentCount, true); 
        Serial.println("EXIT"); 
        updateDashboard(); 

        delay(500); // Debounce / pass-through pause
        state = 0; 
      } 
      else if(millis() - timeoutStart > TIMEOUT) 
      { 
        state = 0; // Reset if person turns back
      } 
      break; 
  } 
} 

void updateDashboard() 
{ 
  // Triggers RED_LED when limit is reached or exceeded
  if(studentCount >= ROOM_LIMIT) 
  { 
    digitalWrite(RED_LED, HIGH); 
    digitalWrite(GREEN_LED, LOW); 
  } 
  else 
  { 
    digitalWrite(RED_LED, LOW); 
    digitalWrite(GREEN_LED, HIGH); 
  }
}