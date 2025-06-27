/*!
* \file
* \brief Данный файл содержит в себе объявление функций, которые используются в ходе работы программы tic_tac_toe.
*/
#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

/*!
* \brief Класс для работы с полем
*/
class GameField
{
private:
    char board[3][3];
public:
    /*!
    * \brief Основной конструктор класса GameField
    */
    GameField();

    /*!
    * \brief Дополнительный конструктор класса GameField
    */
    GameField(char b[3][3]);

    /*!
    * \brief получить 1 элемент из позиции i;j
    * \param[in] i - номер строки
    * \param[in] j - номер элемента в строке
    * \return символ с выбранной позиции
    */
    char get(int i, int j) const;

    /*!
    * \brief установить 1 элемент в позицию i;j
    * \param[in] i - номер строки
    * \param[in] j - номер элемента в строке
    * \param[in] value - символ для вставки
    */
    void set(int i, int j, char value);

    /*!
    * \brief получение всего поля
    * \param[in] dest - поле
    */
    void getBoard(char dest[3][3]) const;

    /*!
    * \brief проверка заполнености поля
    * \return true поле заполнено
    * \return false поле не заполнено
    */
    bool isFull() const;

    /*!
    * \brief проверка победителя
    * \param[in] player - символ проверяемого игрока
    * \return true есть победитель
    * \return false нет победителя
    */
    bool hasWinner(char player) const;
};

/*!
* \brief Структура результата хода
*/
struct EvalResult
{
    int outcome; //!< исход игры (1 - победа, 0 - ничья, -1 - поражение)
    int wins;    //!< количество победных путей
};

/*!
* \brief Класс для записи древа ходов
*/
class TreeNode
{
public:
    int id; //!< номер записи
    GameField field; //!< положение поля
    vector<TreeNode*> children; //!< потомки
    EvalResult result; //!< результат оценки позиции

    /*!
    * \brief Конструктор класса TreeNode
    */
    TreeNode(const GameField& f, int node_id) : field(f), id(node_id), result({ 0,0 }) {}

    /*!
    * \brief Подсчет узлов древа
    * \return количество узлов древа
    */
    int countNodes() const;
};

/*!
* \brief Перечисление типов ошибок
*/
enum ErrorType
{
    noError, //!< нет ошибки
    inputFileError, //!< ошибка чтения входного файла
    outputFileError, //!< ошибка чтения выходного файла
    manyLinesError, //!< ошибка недостаточного количества строк
    notEnoughLinesError, //!< ошибка избыточного количества строк
    lineLengthError, //!< ошибка длинны строк
    lineContentError, //!< ошибка содержания строк
    impossibleConfigurationError //!< ошибка невозможной конфигурации поля
};

/*!
* \brief Структура ошибки
*/
struct Error
{
    ErrorType type; //!< тип ошибки
    string file_path; //!< путь файла с ошибкой
    int lines_count; //!< номер строки
    int line_length; //!< позиция в строке
    char invalid_char; //!< неверный символ
};

/*!
* \brief Функция для считывания и проверки данных из входного файла
* \param [in] filename - абсолютный или относительный путь к входному файлу в виде строки
* \param [in] board - поле для заполнения
* \param [in] player - символ для получения типа игрока
* \return структура ошибки
*/
Error readInput(const string& filename, char board[3][3], char& player);

/*!
* \brief Функция для нахождения дерева ходов в крестики-нолики
* \param [in] position - положение на поле
* \param [in] chosenPlayer - выбранный игрок
* \param [in] currentPlayer - текущий игрок
* \param [in] nodeId - номер записи
* \return древо ходов
*/
TreeNode* generateStrategyTree(GameField position, char chosenPlayer, char currentPlayer, int& nodeId);

/*!
* \brief Функция для записи древа в формат .dot
* \param [in] node - узел древа ходов
* \param [in] out - файл для записи
* \param [in] idCounter - номер узла
*/
void writeDot(TreeNode* node, ofstream& out, int& idCounter);

/*!
* \brief Функция для записи древа ходов в файл в формате .dot
* \param [in] root - начальный узел древа ходов
* \param [in] filename - путь к файлу для записи в формате string
*/
void exportTreeToDot(TreeNode* root, const string& filename);