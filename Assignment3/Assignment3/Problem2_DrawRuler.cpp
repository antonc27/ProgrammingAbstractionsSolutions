//
//  Problem2_DrawRuler.cpp
//  Assignment3
//
//  Created by AC27 on 18/03/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem2_DrawRuler.h"
#include "graphics.h"
#include "extgraph.h"
#include "simpio.h"

void DrawRuler(double x, double y, double w, double h) {
    if (h < 0.1) {
        return;
    }
    
    double halfW = w/2;
    double halfH = h/2;
    
    MovePen(x, y);
    DrawLine(w, 0);
    
    MovePen(x + halfW, y);
    DrawLine(0, halfH);
    
    DrawRuler(x, y, halfW, halfH);
    DrawRuler(x + halfW, y, halfW, halfH);
}

int Problem2_DrawRuler_main() {
    InitGraphics();
    SetPenColor("Blue");
    double w = GetWindowWidth();
    double h = GetWindowHeight();
    double marginW = w/10;
    double marginH = h/10;
    DrawRuler(marginW, marginH, w-2*marginW, h-2*marginH);
    SetWindowTitle("DrawRuler");
    return 0;
}
