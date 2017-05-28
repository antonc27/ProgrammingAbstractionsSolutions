/*
 * File: tictactoe.cpp
 * -------------------
 * This program plays a game of tic-tac-toe with the user. The
 * code is designed to make it easy to adapt the general structure
 * to other games.
 */
#include "genlib.h"
#include "simpio.h"
#include "vector.h"
#include "grid.h"
#include <iostream>
/*
 * Constants: WINNING_POSITION, NEUTRAL_POSITION, LOSING_POSITION
 * --------------------------------------------------------------
 * These constants define a rating system for game positions. A
 * rating is an integer centered at 0 as the neutral score: ratings
 * greater than 0 are good for the current player, ratings less than
 * 0 are good for the opponent. The constants WINNING_POSITION and
 * LOSING_POSITION are opposite in value and indicate a position that
 * is a forced win or loss, respectively. In a game in which the
 * analysis is complete, no intermediate values ever arise. If the
 * full tree is too large to analyze, the EvaluatePosition function
 * returns integers that fall between the two extremes.
 */
const int WINNING_POSITION = 1000;
const int NEUTRAL_POSITION = 0;
const int LOSING_POSITION = -WINNING_POSITION;
/*
 * Type: playerT
 * -------------
 * This type is used to distinguish the human and computer
 * players and keep track of who has the current turn.
 */
enum playerT { Human, Computer };
/*
 * Type: moveT
 * -----------
 * For any particular game, the moveT type must keep track of the
 * information necessary to describe a move. For tic-tac-toe,
 * a moveT is simply an integer identifying the number of one of
 * the nine squares, as follows:
 *
 *  1 | 2 | 3
 * ---+---+---
 *  4 | 5 | 6
 * ---+---+---
 *  7 | 8 | 9
 */
typedef int moveT;
/*
 * Type: stateT
 * ------------
 * For any game, the stateT structure records the current state of
 * the game. As in Chapter 4, the tic-tac-toe board is represented
 * using a Grid<char>; the elements must be either 'X', 'O', or ' '.
 * In addition to the board array, the code stores a playerT value
 * to indicate whose turn it is. In this game, the stateT structure
 * also contains the total number of moves so that functions can
 * find this value without counting the number of occupied squares.
 */
struct stateT {
    Grid<char> board;
    playerT whoseTurn;
    int turnsTaken;
};
/*
 * Constant: MAX_DEPTH
 * -------------------
 * This constant indicates the maximum depth to which the recursive
 * search for the best move is allowed to proceed.
 */
const int MAX_DEPTH = 10000;
/*
 * Constant: FIRST_PLAYER
 * ----------------------
 * This constant indicates which player goes first.
 */
const playerT FIRST_PLAYER = Computer;
/* Private function prototypes */
void GiveInstructions();
moveT FindBestMove(stateT state, int depth, int & pRating);
int EvaluatePosition(stateT state, int depth);
stateT NewGame();
void DisplayGame(stateT state);
void DisplayMove(moveT move);
char PlayerMark(playerT player);
moveT GetUserMove(stateT state);
moveT ChooseComputerMove(stateT state);
void GenerateMoveList(stateT state, Vector<moveT> & moveList);
bool MoveIsLegal(moveT move, stateT state);
void MakeMove(stateT & state, moveT move);
void RetractMove(stateT & state, moveT move);
bool GameIsOver(stateT state);
void AnnounceResult(stateT state);
playerT WhoseTurn(stateT state);
playerT Opponent(playerT player);
int EvaluateStaticPosition(stateT state);
bool CheckForWin(stateT state, playerT player);
bool CheckForWin(Grid<char> & board, char mark);
bool CheckLine(Grid<char> & board, char mark,
               int row, int col, int dRow, int dCol);
/*
 * Main program
 * ------------
 * The main program, along with the functions FindBestMove and
 * EvaluatePosition, are general in their design and can be
 * used with most two-player games. The specific details of
 * tic-tac-toe do not appear in these functions and are instead
 * encapsulated in the stateT and moveT data structures and a
 * a variety of subsidiary functions.
 */
int main() {
    GiveInstructions();
    stateT state = NewGame();
    moveT move;
    while (!GameIsOver(state)) {
        DisplayGame(state);
        switch (WhoseTurn(state)) {
            case Human:
                move = GetUserMove(state);
                break;
            case Computer:
                move = ChooseComputerMove(state);
                DisplayMove(move);
                break;
        }
        MakeMove(state, move);
    }
    AnnounceResult(state);
    return 0;
}
/*
 * Function: GiveInstructions
 * Usage: GiveInstructions();
 * --------------------------
 * This function gives the player instructions about how to
 * play the game.
 */
void GiveInstructions() {
    cout << "Welcome to tic-tac-toe. The object of the game" << endl;
    cout << "is to line up three symbols in a row," << endl;
    cout << "vertically, horizontally, or diagonally." << endl;
    cout << "You'll be " << PlayerMark(Human) << " and I'll be "
    << PlayerMark(Computer) << "." << endl;
}
/*
 * Function: NewGame
 * Usage: state = NewGame();
 * -------------------------
 * This function starts a new game and returns a stateT that
 * has been initialized to the defined starting configuration.
 */
