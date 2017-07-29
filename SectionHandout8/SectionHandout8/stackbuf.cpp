/*
 * File: stackbuf.cpp
 * ------------------
 * This file implements the EditorBuffer class using a pair of
 * stacks to represent the buffer. The characters before the
 * cursor are stored in the before stack, and the characters
 * after the cursor are stored in the after stack.
 */
#include "genlib.h"
#include "buffer.h"
#include <iostream>
/*
 * Implementation notes: EditorBuffer
 * ----------------------------------
 * In this implementation, the only thing that needs to happen is
 * that the two stacks are initialized to be empty. That happens
 * automatically when the CharStack variables are declared.
 */
EditorBuffer::EditorBuffer() {
    /* Empty */
}
/*
 * Implementation notes: ~EditorBuffer
 * -----------------------------------
 * The destructor has to free any dynamically allocated memory.
 * In this implementation, however, all the allocation occurs in
 * the CharStack class and will be managed by its destructor.
 */
EditorBuffer::~EditorBuffer() {
    /* Empty */
}
/*
 * Implementation notes: moveCursor methods
 * ----------------------------------------
 * The four moveCursor methods use push and pop to transfer
 * values between the two stacks.
 */
void EditorBuffer::moveCursorForward() {
    if (!after.isEmpty()) {
        before.push(after.pop());
    }
}
void EditorBuffer::moveCursorBackward() {
    if (!before.isEmpty()) {
        after.push(before.pop());
    }
}
void EditorBuffer::moveCursorToStart() {
    while (!before.isEmpty()) {
        after.push(before.pop());
    }
}
void EditorBuffer::moveCursorToEnd() {
    while (!after.isEmpty()) {
        before.push(after.pop());
    }
}

void EditorBuffer::moveCursorToWordBegin() {
    while (!before.isEmpty() && isspace(before.peek())) {
        moveCursorBackward();
    }
    while (!before.isEmpty() && !isspace(before.peek())) {
        moveCursorBackward();
    }
}

/*
 * Implementation notes: insertCharacter and deleteCharacter
 * ---------------------------------------------------------
 * Each of the functions that inserts or deletes characters
 * can do so with a single push or pop operation.
 */
void EditorBuffer::insertCharacter(char ch) {
    before.push(ch);
}
void EditorBuffer::deleteCharacter() {
    if (!after.isEmpty()) {
        after.pop();
    }
}
/*
 * Implementation notes: display()
 * -------------------------------
 * The display operator is complicated in the stack-based version,
 * but it is not part of the fundamental operator set.
 */
void EditorBuffer::display() {
    int nBefore = before.size();
    moveCursorToStart();
    while (!after.isEmpty()) {
        cout << ' ' << after.peek();
        moveCursorForward();
    }
    cout << endl;
    moveCursorToStart();
    for (int i = 0; i < nBefore; i++) {
        cout << "  ";
        moveCursorForward();
    }
    cout << '^' << endl;
}