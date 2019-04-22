//
//  Computer.h
//  Project3Computer
//
//  Created by Katie Fairbanks on 3/30/18.
//  Copyright © 2018 Katie Fairbanks. All rights reserved.
//

#ifndef Computer_h
#define Computer_h

#include <vector>
#include <stdio.h>
#include "MinimaxTree.h"

class Computer {
private:
    std::vector<std::vector<std::vector<char> > > board;
    MinimaxTree * tree;
public:
    Computer(std::vector<std::vector<std::vector<char> > > b);
    int pointToIndex(std::vector<int> v);
    void update(std::vector<int> move);
    int computerMove();
};


#endif /* Computer_h */
