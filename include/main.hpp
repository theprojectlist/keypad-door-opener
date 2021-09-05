#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-dynamic-static-initializers"

#include <AccelStepper.h>
#include <Keypad.h>
#include <Arduino.h>

// Set for serial printing
#define DEBUG true

// Password
extern const char password[];
extern size_t password_len;  // Set in setup()
extern unsigned long num_entered;
extern bool correct;

// Stepper
#define PIN_STEP                       2
#define PIN_DIRECTION                  3
#define PIN_LIMIT_SWITCH               4
#define STEPPER_HOME_ACCEL             10000
#define STEPPER_HOME_SPEED             500
#define STEPPER_OPEN_CLOSE_DIST_TRAVEL 4000
#define MILLIS_HOLD_DOOR_OPEN_FOR      2000
#define STEPPER_OPEN_CLOSE_ACCEL       10000
#define STEPPER_OPEN_CLOSE_SPEED       8000
extern long home_pos;
extern AccelStepper stepper;

// Pin pad
#define ROWS      4
#define COLS      4
#define PIN_ROW_1 5
#define PIN_ROW_2 6
#define PIN_ROW_3 7
#define PIN_ROW_4 8
#define PIN_COL_1 9
#define PIN_COL_2 10
#define PIN_COL_3 11
#define PIN_COL_4 12
extern char hexaKeys[ROWS][COLS];
extern byte rowPins[ROWS];
extern byte colPins[COLS];
extern Keypad customKeypad;


void unlock();

void home();

#pragma clang diagnostic pop
