#include <iostream>

// State variables
int chat_counters[];
int location;
int step;
string dialog =
LOC 0 CHAT 0 Hi how can I help you ?
LOC 0 CHAT 0 string of option 1 LOC = 0
LOC 0 CHAT 0 string of option 2 LOC = 1
;
string warnings =
STEP 0 you started your journey
STEP 10 you are getting tired..
;

// Game loop function
void startGame();

// Output functions
void printToNewLine(string text, int identation);
void printWaitingToNewLine(int ms);

// Parsing functions
string findNextDialogue(int loc, int chat);
string findNextOptions(int loc, int chat);
string findSelectedOptionLocUpdate(int loc, int chat, int option);

// State update functions
string updateCurrentLoc(string nextLoc);
bool checkIfWarningNeeded(int step);
bool checkIfWin(int loc, int chat, int step);
bool checkIfLoose(int loc, int chat, int step);