//
//  labyrinthView.hpp
//  labyrinth
//
//  Created by TONY on 18/10/2017.
//  Copyright © 2017 TONY COMPANY. All rights reserved.
//

#ifndef labyrinthView_hpp
#define labyrinthView_hpp

#include "header.hpp"

class labyView {
public:
    
    friend labyController;
    
private:
    
    void showStart();
    void showDarkStep(int, int, int, char *);
    void showStep(int, int, int, char *, int *, string *);
    void showDarkStepMes();
    void showStepMes();
    void showWinMes();
    void showLoseMes();
    void showErrorMes(string);
    void showLastInfo(int);
};

#endif /* labyrinthView_hpp */
