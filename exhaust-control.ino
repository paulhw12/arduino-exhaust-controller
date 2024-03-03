// Script that allows an Arduino to control exhaust valves, when soldered to the button pads of the valve remote keyfob
// Paul Hampton Feb 2024

// Define pin numbers
const int buttonPin = 2; // The pin that the button is attached to
const int onSignalPin = 3; // The pin for the "On" signal
const int offSignalPin = 4; // The pin for the "Off" signal
const int ledPin = 13; // The pin for the built-in LED, usually pin 13 on most Arduino boards

// Settings
bool lastButtonState = HIGH; // the previous reading from the input pin
bool currentButtonState = HIGH; // Current state of the button
bool outputState = LOW; // Current state of the output, starts as "Off"
unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 50; // the debounce time; increase if the output flickers
unsigned long lastButtonPressTime = 0; // Time when the button was last pressed
unsigned long signalDuration = 300; // Duration to keep the signals "On" or "Off"

void setup() {
  // Initialize the button pin as an input with pull-up resistor:
  pinMode(buttonPin, INPUT_PULLUP);
  // Initialize the signal pins as inputs to start in high-impedance state
  pinMode(onSignalPin, INPUT);
  pinMode(offSignalPin, INPUT);
  // Initialize the built-in LED pin as an output:
  pinMode(ledPin, OUTPUT);
  
  // Ensure the built-in LED is off initially
  digitalWrite(ledPin, LOW);
}

void loop() {
  bool reading = digitalRead(buttonPin);

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != currentButtonState) {
      currentButtonState = reading;

      // only toggle the LED if the new button state is LOW
      if (currentButtonState == LOW) {
        outputState = !outputState;
        lastButtonPressTime = millis(); // Record the time of button press

        if (outputState) {
          pinMode(onSignalPin, OUTPUT);
          digitalWrite(onSignalPin, LOW); // Activate "On" signal by grounding it
          pinMode(offSignalPin, INPUT); // Ensure "Off" signal is disconnected
          digitalWrite(ledPin, HIGH); // Turn on the built-in LED
        } else {
          pinMode(offSignalPin, OUTPUT);
          digitalWrite(offSignalPin, LOW); // Activate "Off" signal by grounding it
          pinMode(onSignalPin, INPUT); // Ensure "On" signal is disconnected
          digitalWrite(ledPin, LOW); // Turn off the built-in LED
        }
      }
    }
  }

  // After 2 seconds, set both the "On" and "Off" signals to high-impedance state
  if (millis() - lastButtonPressTime >= signalDuration) {
    pinMode(onSignalPin, INPUT); // Disconnect "On" signal
    pinMode(offSignalPin, INPUT); // Disconnect "Off" signal
    // Note: The LED state remains unchanged unless the button is pressed again
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
