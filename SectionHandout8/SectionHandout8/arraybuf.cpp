/*
 * File: arraybuf.cpp
 * ------------------
 * This file implements the EditorBuffer class using an
 * array to represent the buffer.
 */
#include "genlib.h"
#include "buffer.h"
#include <iostream>
/* Constants */
const int INITIAL_CAPACITY = 100;
/*
 * Implementation notes: EditorBuffer
 * ----------------------------------
 * In this representation of the buffer, the characters are stored
 * in a dynamic array along with integers storing the capacity of
 * the buffer (its allocated size), the length of the buffer (its
 * effective size), and the cursor position. The cursor position
 * indicates the index position of the character that follows where
 * the cursor would appear on the screen. The constructor simply
 * initializes that structure.
 */
EditorBuffer::EditorBuffer() {
    capacity = INITIAL_CAPACITY;
    array = new char[capacity];
    length = 0;
    cursor = 0;
}
/*
 * Implementation notes: ~EditorBuffer
 * -----------------------------------
 * The destructor has to free any memory that is allocated
 * along the way in order to support the guarantee that
 * the editor buffer not leak memory. The only dynamically
 * allocated memory is the dynamic array that stores the text.
 */
EditorBuffer::~EditorBuffer() {
    delete[] array;
}
/*
 * Implementation notes: moveCursor methods
 * ----------------------------------------
 * The four moveCursor methods simply adjust the value of the
 * cursor instance variable.
 */
void EditorBuffer::moveCursorForward() {
    if (cursor < length) cursor++;
}
void EditorBuffer::moveCursorBackward() {
    if (cursor > 0) cursor--;
}
void EditorBuffer::moveCursorToStart() {
    cursor = 0;
}
void EditorBuffer::moveCursorToEnd() {
    cursor = length;
}

void EditorBuffer::moveCursorToWordBegin() {
    while (cursor - 1 >= 0 && isspace(array[cursor - 1])) {
        moveCursorBackward();
    }
    while (cursor - 1 >= 0 && !isspace(array[cursor - 1])) {
        moveCursorBackward();
    }
}

/*
 * Implementation notes: insertCharacter and deleteCharacter
 * ---------------------------------------------------------
 * Each of the functions that inserts or deletes characters
 * must shift all subsequent characters in the array, either
 * to make room for new insertions or to close up space left
 * by deletions.
 */
void EditorBuffer::insertCharacter(char ch) {
    if (length == capacity) expandCapacity();
    for (int i = length; i > cursor; i--) {
        array[i] = array[i - 1];
    }
    array[cursor] = ch;
    length++;
    cursor++;
}
void EditorBuffer::deleteCharacter() {
    if (cursor < length) {
        for (int i = cursor+1; i < length; i++) {
            array[i - 1] = array[i];
        }
        length--;
    }
}

void EditorBuffer::display() {
    for (int i = 0; i < length; i++) {
        cout << ' ' << array[i];
    }
    cout << endl;
    for (int i = 0; i < cursor; i++) {
        cout << "  ";
    }
    cout << '^' << endl;
}
/*
 * Implementation notes: expandCapacity
 * ------------------------------------
 * This private method doubles the size of the array whenever
 * it runs out of space. To do so, it must allocate a new array,
 * copy all the characters from the old array to the new one, and
 * then free the old storage.
 */
void EditorBuffer::expandCapacity() {
    char *oldArray = array;
    capacity *= 2;
    array = new char[capacity];
    for (int i = 0; i < length; i++) {
        array[i] = oldArray[i];
    }
    delete[] oldArray;
}
