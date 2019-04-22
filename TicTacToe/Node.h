//
//  Node.h
//  Project3Computer
//
//  Created by Katie Fairbanks on 3/23/18.
//  Copyright © 2018 Katie Fairbanks. All rights reserved.
//

#ifndef Node_h
#define Node_h
#include <stdio.h>
#include <vector>

class Node {
private:
    int value;
    std::vector<int> Xs;
    std::vector<int> Os;
    Node *parent;
    std::vector<Node*> children;
    std::vector<std::vector<std::vector<char> > > board;
    std::vector<int> move;
    friend class MinimaxTree;
public:
    Node(Node *p = nullptr, std::vector<int> x = std::vector<int>(4),
         std::vector<int> o = std::vector<int>(4),
         std::vector<std::vector<std::vector<char> > > b = std::vector<std::vector<std::vector<char> > >(), std::vector<int> m = std::vector<int>(3), char player = 'X');
    ~Node();
    std::vector<int> getMove();
    std::vector<std::vector<std::vector<char> > > getBoard();
    std::vector<int> getXs();
    std::vector<int> getOs();
    int getValue();
    void setValue(int v);
    void setValue();
    void setParent(Node * n);
    Node * getParent();
    std::vector<Node*> getChildren();
    void addChild(Node* n);
    void eraseChild(int index);
};

#endif /* Node_h */
