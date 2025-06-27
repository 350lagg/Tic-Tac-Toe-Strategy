/*!
* \file
* \brief Данный файл содержит в себе реализацию функций, которые используются в ходе работы программы tic_tac_toe.
*/
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

void GameField::set(int i, int j, char value)
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
    // Проверка строк
    for (int i = 0; i < 3; ++i)
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;

    // Проверка столбцов
    for (int j = 0; j < 3; ++j)
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player)
            return true;

    // Проверка диагоналей
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;

    return false;
}

int TreeNode::countNodes() const 
{
    int count = 1;
    for (const TreeNode* child : children) 
    {
        count += child->countNodes();
    }
    return count;
}

/*!
 * \details Поэтапно считывает, проверяет а затем записывает каждую строку входного файла
 */
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

/*!
 * \details Находит древо ходов для выбранного игрока в игре крестики-нолики с помощью рекурсии
 */
TreeNode* generateStrategyTree(GameField position, char chosenPlayer, char currentPlayer, int& nodeId)
{
    //Записать новый узел как текущий
    TreeNode* node = new TreeNode(position, nodeId++);
    //Запомнить символ оппонента основываясь на символе выбранного игрока
    char opponent = (currentPlayer == 'X') ? 'O' : 'X';

    //Проверить поле на конец игры 
    //Если игра окончена вернуть текущий узел
    if (position.hasWinner(chosenPlayer)) {
        node->result = {1, 1};
        return node;
    }
    if (position.hasWinner(opponent)) {
        node->result = {-1, 0};
        return node;
    }
    if (position.isFull()) {
        node->result = {0, 0};
        return node;
    }
    //Если текущий игрок выбранный игрок 
    if (currentPlayer == chosenPlayer) 
    {
        //Проверка есть ли ход к немедленной победе
        for (int i = 0; i < 3; ++i) 
        {
            for (int j = 0; j < 3; ++j) 
            {
                if (position.get(i, j) == '.') 
                {
                    GameField testField = position;
                    testField.set(i, j, currentPlayer);
                    if (testField.hasWinner(currentPlayer)) 
                    {
                        // Нашли ход к немедленной победе - выбираем его
                        //Рекурсивно вызвать функцию считая текущим положением лучший ход для оппонента
                        TreeNode* child = generateStrategyTree(testField, chosenPlayer, opponent, nodeId);
                        //Записать лучший ход в древо
                        node->children.push_back(child);
                        node->result = {1, 1};
                        return node;
                    }
                }
            }
        }

        //Проверка нужно ли блокировать победу противника
        for (int i = 0; i < 3; ++i) 
        {
            for (int j = 0; j < 3; ++j) 
            {
                if (position.get(i, j) == '.') 
                {
                    GameField testField = position;
                    testField.set(i, j, opponent);
                    if (testField.hasWinner(opponent)) 
                    {
                        //Если найден ход который блокирует победу противника
                        GameField blockingField = position;
                        blockingField.set(i, j, currentPlayer);
                        //Рекурсивно вызвать функцию считая текущим положением лучший ход для оппонента
                        TreeNode* child = generateStrategyTree(blockingField, chosenPlayer, opponent, nodeId);
                        //Записать лучший ход в древо
                        node->children.push_back(child);
                        node->result = child->result;
                        return node;
                    }
                }
            }
        }

        //Если нет срочных ходов, выбираем наилучший ход
        TreeNode* bestChild = nullptr;
        EvalResult bestResult = {-2, -1};

        //Для всех клеток поля
        for (int i = 0; i < 3; ++i) 
        {
            for (int j = 0; j < 3; ++j) 
            {
                //Если найдена пустая клетка
                if (position.get(i, j) == '.') 
                {
                    //Запомнить позицию
                    GameField newField = position;
                    //Заменить позицию символом игрока
                    newField.set(i, j, currentPlayer);
                    //Рекурсивно вызвать функцию для оппонента
                    TreeNode* child = generateStrategyTree(newField, chosenPlayer, opponent, nodeId);
                    
                    //Если найден ход лучше заменить предыдущий лучший ход и удалить его ветку
                    if (child->result.outcome > bestResult.outcome || 
                       (child->result.outcome == bestResult.outcome && child->result.wins > bestResult.wins)) 
                    {
                        if (bestChild) delete bestChild;
                        bestChild = child;
                        bestResult = child->result;
                    } 
                    //Иначе удалить новый ход
                    else 
                    {
                        delete child;
                    }
                }
            }
        }

        if (bestChild) 
        {
            node->children.push_back(bestChild);
            node->result = bestResult;
        }
    }
    else 
    {
        // Для оппонента рассматриваем все возможные ходы
        int totalWins = 0;
        EvalResult worstForPlayer = {2, 0};

        //Для всех клеток поля
        for (int i = 0; i < 3; ++i) 
        {
            for (int j = 0; j < 3; ++j) 
            {
                //Если клетка пустая
                if (position.get(i, j) == '.') 
                {
                    //Заполмнить позицию поля
                    GameField newField = position;
                    //Заполнить пустую клетку символом игрока
                    newField.set(i, j, currentPlayer);
                    //Рекурсивно вызвать функцию считая последним ходом последний ход оппонента для выбранного игрока
                    TreeNode* child = generateStrategyTree(newField, chosenPlayer, opponent, nodeId);
                    //Записать ход в древо
                    node->children.push_back(child);
                    
                    totalWins += child->result.wins;
                    if (child->result.outcome < worstForPlayer.outcome || 
                       (child->result.outcome == worstForPlayer.outcome && child->result.wins < worstForPlayer.wins)) 
                    {
                        worstForPlayer = child->result;
                    }
                }
            }
        }

        node->result = {worstForPlayer.outcome, totalWins};
    }
    //Вернуть элемент древа
    return node;
}

/*!
 * \details Рекурсивно записывает полученное древо ходов в формате .dot, основываясь на связях между узлами
 */
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

/*!
 * \details Проверяет путь к выходному файлу, записывает полученное древо в формате, необходимом для .dot
 */
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
    int idCounter = 0;
    //Запись древа в формат .dot
    writeDot(root, out, idCounter);
    //Записать }
    out << "}\n";
    //Закрыть файл
    out.close();
}