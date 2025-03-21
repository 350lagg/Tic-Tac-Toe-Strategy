#pragma once
#include <iostream>

class GameField
{
private:
    char board[3][3];
public:
    GameField();
    GameField(char b[3][3]);
    char get(int i, int j) const;
    void set(int i, int j, char value);
};

class TreeNode
{
    
};
