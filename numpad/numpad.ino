// Pin Definitions
#define R1 4
#define R2 5
#define R3 6
#define R4 7

#define C1 8
#define C2 9
#define C3 10
#define C4 11

// Response LEDs
#define LED_GREEN 12
#define LED_RED 13

const int ROWS = 4;
const int COLS = 4;

char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

int rowPins[ROWS] = {R1, R2, R3, R4};
int colPins[COLS] = {C1, C2, C3, C4};

// This function waits for a key press and its release
char getKey()
{
  char key = 0; // No key pressed
  while (true)
  {
    for (int i = 0; i < ROWS; i++)
    {
      digitalWrite(rowPins[i], LOW); // Activate the row
      for (int j = 0; j < COLS; j++)
      {
        if (digitalRead(colPins[j]) == LOW) // If the column is LOW, a key is pressed
        {
          delay(10); // Debounce delay
          if (digitalRead(colPins[j]) == LOW)
          {                   // Check again for better stability
            key = keys[i][j]; // Record the key value
            while (digitalRead(colPins[j]) == LOW)
              ;                             // Wait until key release
            digitalWrite(rowPins[i], HIGH); // Deactivate the row
            return key;                     // Return the recorded key once released
          }
        }
      }
      digitalWrite(rowPins[i], HIGH); // Deactivate the row
    }
  }
}

void setup()
{
  Serial.begin(9600);

  // Initialize the keypad
  for (int i = 0; i < ROWS; i++)
  {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH); // Deactivate the rows
  }

  for (int j = 0; j < COLS; j++)
  {
    pinMode(colPins[j], INPUT_PULLUP); // Use the internal pull-up resistor
  }

  // Initialize the LEDs
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
}

void loop()
{
  // 4 digit correct PIN
  char CORRECT_PIN[4] = {'1', '2', '3', '4'};
  char entered_PIN[4];
  int i;

  // Get the entered PIN
  for (int i = 0; i < 4; i++)
  {
    entered_PIN[i] = getKey();
    Serial.print(entered_PIN[i]);
  }

  // Check if the entered PIN is correct
  bool correct = true;

  for (i = 0; i < 4; i++)
  {
    delay(100); // Side channel attack demonstration
    if (entered_PIN[i] != CORRECT_PIN[i])
    {

      correct = false;
      break;
    }
  }

  if (correct)
  {
    Serial.println(" - Correct PIN");

    // Turn on the green LED for 1 second
    digitalWrite(LED_GREEN, HIGH);
    delay(1000);
    digitalWrite(LED_GREEN, LOW);
  }
  else
  {
    Serial.print(" - Incorrect PIN -- Failed at digit: ");
    Serial.println(entered_PIN[i]);

    // Turn on the red LED for 1 second
    digitalWrite(LED_RED, HIGH);
    delay(100);
    digitalWrite(LED_RED, LOW);
    delay(100);
    digitalWrite(LED_RED, HIGH);
    delay(1000);
    digitalWrite(LED_RED, LOW);
  }
}
