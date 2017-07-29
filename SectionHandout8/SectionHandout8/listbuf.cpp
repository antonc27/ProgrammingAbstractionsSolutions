/*
 * File: listbuf.cpp
 * -----------------
 * This file implements the EditorBuffer class using a linked
 * list to represent the buffer.
 */
#include "genlib.h"
#include "buffer.h"
#include <iostream>
/*
 * Implementation notes: EditorBuffer constructor
 * ----------------------------------------------
 * This function initializes an empty editor buffer, represented
 * as a linked list. To simplify the link list operation, this
 * implementation adopts the useful programming tactic of
 * keeping an extra "dummy" cell at the beginning of each list,
 * so that the empty buffer has the following representation:
 *
 * +-------+          +------+
 * |   o---+-----====>|      |
 * +-------+    /     +------+
 * |   o---+---/      | NULL |
 * +-------+          +------+
 */
EditorBuffer::EditorBuffer() {
    start = cursor = new cellT;
    start->link = NULL;
}
/*
 * Implementation notes: EditorBuffer destructor
 * ---------------------------------------------
 * The destructor must delete every cell in the buffer. Note
 * that the loop structure is not exactly the standard idiom for
 * processing every cell within a linked list, because it is not
 * legal to delete a cell and later look at its link field. To
 * avoid selecting fields in the structure after it has been
 * deallocated, you have to copy the link pointer before calling
 * delete.
 */
EditorBuffer::~EditorBuffer() {
    cellT *cp = start;
    while (cp != NULL) {
        cellT *next = cp->link;
        delete cp;
        cp = next;
    }
}
/*
 * Implementation notes: cursor movement
 * -------------------------------------
 * The four functions that move the cursor have different time
 * complexities because the structure of a linked list is
 * asymmetrical with respect to moving backward and forward.
 * Moving forward one cell is simply a matter of picking up the
 * link pointer; moving backward requires a loop until you reach
 * the current cursor position. Similarly, moving to the start
 * of the buffer takes constant time, but finding the end requires
 * an O(N) loop.
 */
void EditorBuffer::moveCursorForward() {
    if (cursor->link != NULL) {
        cursor = cursor->link;
    }
}
void EditorBuffer::moveCursorBackward() {
    cellT *cp = start;
    if (cursor != start) {
        while (cp->link != cursor) {
            cp = cp->link;
        }
        cursor = cp;
    }
}
void EditorBuffer::moveCursorToStart() {
    cursor = start;
}
void EditorBuffer::moveCursorToEnd() {
    while (cursor->link != NULL) {
        moveCursorForward();
    }
}

void EditorBuffer::moveCursorToWordBegin() {
    cellT *wordStart = start;
    cellT *cp = start;
    if (cursor != start) {
        while (cp != cursor) {
            cellT *next = cp->link;
            if (isspace(cp->ch) && next != NULL && !isspace(next->ch)) {
                wordStart = cp;
            }
            cp = cp->link;
        }
        cursor = wordStart;
    }
}

/*
 * Implementation notes: insertCharacter
 * -------------------------------------
 * The primary advantage of the linked list representation for
 * the buffer is that the insertCharacter operation can now be
 * accomplished in constant time. The steps required are:
 *
 * 1. Allocate a new cell and put the new character in it.
 * 2. Copy the pointer indicating the rest of the list into the link.
 * 3. Update the link in the current cell to point to the new one.
 * 4. Move the cursor forward over the inserted character.
 */
void EditorBuffer::insertCharacter(char ch) {
    cellT *cp = new cellT;
    cp->ch = ch;
    cp->link = cursor->link;
    cursor->link = cp;
    cursor = cp;
}
/*
 * Implementation notes: deleteCharacter
 * -------------------------------------
 * As with insertCharacter, the list representation makes it
 * possible to implement the deleteCharacter operation in
 * constant time. The necessary steps are:
 *
 * 1. Remove the current cell from the chain by "pointing around it".
 * 2. Free the cell to reclaim the memory.
 */
void EditorBuffer::deleteCharacter() {
    if (cursor->link != NULL) {
        cellT *oldcell = cursor->link;
        cursor->link = oldcell->link;
        delete oldcell;
    }
}
/*
 * Implementation notes: display
 * -----------------------------
 * The display method uses the standard for loop idiom to loop
 * through the cells in the linked list. The first loop displays
 * the character; the second marks the cursor position.
 */
void EditorBuffer::display() {
    for (cellT *cp = start->link; cp != NULL; cp = cp->link) {
        cout << ' ' << cp->ch;
    }
    cout << endl;
    for (cellT *cp = start; cp != cursor; cp = cp->link) {
        cout << "  ";
    }
    cout << '^' << endl;
}