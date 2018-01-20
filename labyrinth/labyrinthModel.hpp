//
//  labyrinthModel.hpp
//  labyrinth
//
//  Created by TONY on 18/10/2017.
//  Copyright © 2017 TONY COMPANY. All rights reserved.
//

#ifndef labyrinthModel_hpp
#define labyrinthModel_hpp

#include "header.hpp"

class labyModel {
public:
    
    friend labyController;
    
    labyModel();
    
private:
    
    char directions[4];
    string allItems[4];
    int howManyItems[4] = {0};
    
    struct room {
        int coordinateX;
        int coordinateY;
        int inventory[4] = {0};
        int doors;
        room *back = NULL;
        room *directionLink[4];
        int darkness = 0;
    };
    
    struct person {
        room *nodeStep;
        int inventory[3] = {0};
        int stepsDone;
        int stepsHave;
    };
    
    int rooms;
    int roomsConst;
    int win;
    
    person *per;
    room *start;
    
    void initPerson();
    void stepsCount();
    void Win();
    bool isWin();
    bool isLose();
    bool isDark();

    
    void setRooms(int);
    void changeXY(int, int*, int*);
    int howManyDoors(int, int);
    void initStart();
    void addRoom(room*);
    void initItems();
    void addInventory();
    void addDarkness();
    void setLabyrinth();
};

#endif /* labyrinthModel_hpp */
