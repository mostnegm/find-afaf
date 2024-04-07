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
//LOC5=prayers
//LOC6=toilets
//LOCX=offense

string dialog =
"LOC 0 CHAT 0 Receptions says wait\n"
"1- sit and wait for afafENTER 1\n"
"2- ابحث عن مدام عفاف في الدور ENTER 2\n"

"LOC 1 CHAT 0 مضى من الوقت ربع ساعة ومدام عفاف مجتش\n"
"1- اذهب لموظف الاستقبال لتعبر عن استيائك ENTER 0\n"
"2- ابحث عن مدام عفاف في الدور ENTER 2\n"

"LOC 0 CHAT 1 موظف الاستقبال يقول لك اجلس استريح دقيقتين \n"
"1- اجلس وانتظر مدام عفاف ENTER X\n"
"2- عبر عن غضبك وابحث عن مدام عفاف في الدور ENTER 2\n"

"LOC X CHAT 0 أنت شخص ساذج...لن تحصل على ملفك الدراسي ابدا\n"

"LOC 2 CHAT 0 على يمينك غرفتين ويسارك مصلى\n"
"1- ادخل المكتب الاولENTER 3\n"
"2- ادخل المكتب الثانيENTER 4\n"
"3- ادخل المصلىENTER 5\n"

"LOC 3 CHAT 0 موظف الاستقبال يصرخ قائلاً 'دة مكتب العميد يا أستاذ!'\n"
"1- ادخل المكتب الثانيENTER 4\n"
"2- ادخل المصلىENTER 5\n"

"LOC 5 CHAT 0 لقد دخلت مصلى السيدات وايقظت الدادة بالخطأ\n"
"1- ادخل المكتب الثانيENTER 4\n"

"LOC 4 CHAT 0 لقد وصلت مكتب مدام عفاف ولكنك وجدت استاذ سيد وانسة منى فقط\n"
"1- اطلب ملفك الدراسيENTER 4\n"
"2- اسأل عن مدام عفافENTER 4\n"

"LOC 4 CHAT 1 أستاذ سيد يقول أن مدام عفاف جالها تليفون راحت تعمل حاجة وراجعة (انسة منى تكتم ابتسامة مريبة)\n"
"1- ارجع الاستقبال لتنتظر مدام عفافENTER 1\n"

"LOC 1 CHAT 1 مضى من الوقت نص ساعة ومدام عفاف مجتش\n"
"1- اطلب رقم مدام عفاف من موظف الاستقبالENTER 0\n"
"2- اذهب لمكتب مدام عفاف مجددا ENTER 4\n"

"LOC 0 CHAT 2 موظف الاستقبال يدعي انه لا يحمل رقم مدام عفاف\n"
"1- ارفع صوتك على موظف الاستقبال ENTER 555\n"
"2- اذهب لمكتب مدام عفاف مجددا ENTER 4\n"

"LOC 4 CHAT 2 أستاذ سيد راح يصلي ولكن انسة منى موجودة\n"
"1- اطلب رقم مدام عفاف من انسة منىENTER 1\n"
"2- ادي لانسة منى 20 جنيهENTER 1\n"
;

string warnings =
"STEP 5 باقي على ميعاد خروج الموظفين ساعة واحدة\n"
"STEP 10 باقي على ميعاد خروج الموظفين نصف ساعة\n"
"STEP 13 باقي على ميعاد خروج الموظفين عشر دقايق\n"
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
            Sleep(250);
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
    size_t option_start = dialog.find("\n", dialogue) + 1;

    string options_text = "";
    while (true) {
        size_t endLine = dialog.find('\n', option_start);
        string line = dialog.substr(option_start, endLine - option_start + 1);
        string firstChar = line.substr(0, 1);
        if (firstChar != "L") {
            option_start += line.length();
            size_t metaSubstrStart = line.find("ENTER");
            options_text += line.substr(0, metaSubstrStart) + "\n";
        } else {
            return options_text;
        }
    }
}

// Returns the next state update code related to the selected option.
int findLocOfSelectedOption(int loc, int chat, int option) {
    string loc_text = to_string(loc);
    string chat_text = to_string(chat);
    size_t dialog_start = dialog.find("LOC " + loc_text + " CHAT " + chat_text);
    size_t option_start = dialog.find("\n", dialog_start) + 1;
    
    while (true) {
        size_t endLine = dialog.find('\n', option_start);
        string line = dialog.substr(option_start, endLine - option_start + 1);
        string firstChar = line.substr(0, 1);
        string option_text = to_string(option);
        if (firstChar == option_text) {
            size_t lineEndLoc = line.find('\n');
            string loc_text = line.substr(lineEndLoc-1, 1);
            return stoi(loc_text);
        } else if (firstChar == "L") {
            // In case of incorrect input, return current location as well.
            return loc;
        } else {
            option_start += line.length();
        }
    }
}

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
    string nextOption1 = findNextOptions(0, 0);
    cout << nextOption1 << endl;
    if (nextOption1 != "1- sit and wait for afaf") {
        return -1;
    }
    
    
    // Testing checkIfWarningNeeded
    int warning_test;
    for (warning_test= 1; warning_test <= 15;++warning_test) {
        
        cout << checkIfWarningNeeded(warning_test);
            
    }
    
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
