//
//  Problem8_ListMnemonics.cpp
//  SectionHandout3
//
//  Created by AC27 on 05/03/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem8_ListMnemonics.h"
#include <iostream>
#include "simpio.h"
#include "map.h"
#include "vector.h"

void ListMnemonicsRec(string str, string out, Map<string> &dict) {
    if (str.length() == 0) {
        cout << out << endl;
        return;
    }
    string s = str.substr(0, 1);
    string value = dict[s];
    for (int i = 0; i < value.length(); i++) {
        ListMnemonicsRec(str.substr(1), out + value.substr(i, 1), dict);
    }
}

Map<string> getMnemonicsDict() {
    Map<string> dict;
    dict.add("2", "ABC");
    dict.add("3", "DEF");
    dict.add("4", "GHI");
    dict.add("5", "JKL");
    dict.add("6", "MNO");
    dict.add("7", "PRS");
    dict.add("8", "TUV");
    dict.add("9", "WXY");
    return dict;
}

void printMap(string key, Vector<string> value) {
    cout << key << " -> ";
    for (int i = 0; i < value.size(); i++)
        cout << value[i];
    cout << endl;
}

void ListMnemonics(string str) {
    Map<string> dict = getMnemonicsDict();
    //    dict.mapAll(printMap);
    ListMnemonicsRec(str, "", dict);
}

int Problem8_ListMnemonics_main() {
    ListMnemonics("723");
    return 0;
}
