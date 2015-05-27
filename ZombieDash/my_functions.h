// My function prototypes for Teensy ZombieDash v1.0
// Lachlan Robinson, for CAB202 Sem 1 2015

// Global Variables
volatile int LEFT = 0;
volatile int RIGHT = 0;
int screen_x = 83;
int screen_x_Full = 83;
int screen_y = 47;
int screen_y_Full = 47;
int charWidth = 8;
int charHeight = 8;
volatile int previousLEFT = 0;
volatile int previousRIGHT = 0;
volatile int buttonPressed = 0;
volatile int previousButton = 0;
volatile int Direction = 1; // {up , down, left, right};
volatile int clockCounter = 0;
volatile int GAMEON = 0;
volatile int HeroX = 1;
volatile int HeroY = 0;
byte width = 3;
byte height = 3;

Sprite *my_pointer;
Sprite *my_pointer2;
Sprite *zombie[8];
//Sprite zombies[8];

int Lives = 3;
int Score = 0;

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

// Initialize interrupt for timer for movement etc
void TimerInit(void);

// Move hero forward one unit
void heroForward(void);

// Draws the Current Screen
void drawScreen(void);

void setupZombies(void);