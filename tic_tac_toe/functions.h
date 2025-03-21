#pragma once
#include <iostream>
#include <vector>
using namespace std;

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
public:
	TreeNode* parent;
	vector<TreeNode*> children;
	int id;
	GameField field;

	TreeNode(const GameField& f, int node_id) : field(f), id(node_id), parent(nullptr) {}
};
