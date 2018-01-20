//
//  labyrinthModel.cpp
//  labyrinth
//
//  Created by TONY on 18/10/2017.
//  Copyright © 2017 TONY COMPANY. All rights reserved.
//

#include "header.hpp"
#include "labyrinthModel.hpp"

labyModel::labyModel() {
    
    win = 0;
    
    directions[0] = 'N';
    directions[1] = 'S';
    directions[2] = 'W';
    directions[3] = 'E';
    
    allItems[0] = "key";
    allItems[1] = "torchlight";
    allItems[2] = "apple";
    allItems[3] = "chest";
    
    per = new person;
    start = new room;
}

void labyModel::setRooms(int setrooms) {
    rooms = setrooms;
    roomsConst = setrooms;
}

void labyModel::initPerson() {
    per->nodeStep = start;
    per->stepsDone = 0;
    per->stepsHave = roomsConst * 2;
    
}

void labyModel::changeXY(int fromDirection, int *x, int *y) {
    switch (fromDirection) {
        case 0: {
            *y = *y + 1;
            break;
        }
        case 1: {
            *y = *y - 1;
            break;
        }
        case 2: {
            *x = *x - 1;
            break;
        }
        case 3: {
            *x = *x + 1;
            break;
        }
        default:
            break;
    }
}

int labyModel::howManyDoors(int x, int y) {
    int randNum = 3;
    if (x - 1 < 0) randNum--;
    if (y - 1 < 0) randNum--;
    
    if (rooms == 0) return 0;
    if (randNum > rooms && rooms > 0) randNum = rooms;
    
    return rand() % randNum + 1;
}

//fix
void labyModel::addRoom(room *root) {
    
    int localDoors = root->doors;
    
    for (int i = rand() % 4; localDoors > 0; i = (i + 1) % 4) {
        
        int x = root->coordinateX, y = root->coordinateY;
        changeXY(i, &x, &y);
        
        if (x < 0 || y < 0) continue;
        if (root != start) {
            if (root->back->coordinateX == x && root->back->coordinateY == y) {
                continue;
            }
        }
        
        room *node = new room;
        node->coordinateX = x;
        node->coordinateY = y;
        node->back = root;
        node->doors = howManyDoors(x, y);
        rooms -= node->doors;
        
        for (int i = 0; i < 4; i++) {
            node->directionLink[i] = NULL;
        }
        
        root->directionLink[i] = node;
        
        addRoom(node);
        localDoors--;
    }
}

void labyModel::initStart() {
    start->coordinateX = 0;
    start->coordinateY = 0;
    
    start->doors = rand() % 2 + 1;
    
    for (int i = 0; i < 4; i++) {
        start->directionLink[i] = NULL;
    }
    
    if (start->doors == 2) {
        rooms -= 2;
    } else {
        rooms--;
    }
}

void labyModel::initItems() {
    for (int i = 0; i < 4; i++) {
        if (i == 0 || i == 3) {
            howManyItems[i] = 1;
        } else {
            howManyItems[i] = rand() % 5 + 1;
        }
    }
    
}

void labyModel::addInventory() {
    
    for (int in = 0; in < 4;) {
        
        int randSteps = rand() % roomsConst;
    
        room *node = start;
        for (int i = 0; i < randSteps && node->doors != 0;) {
            for (int j = rand() % 4; node->doors != 0; j = (j + 1) % 4) {
                if (node->directionLink[j] != NULL) {
                    node = node->directionLink[j];
                    i++;
                    break;
                }
            }
        }
        node->inventory[in]++;
        
        howManyItems[in]--;
        if (howManyItems[in] == 0) in++;
    }
}

void labyModel::addDarkness() {
    for (int in = 0; in < rand() % 5; in++) {
        
        int randSteps = rand() % roomsConst;
        
        room *node = start;
        for (int i = 0; i < randSteps && node->doors != 0;) {
            for (int j = rand() % 4; node->doors != 0; j = (j + 1) % 4) {
                if (node->directionLink[j] != NULL) {
                    node = node->directionLink[j];
                    i++;
                    break;
                }
            }
        }
        node->darkness = 1;
    }
    
}

void labyModel::stepsCount() {
    per->stepsDone++;
}

bool labyModel::isLose() {
    if (per->stepsDone >= per->stepsHave) return 1;
    else return 0;
}

void labyModel::Win() {
    win = 1;
}

bool labyModel::isWin() {
    return win;
}

bool labyModel::isDark() {
    if (per->nodeStep->darkness == 1 && per->nodeStep->inventory[1] == 0 && per->inventory[1] == 0) return 1;
    else return 0;
}

void labyModel::setLabyrinth() {
    initStart();
    addRoom(start);
    
    initItems();
    addInventory();
    
    addDarkness();
}
