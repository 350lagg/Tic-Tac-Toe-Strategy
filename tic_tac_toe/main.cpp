/*!
* \file
* \brief Данный файл содержит главную функцию программы tic_tac_toe.
*
* \mainpage Документация для программы "Tic Tac Toe Strategy" (tic_tac_toe)
Программа предназначена для нахождения древа оптимальной стратегии для игры крестики нолики для заданной конфигурации.
Для функционирования программы необходима операционная система Windows 7 или выше.
Программа разработана на языке С++ с использованием стандартных библиотек C++ в среде разработки Microsoft Visual Studio.
Программа должна получать два аргумента командной строки: имя входного файла и имя выходного файла в формате 'txt'

Пример команды запуска программы:
* \code
./tic_tac_toe.exe ./input.txt ./output.txt
* \endcode

* \author Grechishnikov Ivan
* \date June 2025
* \version 1.0
*/
#include "functions.h"
/*!
 * \brief Главная функция программы
 * \param [in] argc - количество переданных аргументов командной строки
 * \param [in] argv - аргументы командной строки
 * \param [in] argv[0] - аргумент запуска программы
 * \param [in] argv[1] - путь к входному файлу
 * \param [in] argv[2] - путь к выходному файлу
 * \return 0 - программа завершилась без исключений
 */
int main(int argc, char* argv[])
{
    //Устанавливаем русский язык
    setlocale(LC_ALL, "Rus");
    vector<string> file_content;
    //Считывание и проверка файлов
    if (argc != 3)
    {
        cerr << "Неправильно указаны параметры запуска. "
            "Убедитесь, что параметры соответствуют шаблону: \n"
            << argv[0] << "<path/to/input_file> <path/to/save_file>\n";
        return 1;
    }

    string inputFile = argv[1];
    string outputFile = argv[2];

    char board[3][3], player;
    string errName;
    Error err = readInput(inputFile, board, player);
    //Если проверка данных файлов не прошла
    if (err.type != noError)
    {
        //Вернуть ошибку
        //Завершение работы программы
        switch (err.type)
        {
        case inputFileError:
            errName = "Ошибка открытия входного файла";
            break;
        case manyLinesError:
            errName = "Ошибка: слишком большое количество строк в входном файле";
            break;
        case notEnoughLinesError:
            errName = "Ошибка: слишком маленькое количество строк в входном файле";
            break;
        case lineLengthError:
            errName = "Ошибка: ошибка длинны строк входного файла";
            break;
        case lineContentError:
            errName = "Ошибка: неверные символы в входном файле";
            break;
        }
        cerr << errName << endl;
        return 1;
    }
    //Расчет текущего игрока
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
        errName = "Ошибка: невозможная конфигурация начального поля";
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
    //Запомнить начальное поле
    GameField start(board);
    int nodeId = 0;
    //Работа главной вычислительной функции
    TreeNode* root = generateStrategyTree(start, player, currentPlayer, nodeId);

    //Вывод древа ходов в формате .dot
    exportTreeToDot(root, outputFile);
    cout << "Дерево стратегии записано в файл " << outputFile << endl;

    return 0;
}