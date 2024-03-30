#include <iostream>

// State variables
int chat_counters[];
int location;
int step;
string dialog = `
LOC 0 CHAT 0 Hi how can I help you ?
LOC 0 CHAT 0 string of option 1 LOC = 0
LOC 0 CHAT 0 string of option 2 LOC = 1
`;
string warnings = `
STEP 0 you started your journey
STEP 10 you are getting tired..
`;

/////////////////////////
/* Game loop functions */
/////////////////////////
// This function runs the infinite game loop.
// The game loop consists of:
// - Checking the current game state.
// - Updating the GUI based on the current game state (win, loose, next state).
// - Waits for new user input.
void startGame();

//////////////////////
/* Output functions */
//////////////////////
// Prints the provided string to the screen, with a slow animation.
void printToNewLine(string text, int identation);
// Prints a short loading bar (. . .) simulating wait time, blocking input.
void printWaitingToNewLine(int ms);

///////////////////////
/* Parsing functions */
///////////////////////
// Returns the next dialogue message from the dialogue database.
string findNextDialogue(int loc, int chat);
// Returns the next list of options from the dialogue database
// based on the current dialogue message.
string findNextOptions(int loc, int chat);
// Returns the next state update code related to the selected option.
string findSelectedOptionLocUpdate(int loc, int chat, int option);

////////////////////////////
/* State update functions */
////////////////////////////
// Updates the current loc state using the next loc code.
string updateCurrentLoc(string nextLoc);
// Returns the proper warning message based on the current state, if any. 
string checkIfWarningNeeded(int step);
// Returns whether the user has won the game.
bool checkIfWin(int loc, int chat, int step);
// Returns whether the user has lost the game.
bool checkIfLoose(int loc, int chat, int step);

int main() {
    // Insert code here.
}
