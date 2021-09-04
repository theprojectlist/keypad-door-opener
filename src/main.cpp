#include <AccelStepper.h>
#include <Keypad.h>
#include <Arduino.h>

// Set for serial printing
#define DEBUG true

const char password[] = "ABC123";
size_t password_len = 0;  // Set in setup()

unsigned long num_entered = 0;
bool correct = true;

#define ROWS 4
#define COLS 4

#define PIN_STEP 2
#define PIN_DIRECTION 3

#define PIN_ROW_1 5
#define PIN_ROW_2 6
#define PIN_ROW_3 7
#define PIN_ROW_4 8
#define PIN_COL_1 9
#define PIN_COL_2 10
#define PIN_COL_3 11
#define PIN_COL_4 12

char hexaKeys[ROWS][COLS] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {PIN_ROW_1, PIN_ROW_2, PIN_ROW_3, PIN_ROW_4};
byte colPins[COLS] = {PIN_COL_1, PIN_COL_2, PIN_COL_3, PIN_COL_4};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
AccelStepper stepper = AccelStepper(1, PIN_STEP, PIN_DIRECTION);

void unlock() {
#if DEBUG
    Serial.println("Unlocking...");
#endif
    stepper.moveTo(1000);
    stepper.runToPosition();
    delay(1000);
    stepper.moveTo(0);
    stepper.runToPosition();
#if DEBUG
    Serial.println("Locked\n");
#endif
}

void setup() {
    password_len = strlen(password);

#ifdef DEBUG
    Serial.begin(115200);
#endif

    pinMode(PIN_STEP, OUTPUT);
    pinMode(PIN_DIRECTION, OUTPUT);

    stepper.setMaxSpeed(8000);
    stepper.setAcceleration(10000);
    stepper.moveTo(1000);
}

void loop() {
    char input = customKeypad.getKey();

    if (!input){
        return;
    } else {
#ifdef DEBUG
        Serial.print(input);
#endif
    }

    if (input == '#') {
#ifdef DEBUG
        Serial.println("\n");
#endif
        if (correct && num_entered == password_len) {
            unlock();
        }

        correct = true;
        num_entered = 0;
        return;
    } else {
        if (num_entered >= password_len) {
            correct &= false;
        } else {
            correct &= password[num_entered] == input;
        }
    }
    num_entered++;
}
