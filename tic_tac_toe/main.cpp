/*!
* \file
* \brief ������ ���� �������� ������� ������� ��������� tic_tac_toe.
*
* \mainpage ������������ ��� ��������� "Tic Tac Toe Strategy" (tic_tac_toe)
��������� ������������� ��� ���������� ����� ����������� ��������� ��� ���� �������� ������ ��� �������� ������������.
��� ���������������� ��������� ���������� ������������ ������� Windows 7 ��� ����.
��������� ����������� �� ����� �++ � �������������� ����������� ��������� C++ � ����� ���������� Microsoft Visual Studio.
��������� ������ �������� ��� ��������� ��������� ������: ��� �������� ����� � ��� ��������� ����� � ������� 'txt'

������ ������� ������� ���������:
* \code
./tic_tac_toe.exe ./input.txt ./output.txt
* \endcode

* \author Grechishnikov Ivan
* \date June 2025
* \version 1.0
*/
#include "tic_tac_toe.cpp"
/*!
 * \brief ������� ������� ���������
 * \param [in] argc - ���������� ���������� ���������� ��������� ������
 * \param [in] argv - ��������� ��������� ������
 * \param [in] argv[0] - �������� ������� ���������
 * \param [in] argv[1] - ���� � �������� �����
 * \param [in] argv[2] - ���� � ��������� �����
 * \return 0 - ��������� ����������� ��� ����������
 */
int main(int argc, char* argv[])
{
    //������������� ������� ����
    setlocale(LC_ALL, "Rus");
    vector<string> file_content;
    //���������� � �������� ������
    if (argc != 3)
    {
        cerr << "����������� ������� ��������� �������. "
            "���������, ��� ��������� ������������� �������: \n"
            << argv[0] << "<path/to/input_file> <path/to/save_file>\n";
        return 1;
    }

    string inputFile = argv[1];
    string outputFile = argv[2];

    char board[3][3], player;
    string errName;
    Error err = readInput(inputFile, board, player);
    //���� �������� ������ ������ �� ������
    if (err.type != noError)
    {
        //������� ������
        //���������� ������ ���������
        switch (err.type)
        {
        case inputFileError:
            errName = "������ �������� �������� �����";
            break;
        case manyLinesError:
            errName = "������: ������� ������� ���������� ����� � ������� �����";
            break;
        case notEnoughLinesError:
            errName = "������: ������� ��������� ���������� ����� � ������� �����";
            break;
        case lineLengthError:
            errName = "������: ������ ������ ����� �������� �����";
            break;
        case lineContentError:
            errName = "������: �������� ������� � ������� �����";
            break;
        }
        cerr << errName << endl;
        return 1;
    }
    //������ �������� ������
    int xCount = 0, oCount = 0;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j] == 'X') xCount++;
            if (board[i][j] == 'O') oCount++;
        }
    }
    if (xCount != oCount && xCount != oCount + 1)
    {
        err = { impossibleConfigurationError,"",0,0,'\0' };
        errName = "������: ����������� ������������ ���������� ����";
        cerr << errName << endl;
        return 1;
    }

    char currentPlayer;
    if (xCount == oCount)
    {
        currentPlayer = 'X';
    }
    else if (xCount == oCount + 1)
    {
        currentPlayer = 'O';
    }
    //��������� ��������� ����
    GameField start(board);
    int nodeId = 0;
    //������ ������� �������������� �������
    TreeNode* root = generateStrategyTree(start, player, currentPlayer, nodeId);

    //����� ����� ����� � ������� .dot
    exportTreeToDot(root, outputFile);
    cout << "������ ��������� �������� � ���� " << outputFile << endl;

    return 0;
}