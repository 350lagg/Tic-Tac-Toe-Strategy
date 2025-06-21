/*!
* \file
* \brief ������ ���� �������� � ���� ���������� �������, ������� ������������ � ���� ������ ��������� tic_tac_toe.
*/
#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

/*!
* \brief ����� ��� ������ � �����
*/
class GameField
{
private:
    char board[3][3];
public:
    /*!
    * \brief ����������� ������ GameField
    */
    GameField();

    /*!
    * \brief ����������� ������ GameField
    */
    GameField(char b[3][3]);

    /*!
    * \brief �������� 1 ������� �� ������� i;j
    * \param[in] i - ����� ������
    * \param[in] j - ����� �������� � ������
    * \return ������ � ��������� �������
    */
    char get(int i, int j) const;

    /*!
    * \brief ���������� 1 ������� � ������� i;j
    * \param[in] i - ����� ������
    * \param[in] j - ����� �������� � ������
    * \param[in] value - ������ ��� �������
    */
    void set(int i, int j, char value); 

    /*!
    * \brief ��������� ����� ����
    * \param[in] dest - ����
    */
    void getBoard(char dest[3][3]) const;

    /*!
    * \brief �������� ������������ ����
    */
    bool isFull() const;

    /*!
    * \brief �������� ����������
    */
    bool hasWinner(char player) const;
};

/*!
* \brief ����� ��� ������ ����� �����
*/
class TreeNode
{
public:
    int id; //!< ����� ������
    GameField field; //!< ��������� ����
    vector<TreeNode*> children; //!< �������

    /*!
    * \brief ����������� ������ TreeNode
    */
    TreeNode(const GameField& f, int node_id) : field(f), id(node_id) {}
};

/*!
* \brief ������������ ����� ������, ������� ����� ���������� � �������� �������
*/
enum ErrorType
{
    noError, //!< ��� ������
    inputFileError, //!< ������ ������ �������� �����
    outputFileError, //!< ������ ������ ��������� �����
    manyLinesError, //!< ������ �������������� ���������� �����
    notEnoughLinesError, //!< ������ ����������� ���������� �����
    lineLengthError, //!< ������ ������ �����
    lineContentError, //!< ������ ���������� �����
    impossibleConfigurationError //!< ������ ����������� ������������ ����
};

/*!
* \brief ��������� ������
*/
struct Error
{
    ErrorType type; //!< ��� ������
    string file_path; //!< ���� ����� � �������
    int lines_count; //!< ����� ������
    int line_length; //!< ������� � ������
    char invalid_char; //!< �������� ������
};

/*!
* \brief ��������� ���������� ����
*/
struct EvalResult
{
    int outcome; //!< ����������� �����
    int wins;    //!< ���������� �����
    GameField move; //!< ��������� ����
};

/*!
* \brief ������� ��� ���������� � �������� ������ �� �������� �����
* \param [in] filename - ���������� ��� ������������� ���� � �������� ����� � ���� ������
* \param [in] board - ���� ��� ����������
* \param [in] player - ������ ��� ��������� ���� ������
* \return ��������� ������
*/
Error readInput(const string& filename, char board[3][3], char& player);

/*!
* \brief ������� ��� ���������� ������ ����� � ��������-������
* \param [in] position - ��������� �� ����
* \param [in] chosenPlayer - ��������� �����
* \param [in] currentPlayer - ������� �����
* \param [in] nodeId - ����� ������
* \return ����� �����
*/
TreeNode* generateStrategyTree(GameField position, char chosenPlayer, char currentPlayer, int& nodeId);

/*!
* \brief ������� ��� ������ ����� � ������ .dot
* \param [in] node - ���� ����� �����
* \param [in] out - ���� ��� ������
* \param [in] idCounter - ����� ����
*/
void writeDot(TreeNode* node, ofstream& out, int& idCounter);

/*!
* \brief ������� ��� ������ ����� ����� � ���� � ������� .dot
* \param [in] root - ��������� ���� ����� �����
* \param [in] filename - ���� � ����� ��� ������ � ������� string
*/
void exportTreeToDot(TreeNode* root, const string& filename);

/*!
* \brief ������� ��� ���������� ������� ����
* \param [in] field - ��������� �� ����
* \param [in] curPlayer - ������� �����
* \param [in] maximizingPlayer - ��������� �����
*/
EvalResult evaluateGame(GameField field, char curPlayer, char maximizingPlayer);