stateT NewGame() {
    stateT state;
    state.board.resize(3, 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            state.board(i, j) = ' ';
        }
    }
    state.whoseTurn = FIRST_PLAYER;
    state.turnsTaken = 0;
    return state;
}
/*
 * Function: DisplayGame
 * Usage: DisplayGame(state);
 * --------------------------
 * This function displays the current state of the game.
 */
void DisplayGame(stateT state) {
    if (GameIsOver(state)) {
        cout << "The final position looks like this:" << endl << endl;
    } else {
        cout << "The game now looks like this:" << endl << endl;
    }
    for (int i = 0; i < 3; i++) {
        if (i != 0) cout << "---+---+---" << endl;
        for (int j = 0; j < 3; j++) {
            if (j != 0) cout << "|";
            cout << " " << state.board(i, j) << " ";
        }
        cout << endl;
    }
    cout << endl;
}
/*
 * Function: DisplayMove
 * Usage: DisplayMove(move);
 * -------------------------
 * This function displays the computer's move.
 */
void DisplayMove(moveT move) {
    cout << "I'll move to " << move << endl;
}
/*
 * Function: FindBestMove
 * Usage: move = FindBestMove(state, depth, pRating);
 * --------------------------------------------------
 * This function finds the best move for the current player, given
 * the specified state of the game. The depth parameter and the
 * constant MAX_DEPTH are used to limit the depth of the search
 * for games that are too difficult to analyze in full detail.
 * The function returns the best move by storing an integer in
 * the variable to which pRating points.
 */
moveT FindBestMove(stateT state, int depth, int & rating) {
    Vector<moveT> moveList;
    GenerateMoveList(state, moveList);
    int nMoves = moveList.size();
    if (nMoves == 0) Error("No moves available");
    moveT bestMove;
    int minRating = WINNING_POSITION + 1;
    for (int i = 0; i < nMoves && minRating != LOSING_POSITION; i++) {
        moveT move = moveList[i];
        MakeMove(state, move);
        int curRating = EvaluatePosition(state, depth + 1);
        if (curRating < minRating) {
            bestMove = move;
            minRating = curRating;
        }
        RetractMove(state, move);
    }
    rating = -minRating;
    return bestMove;
}
/*
 * Function: EvaluatePosition
 * Usage: rating = EvaluatePosition(state, depth);
 * -----------------------------------------------
 * This function evaluates a position by finding the rating of
 * the best move in that position. The depth parameter and the
 * constant MAX_DEPTH are used to limit the depth of the search.
 */
int EvaluatePosition(stateT state, int depth) {
    int rating;
    if (GameIsOver(state) || depth >= MAX_DEPTH) {
        return EvaluateStaticPosition(state);
    }
    FindBestMove(state, depth, rating);
    return rating;
}
/*
 * Function: PlayerMark
 * Usage: mark = PlayerMark(player);
 * ---------------------------------
 * This function returns the mark used on the board to indicate
 * the specified player. By convention, the first player is
 * always X, so the mark used for each player depends on who
 * goes first.
 */
char PlayerMark(playerT player) {
    if (player == FIRST_PLAYER) {
        return 'X';
    } else {
        return 'O';
    }
}
/*
 * Function: GetUserMove
 * Usage: move = GetUserMove(state);
 * ---------------------------------
 * This function allows the user to enter a move and returns the
 * number of the chosen square. If the user specifies an illegal
 * move, this function gives the user the opportunity to enter
 * a legal one.
 */
moveT GetUserMove(stateT state) {
    cout << "Your move." << endl;
    moveT move;
    while (true) {
        cout << "What square? ";
        move = GetInteger();
        if (MoveIsLegal(move, state)) break;
        cout << "That move is illegal. Try again." << endl;
    }
    return move;
}
/*
 * Function: ChooseComputerMove
 * Usage: move = ChooseComputerMove(state);
 * ----------------------------------------
 * This function chooses the computer's move and is primarily
 * a wrapper for FindBestMove. This function also makes it
 * possible to display any game-specific messages that need
 * to appear at the beginning of the computer's turn. The
 * rating value returned by FindBestMove is simply discarded.
 */
moveT ChooseComputerMove(stateT state) {
    int rating;
    cout << "My move." << endl;
    return FindBestMove(state, 0, rating);
}
/*
 * Function: GenerateMoveList
 * Usage: GenerateMoveList(state, moveList);
 * -----------------------------------------
 * This function generates a list of the legal moves available in
 * the specified state. The list of moves is returned in the
 * vector moveList, which must be allocated by the client.
 */
void GenerateMoveList(stateT state, Vector<moveT> & moveList) {
    for (int i = 1; i <= 9; i++) {
        moveT move = moveT(i);
        if (MoveIsLegal(move, state)) {
            moveList.add(moveT(i));
        }
    }
}
/*
 * Function: MoveIsLegal
 * Usage: if (MoveIsLegal(move, state)) . . .
 * ------------------------------------------
 * This function returns true if the specified move is legal.
 */
