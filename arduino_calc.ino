


#include <Keypad.h>
#include <LiquidCrystal.h>
//#include <stdlib.h>
//#include <math.h>

long first = 0;
long second = 0;
double total = 0;
char input[9]; //buffer for input characters
char customKey;



///////////////////////////////////////////////////////KEYPAD SETUP///////////////////////////////////////
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '*'},
  {'C', '0', '=', '/'}
};

// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 1, 2, 3, 4 };
// Connect keypad COL0, COL1, COL2, and COL3 to these Arduino pins.
byte colPins[COLS] = { 5, 6, 7, 8 };

// Create the Keypad
Keypad customKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

///////////////////////////////////////////////////////LCD SETUP///////////////////////////////////////
LiquidCrystal lcd(10, 11, 12, A0, A1, A2);

void setup()
{
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LOADING");
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 1);
    lcd.write(255);
    delay(170);
  }
  lcd.clear();
  for (int i = 0; i < 8; i++) {
    input[i] = '0';  // initialize input as zero
  }
}


void loop()
{
  customKey = customKeypad.getKey();
  switch(customKey) 
  {
  case '0' ... '9': // This keeps collecting the first value until a operator is pressed "+-*/"
    lcd.setCursor(0,0);
    first = first * 10 + (customKey - '0');
    lcd.print(first);
    break;

  case '+':
    first = (total != 0 ? total : first);
    lcd.setCursor(0,1);
    lcd.print("+");
    second = SecondNumber(); // get the collected the second number
    total = first + second;
    lcd.setCursor(0,3);
    lcd.print(total);
    first = 0, second = 0; // reset values back to zero for next use
    break;

  case '-':
    first = (total != 0 ? total : first);
    lcd.setCursor(0,1);
    lcd.print("-");
    second = SecondNumber();
    total = first - second;
    lcd.setCursor(0,3);
    lcd.print(total);
    first = 0, second = 0;
    break;

  case '*':
    first = (total != 0 ? total : first);
    lcd.setCursor(0,1);
    lcd.print("*");
    second = SecondNumber();
    total = first * second;
    lcd.setCursor(0,3);
    lcd.print(total);
    first = 0, second = 0;
    break;

  case '/':
    first = (total != 0 ? total : first);
    lcd.setCursor(0,1);
    lcd.print("/");
    second = SecondNumber();
    lcd.setCursor(0,3);

    second == 0 ? lcd.print("Invalid") : total = (float)first / (float)second;

    lcd.print(total);
    first = 0, second = 0;
    break;

  case 'C':
    total = 0;
    lcd.clear();
    break;
  }
}

long SecondNumber()
{
  while( 1 )
  {
  customKey = customKeypad.getKey();
    if(customKey >= '0' && customKey <= '9')
    {
      second = second * 10 + (customKey - '0');
      lcd.setCursor(0,2);
      lcd.print(second);
    }

    if(customKey == '=') break;  //return second;
  }
 return second; 
}
