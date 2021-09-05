#include <main.hpp>

// Declare external variables
long home_pos = 0;
const char password[] = "*";
size_t password_len = 0;  // Set in setup()
unsigned long num_entered = 0;
bool correct = true;
char hexaKeys[ROWS][COLS] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {PIN_ROW_1, PIN_ROW_2, PIN_ROW_3, PIN_ROW_4};
byte colPins[COLS] = {PIN_COL_1, PIN_COL_2, PIN_COL_3, PIN_COL_4};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS,
                             COLS);
AccelStepper stepper = AccelStepper(1, PIN_STEP, PIN_DIRECTION);

void home() {
    // Move back a little
    stepper.moveTo(-200);
    stepper.runToPosition();

//    while (1)
//        Serial.println(digitalRead(PIN_LIMIT_SWITCH));

    while (!digitalRead(PIN_LIMIT_SWITCH)) {
        stepper.moveTo(stepper.currentPosition() + 1);
        stepper.runToPosition();
    }

    home_pos = stepper.currentPosition();
}

void unlock() {
#if DEBUG
    Serial.println("Unlocking...");
#endif

    stepper.moveTo(home_pos - STEPPER_OPEN_CLOSE_DIST_TRAVEL);
    stepper.runToPosition();
    delay(MILLIS_HOLD_DOOR_OPEN_FOR);
    stepper.moveTo(home_pos);
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
    pinMode(PIN_LIMIT_SWITCH, INPUT_PULLUP);

    stepper.setAcceleration(STEPPER_HOME_ACCEL);
    stepper.setMaxSpeed(STEPPER_HOME_SPEED);
    home();
    stepper.setAcceleration(STEPPER_OPEN_CLOSE_ACCEL);
    stepper.setMaxSpeed(STEPPER_OPEN_CLOSE_SPEED);
}

void loop() {
    char input = customKeypad.getKey();

    if (!input) {
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
