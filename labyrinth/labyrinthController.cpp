//
//  labyrinthController.cpp
//  labyrinth
//
//  Created by TONY on 18/10/2017.
//  Copyright © 2017 TONY COMPANY. All rights reserved.
//

#include "header.hpp"
#include "labyrinthController.hpp"
#include "labyrinthModel.hpp"
#include "labyrinthView.hpp"

labyController::labyController(labyModel *model, labyView *view) {
    _model = model;
    _view = view;
}

bool labyController::getStart() {
    int rooms;
    
    cin >> rooms;
    if (rooms <= 5) return 0;
    
    _model->setRooms(rooms);
    
    return 1;
}

int labyController::getDirID(char dir) {
    switch (dir) {
        case 'N': {
            return 0;
            break;
        }
        case 'S': {
            return 1;
            break;
        }
        case 'W': {
            return 2;
            break;
        }
        case 'E': {
            return 3;
            break;
        }
            
        default:
            return -1;
            break;
    }
}

void labyController::getStep() {
    string comm, value;

    cin >> comm >> value;
    
    if (comm.compare("go") == 0) {
        char dir = value[0];
        if (dir == 'N' || dir == 'S' || dir == 'W' || dir == 'E') {
            int dirID = getDirID(dir);
            
            if (_model->per->nodeStep->directionLink[dirID] != NULL) {
                _model->per->nodeStep = _model->per->nodeStep->directionLink[dirID];
            } else {
                _view->showErrorMes("Wrong direction");
                prepareForShowStep();
                getStep();
                return;
            }
            
        } else if (value.compare("back") == 0) {
            if (_model->per->nodeStep->back != NULL) {
                _model->per->nodeStep = _model->per->nodeStep->back;
            } else {
                _view->showErrorMes("Wrong direction");
                prepareForShowStep();
                getStep();
                return;
            }
        } else {
            _view->showErrorMes("Wrong value");
            prepareForShowStep();
            getStep();
            return;
        }
        //go
    } else if (comm.compare("get") == 0) {
        if (_model->isDark()) {
            _view->showErrorMes("Can’t see anything in this dark place!");
            prepareForShowStep();
            getStep();
            return;
        }
            
        if (value.compare("key") == 0) {
            if (_model->per->nodeStep->inventory[0] == 1) {
                _model->per->inventory[0] = 1;
                _model->per->nodeStep->inventory[0] = 0;
            } else {
                _view->showErrorMes("No key here");
                prepareForShowStep();
                getStep();
                return;
            }
            
            //key
        } else if (value.compare("torchlight") == 0) {
            if (_model->per->nodeStep->inventory[1] > 0) {
                _model->per->inventory[1]++;
                _model->per->nodeStep->inventory[1]--;
            } else {
                _view->showErrorMes("No torchlight here");
                prepareForShowStep();
                getStep();
                return;
            }
            
            //torchlight
        } else if (value.compare("apple") == 0) {
            if (_model->per->nodeStep->inventory[2] > 0) {
                _model->per->inventory[2]++;
                _model->per->nodeStep->inventory[2]--;
            } else {
                _view->showErrorMes("No apple here");
                prepareForShowStep();
                getStep();
                return;
            }
            
            //apple
        } else {
            _view->showErrorMes("Wrong value");
            prepareForShowStep();
            getStep();
            return;
            //else
        }
        
        //get
    } else if (comm.compare("drop") == 0) {
        if (_model->isDark()) {
            _view->showErrorMes("Can’t see anything in this dark place!");
            prepareForShowStep();
            getStep();
            return;
        }
        
        if (value.compare("key") == 0) {
            if (_model->per->inventory[0] == 1) {
                _model->per->inventory[0] = 0;
                _model->per->nodeStep->inventory[0] = 1;
            } else {
                _view->showErrorMes("You dont have a key");
                prepareForShowStep();
                getStep();
                return;
            }
            
            //key
        } else if (value.compare("torchlight") == 0) {
            if (_model->per->inventory[1] > 0) {
                _model->per->inventory[1]--;
                _model->per->nodeStep->inventory[1]++;
            } else {
                _view->showErrorMes("You dont have a torchlight");
                prepareForShowStep();
                getStep();
                return;
            }
            
            //torchlight
        } else if (value.compare("apple") == 0) {
            if (_model->per->inventory[2] > 0) {
                _model->per->inventory[2]--;
                _model->per->nodeStep->inventory[2]++;
            } else {
                _view->showErrorMes("You dont have an apple");
                prepareForShowStep();
                getStep();
                return;
            }
            
            //apple
        } else {
            _view->showErrorMes("Wrong value");
            prepareForShowStep();
            getStep();
            return;
            //else
        }
        
        //drop
    } else if (comm.compare("open") == 0) {
        if (_model->isDark()) {
            _view->showErrorMes("Can’t see anything in this dark place!");
            prepareForShowStep();
            getStep();
            return;
        }
        
        if (value.compare("chest") != 0) {
            _view->showErrorMes("Wrong value");
            prepareForShowStep();
            getStep();
            return;
        }
        
        if (_model->per->nodeStep->inventory[3] == 0) {
            _view->showErrorMes("No chest here");
            prepareForShowStep();
            getStep();
            return;
        }
        if (_model->per->inventory[1] == 0) {
            _view->showErrorMes("You dont have a key");
            prepareForShowStep();
            getStep();
            return;
        }
        
        _model->Win();
            
        //open
    } else if (comm.compare("eat") == 0) {
        if (_model->isDark()) {
            _view->showErrorMes("Can’t see anything in this dark place!");
            prepareForShowStep();
            getStep();
            return;
        }
        
        if (value.compare("apple") != 0) {
            _view->showErrorMes("Wrong value");
            prepareForShowStep();
            getStep();
            return;
        }
        
        if (_model->per->inventory[2] > 0) {
            _model->per->inventory[2]--;
            _model->per->stepsHave += 10;
        } else {
            _view->showErrorMes("You dont have an apple");
            prepareForShowStep();
            getStep();
            return;
        }
        
        //else
    } else {
        _view->showErrorMes("Wrong command");
        prepareForShowStep();
        getStep();
        return;
    }
}

void labyController::prepareForShowStep() {
    char dir[4];
    
    for(int i = 0; i < 4; i++) {
        if (_model->per->nodeStep->directionLink[i] != NULL) {
            
            dir[i] = _model->directions[i];
            
        } else dir[i] = '_';
    }
    
    if (!_model->isDark()) {
        
        _view->showStep(_model->per->nodeStep->coordinateX, _model->per->nodeStep->coordinateY, _model->per->nodeStep->doors, dir, _model->per->nodeStep->inventory, _model->allItems);
        _view->showStepMes();
        
    } else {
        _view->showDarkStep(_model->per->nodeStep->coordinateX, _model->per->nodeStep->coordinateY, _model->per->nodeStep->doors, dir);
        _view->showDarkStepMes();
    }
}

void labyController::lastInfo() {
    _view->showLastInfo(_model->per->stepsDone);
}

void labyController::runGame() {

    //start
    int fStart = 0;
    while (fStart == 0) {
        _view->showStart();
        fStart = getStart();
    }
    _model->setLabyrinth();
    
    _model->initPerson();
    
    int win = 0, lose = 0;
    
    while (1) {
        prepareForShowStep();
        getStep();
        _model->stepsCount();
        
        win = _model->isWin();
        lose = _model->isLose();
        if (win == 1) break;
        if (lose == 1) break;
    }
    
    if (win == 1) _view->showWinMes();
    if (lose == 1) _view->showLoseMes();
    
    lastInfo();
}
