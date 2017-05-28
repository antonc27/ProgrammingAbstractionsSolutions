//
//  Problem4_ListCompletions.cpp
//  Assignment3
//
//  Created by AC27 on 28/03/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem4_ListCompletions.h"
#include <iostream>
#include "simpio.h"
#include "map.h"
#include "vector.h"
#include "lexicon.h"

void CompleteWordRec(string str, Lexicon &lex) {
    if (!lex.containsPrefix(str)) {
        return;
    }
    if (lex.containsWord(str)) {
        cout << str << endl;
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        CompleteWordRec(str + c, lex);
    }
}

void ListMnemonicsRec(string str, string out, Map<string> &dict, Lexicon &lex) {
    if (str.length() == 0) {
        CompleteWordRec(out, lex);
        return;
    }
    string s = str.substr(0, 1);
    string value = dict[s];
    for (int i = 0; i < value.length(); i++) {
        ListMnemonicsRec(str.substr(1), out + value.substr(i, 1), dict, lex);
    }
}

Map<string> getMnemonicsDict() {
    Map<string> dict;
    dict.add("2", "ABC");
    dict.add("3", "DEF");
    dict.add("4", "GHI");
    dict.add("5", "JKL");
    dict.add("6", "MNO");
    dict.add("7", "PQRS");
    dict.add("8", "TUV");
    dict.add("9", "WXYZ");
    return dict;
}

void printMap(string key, Vector<string> value) {
    cout << key << " -> ";
    for (int i = 0; i < value.size(); i++)
        cout << value[i];
    cout << endl;
}

void ListCompletions(string digitSequence, Lexicon &lex) {
    Map<string> dict = getMnemonicsDict();
    ListMnemonicsRec(digitSequence, "", dict, lex);
}

int Problem4_ListCompletions_main() {
    
    Lexicon lex("./Assignment3.app/Contents/Resources/lexicon.dat");
    
    ListCompletions("72547", lex);
//    ListCompletions("9956", lex);
    return 0;
}
