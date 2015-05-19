// My function prototypes for Teensy ZombieDash v1.0
// Lachlan Robinson, for CAB202 Sem 1 2015

// Global Variables
volatile int LEFT = 0;
volatile int RIGHT = 0;
int screen_x = 84;
int screen_y = 48;
int charWidth = 8;
int charHeight = 8;
volatile int previousLEFT = 0;
volatile int previousRIGHT = 0;
volatile int buttonPressed = 0;
volatile int previousButton = 0;

// Function Prototypes

// Checks button presses
void buttonCheck(void);

/**
* Random number generation:
* - 'seedWithButtonPress()': seeds the random number generator with an
* iterated count while waiting for a button press
* - 'randInRange()': uses the random number generator (assumes it has
* been seeded) to produce a random number between
* 'min' (inclusive') and 'max' (inclusive)
*/
void seedWithButtonPress(void);

int randInRange(int min, int max);

/* Sets up the game
pins, clock and screen initialised.
*/
void setupGame(void);

// Main Game function
void playGame(void);

// Beginning countdown
void CountDown(void);

// Initialises interrupt for button press
void PinChangeInit(void);
