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
	TreeNode* parent;
	vector<TreeNode*> children;
	int id;
	GameField field;

	TreeNode(const GameField& f, int node_id) : field(f), id(node_id), parent(nullptr) {}
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
    int outcome; // минимальный исход
    int wins;    // количесвто побед
    GameField move;
};

//Считывание и проверка файлов
Error readFiles(const string& inputPath, const string& outputPath, char board[3][3]);

//Работа главной вычислительной функции для нахождения дерева ходов в крестики-нолики
TreeNode* generateStrategyTree(GameField position, char chosenPlayer, char currentPlayer, int& nodeId);

//Запись древа в формат .dot
void writeDot(TreeNode* node, ofstream& out, int& idCounter);

//Запись древа ходов в файл в формате .dot
void exportTreeToDot(TreeNode* root, const string& filename);

//Найти лучший ход
EvalResult evaluateGame(GameField field, char curPlayer, char maximizingPlayer);