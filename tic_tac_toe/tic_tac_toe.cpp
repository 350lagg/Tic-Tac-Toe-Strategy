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

void GameField::getBoard(char dest[3][3]) const
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            dest[i][j] = board[i][j];
}

bool GameField::isFull() const
{

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] == '.')
                return false;
    return true;
}

bool GameField::hasWinner(char player) const
{
    for (int i = 0; i < 3; ++i)
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
    for (int j = 0; j < 3; ++j)
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player)
            return true;
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;
    return false;
}

Error readFiles(const string& inputPath, const string& outputPath, char board[3][3])
{
    //Если входной файл не открылся
    {
        //Завершение работы программы, вернуть индекс ошибки inputFileError
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

TreeNode* generateBestStrategy(int EndValue, int minEndValue, char ChosenPlayer, char CurrentPlayer, bool isBestMoveFound, char CurrentBoard[3][3], GameField field)
{
    //Проверка если есть победитель и заполнено ли поле
    {
        //Вернуть величину исхода(+1 если победа, 0 если ничья, -1 если поражение)
        //Запомнить величину наихудшего исхода
        //Завершить работу программы
    }
    //Если текущий игрок это выбранный игрок
    {
        //Проходим каждую клетку
        {
            //Если клетка не заполнена
            {
                //Заполняем ее знаком игрока
                //Рекурсивно вызываем функцию для противника
                //Запоминаем величину суммы исходов и величину наихудшего исхода
                //Отменяем ход
                //Выбираем наилучший ход
            }
        }
        //Запоминаем наилучший ход как новый элемент древа
    }
    //Если текущий игрок это оппонент и наилучший ход не найден
    {
        //Перебираем все возможные ходы
        {
            //Если клетка не заполнена
            {
                //Заполняем ее знаком игрока
                //Рекурсивно вызываем функцию для выбранного игрока
                //Отменяем ход
            }
        }
    }
    //Если текущий игрок это оппонент и наилучший ход найден
    {
        //Наилучший ход считать не найденным
        //Перебираем все возможные ходы
        {
            //Если клетка не заполнена
            {
                //Заполняем ее знаком игрока
                //Запоминаем ход как новый элемент древа 
                //Рекурсивно вызываем функцию для выбранного игрока
            }
        }
    }
    //Вернуть древо оптимальной стратегии
}

void writeDot(TreeNode* node, ofstream& out, int& idCounter)
{
    //Запомнить текущий номер записи
    //Для каждого знака поля
    {
        //Записать его в строку
    }
    //Вывести строку в нужном формате
    //Для каждого потомка в древе
    {
        //Записать связь
        //Рекурсивно вызвать функцию
    }
}

void exportTreeToDot(TreeNode* root, const string& filename)
{
    //Открыть выходной файл
    //Если выходной файл не открывается
    {
        //Завершение работы программы, вернуть ошибку outputFileError
    }
    //Записать digraph G {
    //Запись древа в формат .dot
    //Записать }
    //Закрыть файл
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

