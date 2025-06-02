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

Error readInput(const string& filename, char board[3][3], char& player)
{
    ifstream in(filename);
    //Если входной файл не открылся
    if (!in)
    {
        //Завершение работы программы, вернуть индекс ошибки inputFileError
        return { inputFileError, filename, 0, 0, '\0' };
    }

    string line;
    int count = 0;
    //считывание строк входного файла пока они есть
    while (getline(in, line))
    {   
        //если количество строк меньше 3 
        if (count < 3)
        {
            //если длинна строки не равно 3 
            if (line.size() != 3)
            {
                //Завершение работы программы, вернуть индекс ошибки lineLengthError
                return { lineLengthError, filename, count + 1, (int)line.size(), '\0' };
            }
            //посимвольная проверка строк входного файла
            for (int i = 0; i < 3; ++i)
            {
                //если найден невозможный символ 
                if (line[i] != 'X' && line[i] != 'O' && line[i] != '.')
                {
                    //Завершение работы программы, вернуть индекс ошибки lineContentError
                    return { lineContentError, filename, count + 1, i + 1, line[i] };
                }
                //Запомнить символ
                board[count][i] = line[i];
            }
        }
        //иначе если количество строк равно 3 
        else if (count == 3)
        {
            //если тип игрока невозможный символ 
            if (line.size() != 1 || (line[0] != 'X' && line[0] != 'O'))
            {
                //Завершение работы программы, вернуть индекс ошибки lineContentError
                return { lineContentError, filename, count + 1, 1, line[0] };
            }
            //запомнить тип игрока
            player = line[0];
        }
        //иначе 
        else
        {
            //Завершение работы программы, вернуть индекс ошибки manyLinesError
            return { manyLinesError, filename, count + 1, 0, '\0' };
        }
        //Увеличить количество строк на 1
        ++count;
    }
    //если количество строк меньше 4 
    if (count < 4)
    {
        //Завершение работы программы, вернуть индекс ошибки notEnoughLinesError
        return { notEnoughLinesError, filename, count, 0, '\0' };
    }
    //вернуть индекс ошибки noError
    return { noError, "", 0, 0, '\0' };
}

TreeNode* generateStrategyTree(GameField position, char chosenPlayer, char currentPlayer, int& nodeId)
{
    //Записать новый узел как текущий
    //Запомнить символ оппонента основываясь на символе выбранного игрока
    //Проверить поле на конец игры 
    //Если игра окончена вернуть текущий узел
    //Если текущий игрок выбранный игрок 
    {
        //Найти лучший ход#
        //Рекурсивно вызвать функцию считая текущим положением лучший ход для оппонента
        //Записать лучший ход в древо
    }
    //Иначе
    {
        //Для всех символов поля
        {
                //Если символ пустой
                {
                    //Запомнить положение поля
                    //Заменить в запомненном положении текущий символ на знак выбранного игрока
                    //Рекурсивно вызвать функцию считая текущим положением последний ход для выбранного игрока
                    //Записать последний ход в древо
                }
            
        }
    }
    //Вернуть элемент древа ходов
}

EvalResult evaluateGame(GameField field, char curPlayer, char maximizingPlayer)
{
    //Записать символ оппонента основываясь на символе выбранного игрока
    //Проверить поле на конец игры 
    //Если игра окончена вернуть величину исхода
    //Для каждого символа поля
    {
            //Если символ пустой
            {
                //Запомнить положение поля
                //Заменить в запомненном положении текущий символ на знак выбранного игрока 
                //Рекурсивно вызвать функцию считая текущим положением поля последний ход для оппонента
                //Запомнить результат
            }
        
    }
    //Для результата
    {
        //Если ход – мгновенная победа
        {
            //Вернуть величины исхода и ход
        }
        //Если ход – мгновенная победа противника
        {
            //Вернуть величины исхода и ход
        }
    }

    //Запомнить результаты
    //Для результатов
    {
        //Если текущий игрок-выбранный игрок
        {
            //Выбираем лучший ход
        }
        //Иначе
        {
            //Рассматриваем все ходы
        }
    }
    //Считаем общее количество побед для хода
    //Возвращаем минимальный исход, количество побед и лучший ход
}

void writeDot(TreeNode* node, ofstream& out, int& idCounter)
{
    //Запомнить текущий номер записи
    int currentId = node->id;
    string label;
    //Для каждого знака поля
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            //Записать его в строку
            label += node->field.get(i, j);
            if (j < 2) label += " ";
        }
        if (i < 2) label += "\\n";
    }
    //Вывести строку в нужном формате
    out << "  node" << currentId << " [label=\"" << label << "\", fontname=\"courier\"];\n";

    //Для каждого потомка в древе
    for (TreeNode* child : node->children)
    {
        //Записать связь
        out << "  node" << currentId << " -> node" << child->id << ";\n";
        //Рекурсивно вызвать функцию
        writeDot(child, out, idCounter);
    }
}

void exportTreeToDot(TreeNode* root, const string& filename)
{
    //Открыть выходной файл
    //Если выходной файл не открывается
    {
        //Завершение работы программы, вернуть ошибку
    }
    //Записать digraph G {
    //Запись древа в формат .dot
    //Записать }
    //Закрыть файл
}

int main(int argc, char* argv[])
{
    //Устанавливаем русский язык
	//Считывание и проверка файлов
    //Если проверка данных файлов не прошла
    {
        //Вернуть ошибку
        //Завершение работы программы
    }
    //Расчет текущего игрока
    //Запомнить начальное поле
    //Работа главной вычислительной функции
    //Вывод древа ходов в формате .dot
    return 0;
}

