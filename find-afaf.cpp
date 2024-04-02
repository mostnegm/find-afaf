#include <iostream>
#include <string>
#include <unistd.h> // include <windows.h> on windows
using namespace std;

// State variables
int chat[7];
int location;
int step;

//LOC0=receptionist
//LOC1=bench
//LOC2=corridor
//LOC3=manager office
//LOC4=afaf office
//LOC5=toilets
//LOC6=prayers

string dialog =
"LOC 0 CHAT 0 موظف الاستقبال قالك شوية وجاية\n"
"1- You wait for afaf on the bench ENTER 1 \n"
"2- You refuse to wait and search for afaf ENTER 2\n"
"LOC 1 CHAT 0 You've been waiting for 15 minutes and nothing happens.\n"
"1- You go to the receptionist again\n"
"2- You search for afaf\n"
"LOC 2 CHAT 0 You find two office rooms and a prayer zone\n"
"1- You enter first office \n"
"2- You enter second office\n"
"3- You enter prayer zone\n"
;

string warnings =
"STEP 5 thirty minutes left\n"
"STEP 10 fifteen minutes left\n"
"STEP 13 5 minutes left\n"
;

//////////////////////
/* Output functions */
//////////////////////

// Prints the provided string to the screen, with a slow animation.
void printToNewLine(string text){
    for (size_t i = 0; i < text.size(); ++i)
    {
        cout << text[i] << flush;
        usleep(100000); // use Sleep on windows
    }
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
void checkIfWarningNeeded(int step) {
    if (step==5) {
        cout << "60 minutes left";
    }
    if (step==10) {
        cout << "30 minutes left";
    }
    if (step==13) {
        cout << "15 minutes left";
    }
}

// Returns whether the user has won the game.
bool checkIfWin(int loc, int chat, int step);
// Returns whether the user has lost the game.
bool checkIfLose(int loc, int chat, int step);


/////////////////////////
/* Game loop functions */
/////////////////////////
// This function runs the infinite game loop.
// The game loop consists of:
// - Checking the current game state.
// - Updating the GUI based on the current game state (win, lose, next state).
// - Waits for new user input.
void startGame() {
    while (true) {
        printToNewLine(dialog.substr(0,5));
        break;
    }
}



int main()
{
    printToNewLine(dialog.substr(13,56));
    cout<<endl;
}
