/*
 * File: editor.cpp
 * ----------------
 * This program implements a simple character editor, which
 * is used to test the buffer class. The editor reads
 * and executes simple commands entered by the user.
 */
#include "genlib.h"
#include "buffer.h"
#include "simpio.h"
#include <iostream>
#include <cctype>
/* Private function prototypes */
void ExecuteCommand(EditorBuffer & buffer, string line);
/* Main program */
int editor_main() {
    EditorBuffer buffer;
    while (true) {
        cout << "*";
        string cmd = GetLine();
        if (cmd != "") ExecuteCommand(buffer, cmd);
        buffer.display();
    }
    return 0;
}
/*
 * Executes a single editor command.
 */
void ExecuteCommand(EditorBuffer & buffer, string line) {
    switch (toupper(line[0])) {
        case 'I': for (int i = 1; i < line.length(); i++) {
            buffer.insertCharacter(line[i]);
        }
            break;
        case 'D': buffer.deleteCharacter(); break;
        case 'F': buffer.moveCursorForward(); break;
        case 'B': buffer.moveCursorBackward(); break;
        case 'J': buffer.moveCursorToStart(); break;
        case 'E': buffer.moveCursorToEnd(); break;
        case 'W': buffer.moveCursorToWordBegin(); break;
        case 'Q': exit(0);
        default: cout << "Illegal command" << endl; break;
    }
}
