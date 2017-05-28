/* File: boggle.cpp
 * ----------------
 * Your name here!
 */
 
#include "genlib.h"
#include "simpio.h"
#include <iostream>
#include "extgraph.h"
#include "gboggle.h"
#include "grid.h"
#include "random.h"
#include "lexicon.h"
#include "set.h"
#include "vector.h"

int STANDARD_BOARD_SIZE = 4;
int BIG_BOARD_SIZE = 5;

string StandardCubes[16]  =
{"AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS", "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
 "DISTTY", "EEGHNW", "EEINSU", "EHRTVW", "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"};
 
string BigBoggleCubes[25]  = 
{"AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM", "AEEGMU", "AEGMNN", "AFIRSY", 
"BJKQXZ", "CCNSTW", "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT", "DHHLOR", 
"DHLNOR", "EIIITT", "EMOTTT", "ENSSSU", "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"};

void GiveInstructions()
{
    cout << endl << "The boggle board is a grid onto which I will randomly distribute " 
	 << "cubes. These 6-sided cubes have letters rather than numbers on the faces, " 
	 << "creating a grid of letters on which you try to form words. You go first, " 
	 << "entering all the words you can find that are formed by tracing adjoining " 
	 << "letters. Two letters adjoin if they are next to each other horizontally, " 
	 << "vertically, or diagonally. A letter can only be used once in the word. Words "
	 << "must be at least 4 letters long and can only be counted once. You score points "
	 << "based on word length: a 4-letter word is worth 1 point, 5-letters earn 2 "
	 << "points, and so on. After your puny brain is exhausted, I, the super computer, "
	 << "will find all the remaining words and double or triple your paltry score." << endl;
	
    cout << "\nHit return when you're ready...";
    GetLine();
}

