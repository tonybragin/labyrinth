//
//  main.cpp
//  labyrinth
//
//  Created by TONY on 18/10/2017.
//  Copyright © 2017 TONY COMPANY. All rights reserved.
//
#include "header.hpp"
#include "labyrinthController.hpp"
#include "labyrinthModel.hpp"
#include "labyrinthView.hpp"

int main(int argc, const char * argv[]) {
    
    random_device rand;
    labyModel lModel;
    labyView lView;
    labyController lController (&lModel, &lView);
    
    lController.runGame();
    
    return 0;
}
