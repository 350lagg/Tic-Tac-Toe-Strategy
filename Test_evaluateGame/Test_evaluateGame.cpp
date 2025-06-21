/*!
* \file
* \brief Данный файл содержит тесты для функции evaluateGame.
*/
#include "pch.h"
#include "CppUnitTest.h"
#include "../tic_tac_toe/functions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestevaluateGame
{
	TEST_CLASS(TestevaluateGame)
	{
	public:
		
		TEST_METHOD(DefaultTest)
		{
			char board[3][3] =
			{
				{'.', '.', 'X'},
				{'.', 'X', 'O'},
				{'O', '.', '.'}
			};
			int outcome = 0;
			int	wins = 0;
			char player = 'X';
			char curPlayer = 'X';
			GameField start(board);
			EvalResult res = evaluateGame(start, curPlayer, player);
			char expMove[3][3] =
			{
				{'X', '.', 'X'},
				{'.', 'X', 'O'},
				{'O', '.', '.'}
			};
			GameField expStart(expMove);
			int expOutcome = 1;
			int	expWins = 22;
			EvalResult expRes{ expOutcome, expWins,expStart };
			Assert::AreEqual(expRes.outcome, res.outcome);
			Assert::AreEqual(expRes.wins, res.wins);

			// Сравнение полей 
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					Assert::AreEqual(expRes.move.get(i, j), res.move.get(i, j));
				}
			}
		}

		TEST_METHOD(PlayerO)
		{
			char board[3][3] =
			{
				{'.', 'X', '.'},
				{'.', 'O', '.'},
				{'X', '.', '.'}
			};
			int outcome = 0;
			int	wins = 0;
			char player = 'O';
			char curPlayer = 'O';
			GameField start(board);
			EvalResult res = evaluateGame(start, curPlayer, player);
			char expMove[3][3] =
			{
				{'.', 'X', 'O'},
				{'.', 'O', '.'},
				{'X', '.', '.'}
			};
			GameField expStart(expMove);
			int expOutcome = 0;
			int	expWins = 45;
			EvalResult expRes{ expOutcome, expWins,expStart };
			Assert::AreEqual(expRes.outcome, res.outcome);
			Assert::AreEqual(expRes.wins, res.wins);

			// Сравнение полей
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					Assert::AreEqual(expRes.move.get(i, j), res.move.get(i, j));
				}
			}
		}

		TEST_METHOD(BestMove_InstantWin)
		{
			char board[3][3] =
			{
				{'.', 'O', 'X'},
				{'.', 'X', 'O'},
				{'.', '.', '.'}
			};
			int outcome = 0;
			int	wins = 0;
			char player = 'X';
			char curPlayer = 'X';
			GameField start(board);
			EvalResult res = evaluateGame(start, curPlayer, player);
			char expMove[3][3] =
			{
				{'.', 'O', 'X'},
				{'.', 'X', 'O'},
				{'X', '.', '.'}
			};
			GameField expStart(expMove);
			int expOutcome = 1;
			int	expWins = 1;
			EvalResult expRes{ expOutcome, expWins,expStart };
			Assert::AreEqual(expRes.outcome, res.outcome);
			Assert::AreEqual(expRes.wins, res.wins);

			// Сравнение полей 
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					Assert::AreEqual(expRes.move.get(i, j), res.move.get(i, j));
				}
			}
		}

		TEST_METHOD(BestMove_NotToInstantWin)
		{
			char board[3][3] =
			{
				{'.', 'X', 'O'},
				{'.', 'O', 'X'},
				{'.', '.', '.'}
			};
			int outcome = 0;
			int	wins = 0;
			char player = 'X';
			char curPlayer = 'X';
			GameField start(board);
			EvalResult res = evaluateGame(start, curPlayer, player);
			char expMove[3][3] =
			{
				{'.', 'X', 'O'},
				{'.', 'O', 'X'},
				{'X', '.', '.'}
			};
			GameField expStart(expMove);
			int expOutcome = 0;
			int	expWins = 6;
			EvalResult expRes{ expOutcome, expWins,expStart };
			Assert::AreEqual(expRes.outcome, res.outcome);
			Assert::AreEqual(expRes.wins, res.wins);

			// Сравнение полей
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					Assert::AreEqual(expRes.move.get(i, j), res.move.get(i, j));
				}
			}
		}

		TEST_METHOD(EmptyBoard)
		{
			char board[3][3] =
			{
				{'.', '.', '.'},
				{'.', '.', '.'},
				{'.', '.', '.'}
			};
			int outcome = 0;
			int	wins = 0;
			char player = 'X';
			char curPlayer = 'X';
			GameField start(board);
			EvalResult res = evaluateGame(start, curPlayer, player);
			char expMove[3][3] =
			{
				{'.', 'X', '.'},
				{'.', '.', '.'},
				{'.', '.', '.'}
			};
			GameField expStart(expMove);
			int expOutcome = 0;
			int	expWins = 24096;
			EvalResult expRes{ expOutcome, expWins,expStart };
			Assert::AreEqual(expRes.outcome, res.outcome);
			Assert::AreEqual(expRes.wins, res.wins);

			// Сравнение полей
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					Assert::AreEqual(expRes.move.get(i, j), res.move.get(i, j));
				}
			}
		}

		TEST_METHOD(OneElOnBoard)
		{
			char board[3][3] =
			{
				{'.', 'X', '.'},
				{'.', '.', '.'},
				{'.', '.', '.'}
			};
			int outcome = 0;
			int	wins = 0;
			char player = 'O';
			char curPlayer = 'O';
			GameField start(board);
			EvalResult res = evaluateGame(start, curPlayer, player);
			char expMove[3][3] =
			{
				{'O', 'X', '.'},
				{'.', '.', '.'},
				{'.', '.', '.'}
			};
			GameField expStart(expMove);
			int expOutcome = 0;
			int	expWins = 1824;
			EvalResult expRes{ expOutcome, expWins,expStart };
			Assert::AreEqual(expRes.outcome, res.outcome);
			Assert::AreEqual(expRes.wins, res.wins);

			// Сравнение полей
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					Assert::AreEqual(expRes.move.get(i, j), res.move.get(i, j));
				}
			}
		}

		TEST_METHOD(OneEmptyPlace)
		{
			char board[3][3] =
			{
				{'O', 'X', 'X'},
				{'X', 'X', 'O'},
				{'.', 'O', 'O'}
			};
			int outcome = 0;
			int	wins = 0;
			char player = 'X';
			char curPlayer = 'X';
			GameField start(board);
			EvalResult res = evaluateGame(start, curPlayer, player);
			char expMove[3][3] =
			{
				{'O', 'X', 'X'},
				{'X', 'X', 'O'},
				{'X', 'O', 'O'}
			};
			GameField expStart(expMove);
			int expOutcome = 1;
			int	expWins = 1;
			EvalResult expRes{ expOutcome, expWins,expStart };
			Assert::AreEqual(expRes.outcome, res.outcome);
			Assert::AreEqual(expRes.wins, res.wins);

			// Сравнение полей
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					Assert::AreEqual(expRes.move.get(i, j), res.move.get(i, j));
				}
			}
		}

		TEST_METHOD(NoEmptyPlace)
		{
			char board[3][3] =
			{
				{'O', 'X', 'O'},
				{'O', 'X', 'X'},
				{'X', 'O', 'X'}
			};
			int outcome = 0;
			int	wins = 0;
			char player = 'O';
			char curPlayer = 'O';
			GameField start(board);
			EvalResult res = evaluateGame(start, curPlayer, player);
			char expMove[3][3] =
			{
				{'O', 'X', 'O'},
				{'O', 'X', 'X'},
				{'X', 'O', 'X'}
			};
			GameField expStart(expMove);
			int expOutcome = 0;
			int	expWins = 0;
			EvalResult expRes{ expOutcome, expWins,expStart };
			Assert::AreEqual(expRes.outcome, res.outcome);
			Assert::AreEqual(expRes.wins, res.wins);

			// Сравнение полей
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					Assert::AreEqual(expRes.move.get(i, j), res.move.get(i, j));
				}
			}
		}
	};
}
