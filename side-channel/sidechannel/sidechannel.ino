#define SIDECHANNEL_MONITOR 16

void setup()
{
  // put your setup code here, to run once:
  pinMode(SIDECHANNEL_MONITOR, INPUT);
  // Pull the pin low
  digitalWrite(SIDECHANNEL_MONITOR, LOW);

  Serial.begin(115200);
  Serial.println("Side channel monitoring started");
}

void loop()
{
  // Monitoring the time when Side channel pin comes high and goes back to low

  int startMillis = 0; // Store the start time when the pin goes HIGH
  int elapsed = 0;     // Store elapsed time
  int temp = 0;
  // Wait until the side channel pin goes HIGH
  while (digitalRead(SIDECHANNEL_MONITOR) == LOW)
  {
    // Intentionally empty: waiting for pin to go HIGH
    yield();
  }

  // Record the start time
  startMillis = millis(); // Record the time when pin goes HIGH
  Serial.println("Side channel pin is high");

  // Now wait for the pin to go LOW
  while (digitalRead(SIDECHANNEL_MONITOR) == HIGH)
  {
    // Intentionally empty: waiting for pin to go LOW
    yield();
  }
  elapsed = millis() - startMillis; // Calculate elapsed time
  Serial.print("Elapsed time while pin was high: ");
  Serial.println(elapsed);

  /**
   * Elapsed values table
   * 1: First digit incorrect
   * 2: Second digit incorrect
   * 3: Third digit incorrect
   * 4: Fourth digit incorrect
   * 5: All digits correct
   */

  // Expected output OOX- . O is the correct digit, X is the incorrect digit and - is to denote not checked
  if (elapsed == 1)
  {
    Serial.println("X - - -");
  }
  else if (elapsed == 2)
  {
    Serial.println("O X - -");
  }
  else if (elapsed == 3)
  {
    Serial.println("O O X -");
  }
  else if (elapsed == 4)
  {
    Serial.println("O O O X");
  }
  else if (elapsed == 5)
  {
    Serial.println("O O O O");
  }
  else
  {
    Serial.println("Invalid elapsed time");
  }
}
