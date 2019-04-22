//
//  MinimaxTree.h
//  Project3Computer
//
//  Created by Katie Fairbanks on 3/23/18.
//  Copyright © 2018 Katie Fairbanks. All rights reserved.
//

#ifndef MinimaxTree_h
#define MinimaxTree_h

#include <stdio.h>
#include <vector>
#include "Node.h"

class MinimaxTree {
private:
    Node * head;
public:
    MinimaxTree(std::vector<std::vector<std::vector<char> > > b);
    std::vector<int> getMove();
    void update(std::vector<int> lastMove, char player);
};

#endif /* MinimaxTree_h */
