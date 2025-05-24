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
    void getBoard(char dest[3][3]) const;
    bool isFull() const;
    bool hasWinner(char player) const;
};

class TreeNode
{
public:
    int id;
    GameField field;
    vector<TreeNode*> children;

    TreeNode(const GameField& f, int node_id) : field(f), id(node_id) {}
};

enum ErrorType
{
    noError,
    inputFileError,
    outputFileError,
    manyLinesError,
    notEnoughLinesError,
    lineLengthError,
    lineContentError,
    impossibleConfigurationError
};

struct Error
{
    ErrorType type;
    string file_path;
    int lines_count;
    int line_length;
    char invalid_char;
};

struct EvalResult
{
    int outcome; // ����������� �����
    int wins;    // ���������� �����
    GameField move;
};

//���������� � �������� ������
Error readInput(const string& filename, char board[3][3], char& player);

//������ ������� �������������� ������� ��� ���������� ������ ����� � ��������-������
TreeNode* generateStrategyTree(GameField position, char chosenPlayer, char currentPlayer, int& nodeId);

//������ ����� � ������ .dot
void writeDot(TreeNode* node, ofstream& out, int& idCounter);

//������ ����� ����� � ���� � ������� .dot
void exportTreeToDot(TreeNode* root, const string& filename);

//����� ������ ���
EvalResult evaluateGame(GameField field, char curPlayer, char maximizingPlayer);