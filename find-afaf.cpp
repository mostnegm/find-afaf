#include <iostream>
#include <string>
#include <unistd.h> // include <windows.h> on windows
using namespace std;

// State variables
int chat_counters[7];
int location;
int step;
string dialog=
"LOC 0 CHAT 0 Hello how can I help you? /n"
"LOC 0 CHAT 0 string of option 1 LOC = 0 /n"
"LOC 0 CHAT 0 string of option 2 LOC = 1 /n"
;

string warnings=
"STEP 5 thirty minutes left/n"
"STEP 10 fifteen minutes left/n"
"STEP 13 5 minutes left/n"
;

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
void printToNewLine(string text)
{
	// loop through each character in the text
	for (size_t i = 0; i < text.size(); ++i)
	{
		// output one character
		// flush to make sure the output is not delayed
		cout << text[i]<<flush;
		usleep(60000); // use Sleep on windows
	}
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
    printToNewLine("You enter the corridor and find no one to talk to");
}
