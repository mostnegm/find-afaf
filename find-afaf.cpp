#include <iostream>
#include <string>
#include <unistd.h> // include <windows.h> on windows
using namespace std;

// State variables
int chat[7];
int loc;
int step;

//LOC0=receptionist
//LOC1=bench
//LOC2=corridor
//LOC3=manager office
//LOC4=afaf office
//LOC5=toilets
//LOC6=prayers
//LOCX=offense

string dialog =
"LOC 0 CHAT 0 Receptions says wait \n"
"1- You wait for afaf on the bench ENTER 1\n"
"2- You refuse to wait and search for afaf ENTER 2\n"
"LOC 1 CHAT 0 You've been waiting for 15 minutes and nothing happens.\n"
"1- You go to the receptionist again ENTER 0\n"
"2- You search for afaf ENTER 2\n"
"LOC 0 CHAT 1 Reception says wait again \n"
"1- You wait for afaf on the bench ENTER X\n"
"2- You refuse to wait and search for afaf ENTER 2\n"
"LOC X CHAT 0 Enta ghaby\n"
"LOC 2 CHAT 0 You find two office rooms and a prayer zone\n"
"1- You enter first office\n"
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
void printWaitingToNewLine(){
    string loading=". . .";
    for (size_t i = 0; i < 5; ++i)
    {
        cout << loading[i] << flush;
        usleep(500000); // use Sleep on windows
    }
}

///////////////////////
/* Parsing functions */
///////////////////////
// Returns the next dialogue message from the dialogue database.
string findNextDialogue(int loc, int chat){
    string loc_text= to_string(loc);
    string chat_text= to_string (chat);
    size_t start=dialog.find("LOC "+loc_text+" CHAT "+chat_text);
    size_t end=dialog.find("\n", start);
    size_t sentence=end-start-13;
    return (dialog.substr(start+13,sentence));
}

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
string checkIfWarningNeeded(int step) {
    if (step==5) {
        return "60 minutes left";
    }
    if (step==10) {
        return "30 minutes left";
    }
    if (step==13) {
        return "15 minutes left";
    }
    
    return " ";
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
    printWaitingToNewLine();
    cout<<endl;
}
