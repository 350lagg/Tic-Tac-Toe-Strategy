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
    TreeNode* node = new TreeNode(position, nodeId++);
    //Запомнить символ оппонента основываясь на символе выбранного игрока
    char opponent = (currentPlayer == 'X') ? 'O' : 'X';
    //Проверить поле на конец игры 
    //Если игра окончена вернуть текущий узел
    if (position.hasWinner('X') || position.hasWinner('O') || position.isFull())
    {
        return node;
    }
    //Если текущий игрок выбранный игрок 
    if (currentPlayer == chosenPlayer)
    {
        //Найти лучший ход#
        EvalResult best = evaluateGame(position, currentPlayer, chosenPlayer);
        //Рекурсивно вызвать функцию считая текущим положением лучший ход для оппонента
        TreeNode* bestChild = generateStrategyTree(best.move, chosenPlayer, opponent, nodeId);
        //Записать лучший ход в древо
        node->children.push_back(bestChild);
    }
    //Иначе
    else
    {
        //Для всех символов поля
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                //Если символ пустой
                if (position.get(i, j) == '.')
                {
                    //Запомнить положение поля
                    GameField newField = position;
                    //Заменить в запомненном положении текущий символ на знак выбранного игрока
                    newField.set(i, j, currentPlayer);
                    //Рекурсивно вызвать функцию считая текущим положением последний ход для выбранного игрока
                    TreeNode* child = generateStrategyTree(newField, chosenPlayer, opponent, nodeId);
                    //Записать последний ход в древо
                    node->children.push_back(child);
                }
            }
        }
    }
    //Вернуть элемент древа ходов
    return node;
}

EvalResult evaluateGame(GameField field, char curPlayer, char maximizingPlayer)
{
    //Записать символ оппонента основываясь на символе выбранного игрока
    char opponent = (curPlayer == 'X') ? 'O' : 'X';
    //Проверить поле на конец игры 
    //Если игра окончена вернуть величину исхода
    if (field.hasWinner(maximizingPlayer)) return { 1, 1, field };
    if (field.hasWinner(opponent)) return { -1, 0, field };
    if (field.isFull()) return { 0, 0, field };
    vector<EvalResult> results;
    //Для каждого символа поля
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            //Если символ пустой
            if (field.get(i, j) == '.')
            {
                //Запомнить положение поля
                GameField newField = field;
                //Заменить в запомненном положении текущий символ на знак выбранного игрока 
                newField.set(i, j, curPlayer);
                //Рекурсивно вызвать функцию считая текущим положением поля последний ход для оппонента
                EvalResult result = evaluateGame(newField, opponent, maximizingPlayer);
                //Запомнить результат
                result.move = newField;
                results.push_back(result);
            }
        }
    }
    //Для результата
    for (const EvalResult& r : results)
    {
        //Если ход – мгновенная победа
        if (r.outcome == 1 && curPlayer == maximizingPlayer && r.move.hasWinner(maximizingPlayer))
        {
            //Вернуть величины исхода и ход
            return { 1, 1, r.move };
        }
        //Если ход – мгновенная победа противника
        if (r.outcome == -1 && curPlayer != maximizingPlayer && r.move.hasWinner((maximizingPlayer == 'X') ? 'O' : 'X'))
        {
            //Вернуть величины исхода и ход
            return { -1, 0, r.move };
        }
    }

    //Запомнить результаты
    EvalResult best = results[0];
    //Для результатов
    for (const EvalResult& r : results)
    {
        //Если текущий игрок-выбранный игрок
        if (curPlayer == maximizingPlayer)
        {
            //Выбираем лучший ход
            if (r.outcome > best.outcome || (r.outcome == best.outcome && r.wins > best.wins))
            {
                //Выбираем лучший ход
                best = r;
            }
        }
        //Иначе
        else
        {
            //Рассматриваем все ходы
            if (r.outcome < best.outcome || (r.outcome == best.outcome && r.wins < best.wins))
            {
                best = r;
            }
        }
    }
    //Считаем общее количество побед для хода
    int totalWins = 0;
    for (const EvalResult& r : results)
    {
        totalWins += r.wins;
    }
    //Возвращаем минимальный исход, количество побед и лучший ход
    return { best.outcome, totalWins, best.move };
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
    ofstream out(filename);
    //Если выходной файл не открывается
    if (!out)
    {
        //Завершение работы программы, вернуть ошибку
        cerr << "Ошибка записи в " << filename << endl;
        return;
    }
    //Записать digraph G {
    out << "digraph G {\n";
    //Запись древа в формат .dot
    int idCounter = 0;
    writeDot(root, out, idCounter);
    //Записать }
    out << "}\n";
    //Закрыть файл
    out.close();
}


