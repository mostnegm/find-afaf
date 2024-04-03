#include <iostream>
#include <string>
#ifdef __APPLE__
    #include <unistd.h>
#else
    #include <windows.h>
#endif
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
"LOC 0 CHAT 0 Receptions says wait\n"
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
void printToNewLine(string text) {
    for (size_t i = 0; i < text.size(); ++i) {
        cout << text[i] << flush;
        #ifdef __APPLE__
            usleep(100000);
        #else
            Sleep(100);
        #endif
    }
}

// Prints a short loading bar (. . .) simulating wait time, blocking input.
void printWaitingToNewLine() {
    string loading=". . .";
    for (size_t i = 0; i < 5; ++i) {
        cout << loading[i] << flush;
        #ifdef __APPLE__
            usleep(500000);
        #else
            Sleep(1000);
        #endif
    }
    cout << endl;
}

///////////////////////
/* Parsing functions */
///////////////////////

// Returns the next dialogue message from the dialogue database.
string findNextDialogue(int loc, int chat) {
    string loc_txt = to_string(loc);
    string chat_txt = to_string(chat);
    size_t start = dialog.find("LOC " + loc_txt + " CHAT " + chat_txt);
    size_t end = dialog.find("\n", start);
    size_t dialog_length = end-start-13;
    string dialog_txt = dialog.substr(start + 13, dialog_length);
    return (dialog_txt);
}

// Returns the next list of options from the dialogue database
// based on the current dialogue message.
string findNextOptions(int loc, int chat) {
    string loc_text = to_string(loc);
    string chat_text = to_string(chat);
    size_t dialogue = dialog.find("LOC " + loc_text + " CHAT " + chat_text);
    size_t start = dialog.find("\n", dialogue);
    size_t end = dialog.find("ENTER", start);
    size_t option_length = end-start-1;
    string option_txt = dialog.substr(start +1, option_length);
    return (option_txt);
}

// Returns the next state update code related to the selected option.
string findSelectedOptionLocUpdate(int loc, int chat, int option);

////////////////////////////
/* State update functions */
////////////////////////////

// Updates the current loc state using the next loc code.
void updateCurrentLoc(int nextLoc) {
    step++;
    chat[loc]++;
    loc = nextLoc;
}

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
bool checkIfWin(int loc, int chat) {
    if ((loc == 3 && chat == 1)) {
        return (true);
    }
    return(false);
}

// Returns whether the user has lost the game.
bool checkIfLose(int step) {
    if (step == 15) {
        return(true);
    }
    return(false);
}

////////////////////////
/* Game loop function */
////////////////////////

// This function runs the infinite game loop.
// The game loop consists of:
// - Checking the current game state.
// - Updating the GUI based on the current game state (win, lose, next state).
// - Waits for new user input.
void startGame() {
    while (true) {
        
        ++step;
    }
}

int runSystemChecks() {
    // Testing printToNewLine
    printToNewLine("Hi there, nice meeting you!\n");
    
    // Testing printWaitingToNewLine
    printWaitingToNewLine();
    
    // Testing findNextDialogue
    string nextDialogue1 = findNextDialogue(0, 0);
    cout << nextDialogue1 << endl;
    if (nextDialogue1 != "Receptions says wait") {
        return -1;
    }
    
    // Testing findNextOptions
    
    // Testing updateCurrentLoc
    
    // Testing checkIfWarningNeeded
    
    // Testing checkIfWin
    
    // Testing checkIfLose
    
    return 0;
}

// Intro function.
int main() {
    int error = runSystemChecks();
    if (error != 0) {
        cout << "Something is broken.\n";
        return 0;
    }
    
    // Game loop.
    
    return 0;
}
