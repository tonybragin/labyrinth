//
//  labyrinthView.cpp
//  labyrinth
//
//  Created by TONY on 18/10/2017.
//  Copyright © 2017 TONY COMPANY. All rights reserved.
//

#include "header.hpp"
#include "labyrinthView.hpp"

//MARK: VIEW METHODS
void labyView::showStart() {
    cout << "Write count of rooms (must be > 5): " << endl;
}

void labyView::showDarkStep(int x, int y, int doors, char *dir) {
    //room
    cout << "\nYou are in the room [" << x << ", " << y << "]. ";
    
    //doors
    if (doors != 0) {
        cout << "There are " << doors << " doors: ";
        for(int i = 0; i < 4; i++) {
            cout << dir[i];
        }
    } else cout << "There are only back door ";
    
    cout << ". Can’t see anything in this dark place!" << endl;
}

void labyView::showStep(int x, int y, int doors, char *dir, int *invent, string *allItems) {
    //room
    cout << "\nYou are in the room [" << x << ", " << y << "]. ";
    
    //doors
    if (doors != 0) {
        cout << "There are " << doors << " doors: ";
        for(int i = 0; i < 4; i++) {
            cout << dir[i];
        }
    } else cout << "There are only back door";
    
    //items
    cout << ". Items in the room:";
    int f = 0;
    for(int i = 0; i < 4; i++) {
        if (invent[i] > 0) {
            cout << " " << allItems[i];
            f = 1;
        }
    }
    if (f == 0) cout << " none";
    cout << ". " << endl;
}

void labyView::showDarkStepMes() {
    cout << "Write command (go [N, S, W, E, back]): \n";
}

void labyView::showStepMes() {
    cout << "Write command (go [N, S, W, E, back] / get [key, torchlight, apple] / drop [key, torchlight, apple] / open chest / eat apple): \n";
}

void labyView::showErrorMes(string messege) {
    cout << "\n!!!" << messege << "\n\n";
}

void labyView::showWinMes() {
    cout << "!!! You're WIN !!!" << endl;
}

void labyView::showLoseMes() {
    cout << "You're lose" << endl;
}

void labyView::showLastInfo(int steps) {
    cout << "You've done " << steps << " steps" << endl;
    
}