bool MoveIsLegal(moveT move, stateT state) {
    if (move < 1 || move > 9) return false;
    int row = (move - 1) / 3;
    int col = (move - 1) % 3;
    return state.board(row, col) == ' ';
}
/*
 * Function: MakeMove
 * Usage: MakeMove(state, move);
 * -----------------------------
 * This function changes the state by making the indicated move.
 */
void MakeMove(stateT & state, moveT move) {
    int row = (move - 1) / 3;
    int col = (move - 1) % 3;
    state.board(row, col) = PlayerMark(state.whoseTurn);
    state.whoseTurn = Opponent(state.whoseTurn);
    state.turnsTaken++;
}
/*
 * Function: RetractMove
 * Usage: RetractMove(state, move);
 * --------------------------------
 * This function changes the state by "unmaking" the indicated move.
 */
void RetractMove(stateT & state, moveT move) {
    int row = (move - 1) / 3;
    int col = (move - 1) % 3;
    state.board(row, col) = ' ';
    state.whoseTurn = Opponent(state.whoseTurn);
    state.turnsTaken--;
}
/*
 * Function: GameIsOver
 * Usage: if (GameIsOver(state)) . . .
 * -----------------------------------
 * This function returns true if the game is complete.
 */
bool GameIsOver(stateT state) {
    return (state.turnsTaken == 9
            || CheckForWin(state, state.whoseTurn)
            || CheckForWin(state, Opponent(state.whoseTurn)));
}
/*
 * Function: AnnounceResult
 * Usage: AnnounceResult(state);
 * -----------------------------
 * This function announces the result of the game.
 */
void AnnounceResult(stateT state) {
    DisplayGame(state);
    if (CheckForWin(state, Human)) {
        cout << "You win." << endl;
    } else if (CheckForWin(state, Computer)) {
        cout << "I win." << endl;
    } else {
        cout << "Cat's game." << endl;
    }
}
/*
 * Function: WhoseTurn
 * Usage: player = WhoseTurn(state);
 * ---------------------------------
 * This function returns whose turn it is, given the current
 * state of the game. The reason for making this a separate
 * function is to ensure that the common parts of the code do
 * not need to refer to the internal components of the state.
 */
playerT WhoseTurn(stateT state) {
    return state.whoseTurn;
}
/*
 * Function: Opponent
 * Usage: opp = Opponent(player);
 * ------------------------------
 * This function returns the playerT value corresponding to the
 * opponent of the specified player.
 */
playerT Opponent(playerT player) {
    return (player == Human) ? Computer : Human;
}
/*
 * Function: EvaluateStaticPosition
 * Usage: rating = EvaluateStaticPosition(state);
 * ----------------------------------------------
 * This function gives the rating of a position without looking
 * ahead any further in the game tree. Although this function
 * duplicates much of the computation of GameIsOver and therefore
 * introduces some runtime inefficiency, it makes the algorithm
 * somewhat easier to follow.
 */
int EvaluateStaticPosition(stateT state) {
    if (CheckForWin(state, state.whoseTurn)) {
        return WINNING_POSITION;
    }
    if (CheckForWin(state, Opponent(state.whoseTurn))) {
        return LOSING_POSITION;
    }
    return NEUTRAL_POSITION;
}
/*
 * Function: CheckForWin
 * Usage: if (CheckForWin(state, player)) . . .
 * --------------------------------------------
 * This function returns true if the specified player has won
 * the game. The check on turnsTaken increases efficiency,
 * because neither player can win the game until the fifth move.
 */
bool CheckForWin(stateT state, playerT player) {
    if (state.turnsTaken < 5) return false;
    return CheckForWin(state.board, PlayerMark(player));
}
/*
 * Checks to see whether the specified player identified by mark
 * ('X' or 'O') has won the game. To reduce the number of special
 * cases, this implementation uses the helper function CheckLine
 * so that the row, column, and diagonal checks are the same.
 */
bool CheckForWin(Grid<char> & board, char mark) {
    for (int i = 0; i < 3; i++) {
        if (CheckLine(board, mark, i, 0, 0, 1)) return true;
        if (CheckLine(board, mark, 0, i, 1, 0)) return true;
    }
    if (CheckLine(board, mark, 0, 0, 1, 1)) return true;
    return CheckLine(board, mark, 2, 0, -1, 1);
}
/*
 * Checks a line extending across the board in some direction.
 * The starting coordinates are given by the row and col
 * parameters. The direction of motion is specified by dRow
 * and dCol, which show how to adjust the row and col values
 * on each cycle. For rows, dRow is always 0; for columns,
 * dCol is 0. For diagonals, the dRow and dCol values will
 * be +1 or -1 depending on the direction of the diagonal.
 */
bool CheckLine(Grid<char> & board, char mark, int row, int col,
               int dRow, int dCol) {
    for (int i = 0; i < 3; i++) {
        if (board(row, col) != mark) return false;
        row += dRow;
        col += dCol;
    }
    return true;
}