static void Welcome()
{
    cout << "Welcome!  You're about to play an intense game of mind-numbing Boggle. " 
	 << "The good news is that you might improve your vocabulary a bit.  The "
	 << "bad news is that you're probably going to lose miserably to this little "
	 << "dictionary-toting hunk of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

void InitLexicon(Lexicon &lex) {
    lex = *new Lexicon("./Assignment4.app/Contents/Resources/lexicon.dat");
}

bool GetAnswerForQuestion(string question) {
    while (true) {
        cout << question;
        string answer = ConvertToLowerCase(GetLine());
        if (answer == "yes") {
            return true;
        } else if (answer == "no") {
            return false;
        } else {
            cout << "Please answer YES or NO" << endl;
        }
    }
}

int GetBoardSize() {
    cout << endl << "You can choose standard Boggle (4x4 grid) or Big Boggle (5x5)." << endl;
    if (GetAnswerForQuestion("Would you like Big Boggle? ")) {
        return BIG_BOARD_SIZE;
    } else {
        return STANDARD_BOARD_SIZE;
    }
}

bool IsNeedToForceConfig() {
    cout << endl << "I'll give you a chance to set up the board to your specification, which makes it easier to confirm your boggle program is working." << endl;
    return GetAnswerForQuestion("Do you want to force the board configuration? ");
}

string GetConfigFromUser(int configStringSize) {
    while (true) {
        cout << "Enter the string: ";
        string str = GetLine();
        if (str.length() >= configStringSize) {
            return str.substr(0, configStringSize);
        } else {
            cout << "String must include " << configStringSize << " characters! Try again." << endl;
        }
    }
}

void ForceConfigFromUser(Grid<char> &board, int boardSize) {
    int stringSize = boardSize*boardSize;
    cout << endl << "Enter a " << stringSize << "-character string to identify which letters you want on the cubes.  The first " << boardSize << " letters are the cubes on the top row from left to right, the next " << boardSize << " letters are the second row, and so on." << endl;
    
//    string config = "EECAALEPHNBOQTTY";
    string config = GetConfigFromUser(stringSize);
    
    for (int row = 0; row < boardSize; row++) {
        for (int col = 0; col < boardSize; col++) {
            board(row, col) = config[row * boardSize + col];
        }
    }
}

void SwapCubies(string cubies[], int boardSize, int rowX, int colX, int rowY, int colY) {
    int xPos = rowX * boardSize + colX;
    int yPos = rowY * boardSize + colY;
    
    string tmp = cubies[xPos];
    cubies[xPos] = cubies[yPos];
    cubies[yPos] = tmp;
}

void ShuffleBoard(Grid<char> &board, int boardSize) {
    string *cubies = (boardSize == STANDARD_BOARD_SIZE) ? StandardCubes : BigBoggleCubes;
    for (int row = 0; row < boardSize; row++) {
        for (int col = 0; col < boardSize; col++) {
            int randomRow = RandomInteger(row, boardSize-1);
            int randomCol = RandomInteger(col, boardSize-1);
            SwapCubies(cubies, boardSize, row, col, randomRow, randomCol);
            
            string cube = cubies[row * boardSize + col];
            int randomSide = RandomInteger(0, 5);
            board(row, col) = cube[randomSide];
        }
    }
}

void DrawBoggleBoard(Grid<char> &board, int boardSize) {
    for (int row = 0; row < boardSize; row++) {
        for (int col = 0; col < boardSize; col++) {
            LabelCube(row, col, board(row, col));
        }
    }
}

struct pointT {
    int row;
    int col;
};

bool ContainsPosition(Vector<pointT> &positions, pointT pos) {
    for (int i = 0; i < positions.size(); i++) {
        pointT p = positions[i];
        if (pos.col == p.col && pos.row == p.row) {
            return true;
        }
    }
    
    return false;
}

bool IsInBounds(pointT currentPos, Grid<char> &board) {
    return !(currentPos.col < 0 || currentPos.col >= board.numCols() || currentPos.row < 0 || currentPos.row >= board.numRows());
}

bool FindWordRecForHuman(Lexicon &lex, string word, string current, Grid<char> &board, Vector<pointT> &positions) {
    if (!lex.containsPrefix(current)) {
        return false;
    }
    if (current.size() > 0 && word.find(current) == string::npos) {
        return false;
    }
    if (word == current) {
        return true;
    }
    pointT currentPos = positions[positions.size() - 1];
    for (int p=-1; p<2; p++) {
        for (int q=-1; q<2; q++) {
            if (p == 0 && q == 0) {
                continue;
            }
            pointT nextPos = {currentPos.row + p, currentPos.col + q};
            if (!IsInBounds(nextPos, board) || ContainsPosition(positions, nextPos)) {
                continue;
            }
            string newCurrent = ConvertToLowerCase(current + board(nextPos.row, nextPos.col));
            Vector<pointT> newPostions = positions;
            newPostions.add(nextPos);
            if (FindWordRecForHuman(lex, word, newCurrent, board, newPostions)) {
                positions = newPostions;
                return true;
            }
        }
    }
    
    return false;
}

void HighlightPositions(Vector<pointT> &positions, bool flag) {
    for (int i=0; i<positions.size(); i++) {
        pointT pos = positions[i];
        HighlightCube(pos.row, pos.col, flag);
    }
}

void BlinkPositions(Vector<pointT> &positions) {
    HighlightPositions(positions, true);
    Pause(0.3);
    HighlightPositions(positions, false);
}

bool FindWordForHuman(Lexicon &lex, string word, Grid<char> &board) {
    for (int row = 0; row < board.numRows(); row++) {
        for (int col = 0; col < board.numCols(); col++) {
            Vector<pointT> positions;
            pointT start = {row, col};
            positions.add(start);
            string str = "";
            str += board(row, col);
            str = ConvertToLowerCase(str);
            bool isFound = FindWordRecForHuman(lex, word, str, board, positions);
            if (isFound) {
                BlinkPositions(positions);
                return true;
            }
        }
    }
    
    return false;
}

void HumanTurn(Lexicon &lex, Grid<char> &board, Set<string> &humanFoundWords) {
    cout << endl << "Ok, take all the time you want and find all the words you can!  Signal that you're finished by entering an empty line." << endl;
    
    while (true) {
        cout << "Enter a word: ";
        string word = ConvertToLowerCase(GetLine());
        if (word == "") {
            break;
        } else if (word.length() < 4) {
            cout << "I'm sorry, but we have our standards. \nThat word doesn't meet the minimum word length." << endl;
        } else if (!lex.containsWord(word)) {
            cout << "You can't make that word!" << endl;
        } else if (humanFoundWords.contains(word)) {
            cout << "You've already guessed that!" << endl;
        } else if (!FindWordForHuman(lex, word, board)) {
            cout << "You can't make that word!" << endl;
        } else {
            humanFoundWords.add(word);
            RecordWordForPlayer(word, Human);
        }
    }
}

void FindWordRecForComputer(Lexicon &lex, string current, Grid<char> &board, Vector<pointT> &positions, Set<string> &foundWords) {
    if (!lex.containsPrefix(current)) {
        return;
    } else {
        if (current.length() >= 4 && lex.containsWord(current) && !foundWords.contains(current)) {
            foundWords.add(current);
            RecordWordForPlayer(current, Computer);
        }
    }
    pointT currentPos = positions[positions.size() - 1];
    for (int p=-1; p<2; p++) {
        for (int q=-1; q<2; q++) {
            if (p == 0 && q == 0) {
                continue;
            }
            pointT nextPos = {currentPos.row + p, currentPos.col + q};
            if (!IsInBounds(nextPos, board) || ContainsPosition(positions, nextPos)) {
                continue;
            }
            string newCurrent = ConvertToLowerCase(current + board(nextPos.row, nextPos.col));
            Vector<pointT> newPostions = positions;
            newPostions.add(nextPos);
            
            FindWordRecForComputer(lex, newCurrent, board, newPostions, foundWords);
        }
    }
}

void ComputerTurn(Lexicon &lex, Grid<char> &board, Set<string> &foundWords) {
    for (int row = 0; row < board.numRows(); row++) {
        for (int col = 0; col < board.numCols(); col++) {
            Vector<pointT> positions;
            pointT start = {row, col};
            positions.add(start);
            string str = "";
            str += board(row, col);
            str = ConvertToLowerCase(str);
            FindWordRecForComputer(lex, str, board, positions, foundWords);
        }
    }
}

bool WantPlayAgain() {
    return GetAnswerForQuestion("Would you like to play again? ");
}

int main()
{
    Randomize();
	SetWindowSize(9, 5);
	InitGraphics();
	Welcome();
	GiveInstructions();
    
    Lexicon lex;
    InitLexicon(lex);
    
    int boardSize = GetBoardSize();
    Grid<char> board(boardSize, boardSize);
    
    while (true) {
        InitGraphics();
        DrawBoard(boardSize, boardSize);
        
        if (IsNeedToForceConfig()) {
            ForceConfigFromUser(board, boardSize);
        } else {
            ShuffleBoard(board, boardSize);
        }
        DrawBoggleBoard(board, boardSize);
        
        Set<string> humanFoundWords;
        HumanTurn(lex, board, humanFoundWords);
        
        ComputerTurn(lex, board, humanFoundWords);
        
        if (!WantPlayAgain()) {
            break;
        }
    }
    
	return 0;
}
