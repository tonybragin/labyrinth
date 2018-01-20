//
//  labyrinthController.hpp
//  labyrinth
//
//  Created by TONY on 18/10/2017.
//  Copyright © 2017 TONY COMPANY. All rights reserved.
//

#ifndef labyrinthController_hpp
#define labyrinthController_hpp

#include "header.hpp"

class labyController {
public:
    
    labyController(labyModel *, labyView *);
    void runGame();
    
private:
    
    void prepareForShowStep();
    int getDirID (char);
    bool getStart();
    void getStep();
    void lastInfo();
    
    labyModel *_model;
    labyView *_view;
};

#endif /* labyrinthController_hpp */
