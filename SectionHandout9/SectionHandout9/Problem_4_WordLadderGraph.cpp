//
//  Problem_4_WordLadderGraph.cpp
//  SectionHandout9
//
//  Created by AC27 on 04/09/2017.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem_4_WordLadderGraph.h"
#include "graph_utils.h"
#include "lexicon.h"

void PrintWord(string word, int &count) {
    count++;
    cout << word << endl;
}

int Problem_4_WordLadderGraph_main() {
    Lexicon lex;
    lex.add("cake");
    lex.add("came");
    lex.add("camp");
    lex.add("damp");
    lex.add("dame");
    lex.add("dime");
    lex.add("dike");
    lex.add("like");
    lex.add("lake");
    lex.add("lame");
    lex.add("lamp");
    lex.add("limp");
    lex.add("lime");
    
    int count = 0;
    lex.mapAll(PrintWord, count);
    
    cout << count << endl;
    
    return 0;
}