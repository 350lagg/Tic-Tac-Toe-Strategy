#include "functions.h"

GameField::GameField()
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board[i][j] = ' ';
}

GameField::GameField(char b[3][3])
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board[i][j] = b[i][j];
}

char GameField::get(int i, int j) const
{
    return board[i][j];
}

void  GameField::set(int i, int j, char value)
{
    if (i >= 0 && i < 3 && j >= 0 && j < 3)
        board[i][j] = value;
}

Error readFiles(const string& inputPath, const string& outputPath, char board[3][3])
{
    //Если входной файл не открылся
    {
        //Завершение работы программы, вернуть индекс ошибки inputFileError
    }
    //Если выходной файл не открылся
    {
        //Завершение работы программы, вернуть индекс ошибки outputFileError
    }
    //Если не прошла проверка на количество строк
    {
        //Завершение работы программы, вернуть индекс ошибки manyLinesError или notEnoughLinesError в зависимости от отклонения количества строк
    }
    //Если не прошла проверка на длинну строк
    {
        //Завершение работы программы, вернуть индекс ошибки lineLengthError
    }
    //Если не прошла проверка на  содержание строк
    {
        //Завершение работы программы, вернуть индекс ошибки lineContentError
    }
    //Если не прошла проверка на  конфигурацию на поле
    {
        //Завершение работы программы, вернуть индекс ошибки impossibleConfigurationError
    }
    //Завершение работы программы, вернуть индекс noError
}

int main(int argc, char* argv[])
{
	//Считывание и проверка файлов
    //Если проверка данных файлов не прошла
    {
        //Вернуть ошибку
        //Завершение работы программы
    }
    //Иначе
    {
        //Работа главной вычислительной функции для нахождения дерева ходов в крестики-нолики
        //Вывод программы 
    }
}

