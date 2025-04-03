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

