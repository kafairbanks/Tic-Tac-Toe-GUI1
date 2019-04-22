//
//  MinimaxTree.cpp
//  Project3Computer
//
//  Created by Katie Fairbanks on 3/23/18.
//  Copyright © 2018 Katie Fairbanks. All rights reserved.
//

#include <vector>
#include <iostream>
#include "MinimaxTree.h"
#include "Node.h"
using namespace std;

const int INFINITY = 1000000;

MinimaxTree::MinimaxTree(vector<vector<vector<char> > > b){
    head = new Node(nullptr, vector<int>(4, 0), vector<int>(4, 0), b, vector<int>(3, 0), ' ');
    Node * currentNode = head;
    vector<int> move(3);
    
    for(int x=0; x<4; x++) {
        for(int y=0; y<4; y++) {
            for(int z=0; z<4; z++) {
                move.at(0) = x;
                move.at(1) = y;
                move.at(2) = z;
                head->addChild(new Node(head, head->getXs(), head->getOs(), head->getBoard(), move, 'X'));
            }
        }
    }
    
    Node * currentChild;
    for(int i=0; i<currentNode->getChildren().size(); i++) {
        currentChild = currentNode->getChildren().at(i);
        vector<vector<vector<char> > > currentBoard = currentChild->getBoard();
        
        for(int x=0; x<4; x++) {
            for(int y=0; y<4; y++) {
                for(int z=0; z<4; z++) {
                    if(currentBoard.at(x).at(y).at(z) == ' ') {
                        move.at(0) = x;
                        move.at(1) = y;
                        move.at(2) = z;
                        currentChild->addChild(new Node(currentChild, currentChild->getXs(),
                                                        currentChild->getOs(), currentBoard, move, 'O'));
                    }
                }
            }
        }
    }
}

vector<int> MinimaxTree::getMove() {
    int value = 0;
    int minValue = INFINITY;
    Node * minNode = head;
    
    Node * currentNode = head;
    vector<Node*> children = head->getChildren();
    
    for(int i=0; i < children.size(); i++) {
        currentNode = children.at(i);
        minValue = INFINITY;
        vector<Node*> children2 = currentNode->getChildren();
        for(int j=0; j < children2.size(); j++) {
            value = children2.at(j)->getValue();
            if(value < minValue) minValue = value;
        }
        currentNode->setValue(minValue);
    }
    
    minValue = INFINITY;
    for(int i=0; i < children.size(); i++) {
        if(children.at(i)->getValue() < minValue) {
            minValue = children.at(i)->getValue();
            minNode = children.at(i);
        }
    }
    
    return minNode->getMove();
}

void MinimaxTree::update(vector<int> lastMove, char player) {
    vector<Node*> children = head->getChildren();
    Node * lastHead = head;
    
    for(int i=0; i<children.size(); i++) {
        vector<int> currentMove = children.at(i)->getMove();
        if(currentMove.at(0) == lastMove.at(0) && currentMove.at(1) == lastMove.at(1) &&
           currentMove.at(2) == lastMove.at(2)) {
            head = children.at(i);
            lastHead->eraseChild(i);
            break;
        }
    }
    head->setParent(nullptr);
    delete lastHead;

    Node * currentChild;
    vector<int> move(3);
    
    for(int i=0; i<head->getChildren().size(); i++) {
        currentChild = head->getChildren().at(i);
        vector<vector<vector<char> > > currentBoard = currentChild->getBoard();
        
        for(int x=0; x<4; x++) {
            for(int y=0; y<4; y++) {
                for(int z=0; z<4; z++) {
                    if(currentBoard.at(x).at(y).at(z) == ' ') {
                        move.at(0) = x;
                        move.at(1) = y;
                        move.at(2) = z;
                        currentChild->addChild(new Node(currentChild, currentChild->getXs(),
                                                        currentChild->getOs(), currentBoard, move, player));
                    }
                }
            }
        }
    }
    
    return;
}
