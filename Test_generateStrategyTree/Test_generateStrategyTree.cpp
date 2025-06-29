﻿/*!
* \file
* \brief Данный файл содержит тесты для функции generateStrategyTree.
*/
#include "pch.h"
#include "CppUnitTest.h"
#include "../tic_tac_toe/functions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestgenerateStrategyTree
{
	TEST_CLASS(TestgenerateStrategyTree)
	{
	public:
		
        TEST_METHOD(DefaultTest)
        {
            char exprootBoard[3][3] =
            {
                {'.', 'O', 'X'},
                {'.', 'X', 'O'},
                {'.', '.', '.'}
            };
            char expChildBoard[3][3] =
            {
                {'.', 'O', 'X'},
                {'.', 'X', 'O'},
                {'X', '.', '.'}
            };
            GameField rootField(exprootBoard);
            TreeNode* exproot = new TreeNode(rootField, 0);
            GameField childField(expChildBoard);
            TreeNode* childNode = new TreeNode(childField, 1);
            exproot->children.push_back(childNode);
            char board[3][3] =
            {
                {'.', 'O', 'X'},
                {'.', 'X', 'O'},
                {'.', '.', '.'}
            };
            GameField start(board);
            int nodeId = 0;
            char player = 'X';
            char currentPlayer = 'X';
            TreeNode* root = generateStrategyTree(start, player, currentPlayer, nodeId);
            bool treesEqual = true;

            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    if (root->field.get(i, j) != exproot->field.get(i, j))
                    {
                        treesEqual = false;
                        break;
                    }
                }
                if (!treesEqual) break;
            }

            if (treesEqual)
            {
                if (root->children.size() != exproot->children.size())
                {
                    treesEqual = false;
                }
            }

            if (treesEqual && !root->children.empty() && !exproot->children.empty())
            {
                for (int i = 0; i < 3; ++i)
                {
                    for (int j = 0; j < 3; ++j)
                    {
                        if (root->children[0]->field.get(i, j) != exproot->children[0]->field.get(i, j))
                        {
                            treesEqual = false;
                            break;
                        }
                    }
                    if (!treesEqual) break;
                }

                if (treesEqual)
                {
                    if (!root->children[0]->children.empty() || !exproot->children[0]->children.empty())
                    {
                        treesEqual = false;
                    }
                }
            }

            Assert::IsTrue(treesEqual, L"Сгенерированное дерево не соответствует ожидаемому");
        }

        TEST_METHOD(ChosenPlayerX)
        {
            char board[3][3] =
            {
                {'.', 'O', 'X'},
                {'.', 'X', 'O'},
                {'.', '.', '.'}
            };
            GameField start(board);
            int nodeId = 0;
            char player = 'X';
            char currentPlayer = 'X';
            TreeNode* root = generateStrategyTree(start, player, currentPlayer, nodeId);
            int expEndId = 2;
            int totalNodes = root->countNodes();
            Assert::AreEqual(expEndId, totalNodes);
        }

        TEST_METHOD(ChosenPlayerO)
        {
            char board[3][3] =
            {
                {'.', 'O', 'X'},
                {'.', 'X', 'O'},
                {'.', '.', '.'}
            };
            GameField start(board);
            int nodeId = 0;
            char player = 'O';
            char currentPlayer = 'X';
            TreeNode* root = generateStrategyTree(start, player, currentPlayer, nodeId);
            int expEndId = 42;
            int totalNodes = root->countNodes();
            Assert::AreEqual(expEndId, totalNodes);
        }

        TEST_METHOD(EqualXAndO)
        {
            char board[3][3] =
            {
                {'.', 'O', '.'},
                {'O', 'X', 'X'},
                {'.', 'X', 'O'}
            };
            GameField start(board);
            int nodeId = 0;
            char player = 'X';
            char currentPlayer = 'X';
            TreeNode* root = generateStrategyTree(start, player, currentPlayer, nodeId);
            int expEndId = 6;
            int totalNodes = root->countNodes();
            Assert::AreEqual(expEndId, totalNodes);
        }

        TEST_METHOD(X1MoreThanO)
        {
            char board[3][3] =
            {
                {'.', 'O', '.'},
                {'O', 'X', 'X'},
                {'.', 'X', '.'}
            };
            GameField start(board);
            int nodeId = 0;
            char player = 'X';
            char currentPlayer = 'O';
            TreeNode* root = generateStrategyTree(start, player, currentPlayer, nodeId);
            int expEndId = 24;
            int totalNodes = root->countNodes();
            Assert::AreEqual(expEndId, totalNodes);
        }

        TEST_METHOD(EmptyBoard)
        {
            char board[3][3] =
            {
                {'.', '.', '.'},
                {'.', '.', '.'},
                {'.', '.', '.'}
            };
            GameField start(board);
            int nodeId = 0;
            char player = 'X';
            char currentPlayer = 'X';
            TreeNode* root = generateStrategyTree(start, player, currentPlayer, nodeId);
            int expEndId = 478;
            int totalNodes = root->countNodes();
            Assert::AreEqual(expEndId, totalNodes);
        }

        TEST_METHOD(oneElOnBoard)
        {
            char board[3][3] =
            {
                {'.', 'X', '.'},
                {'.', '.', '.'},
                {'.', '.', '.'}
            };
            GameField start(board);
            int nodeId = 0;
            char player = 'X';
            char currentPlayer = 'O';
            TreeNode* root = generateStrategyTree(start, player, currentPlayer, nodeId);
            int expEndId = 477;
            int totalNodes = root->countNodes();
            Assert::AreEqual(expEndId, totalNodes);
        }

        TEST_METHOD(twoElsOnBoard)
        {
            char board[3][3] =
            {
                {'.', 'X', '.'},
                {'.', 'O', '.'},
                {'.', '.', '.'}
            };
            GameField start(board);
            int nodeId = 0;
            char player = 'X';
            char currentPlayer = 'X';
            TreeNode* root = generateStrategyTree(start, player, currentPlayer, nodeId);
            int expEndId = 90;
            int totalNodes = root->countNodes();
            Assert::AreEqual(expEndId, totalNodes);
        }

        TEST_METHOD(emptyHalfOfBoard)
        {
            char board[3][3] =
            {
                {'O', 'X', 'X'},
                {'.', 'O', '.'},
                {'.', '.', '.'}
            };
            GameField start(board);
            int nodeId = 0;
            char player = 'X';
            char currentPlayer = 'X';
            TreeNode* root = generateStrategyTree(start, player, currentPlayer, nodeId);
            int expEndId = 14;
            int totalNodes = root->countNodes();
            Assert::AreEqual(expEndId, totalNodes);
        }

        TEST_METHOD(oneEmptySlot)
        {
            char board[3][3] =
            {
                {'O', 'X', 'X'},
                {'X', 'O', 'O'},
                {'O', 'X', '.'}
            };
            GameField start(board);
            int nodeId = 0;
            char player = 'X';
            char currentPlayer = 'X';
            TreeNode* root = generateStrategyTree(start, player, currentPlayer, nodeId);
            int expEndId = 2;
            int totalNodes = root->countNodes();
            Assert::AreEqual(expEndId, totalNodes);
        }

        TEST_METHOD(fullBoard)
        {
            char board[3][3] =
            {
                {'O', 'X', 'X'},
                {'X', 'O', 'O'},
                {'O', 'X', 'X'}
            };
            GameField start(board);
            int nodeId = 0;
            char player = 'X';
            char currentPlayer = 'X';
            TreeNode* root = generateStrategyTree(start, player, currentPlayer, nodeId);
            int expEndId = 1;
            int totalNodes = root->countNodes();
            Assert::AreEqual(expEndId, totalNodes);
        }
	};
}
