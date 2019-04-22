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
    MinimaxTree * tree;
public:
    Computer();
	std::vector<std::vector<std::vector<char> > > board;
    int pointToIndex(std::vector<int> v);
    void update(std::vector<int> move, char humanChar);
    int computerMove(char humanChar);

	int test = 5;
};


#endif /* Computer_h */
