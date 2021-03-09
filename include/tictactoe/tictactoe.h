#pragma once

#include <string>
#include <vector>

namespace tictactoe {

/**
 * This enumeration specifies the possible results of the evaluation of a
 * Tic-Tac-Toe board.
 */
enum class BoardState {
  NoWinner,
  Xwins,
  Owins,
  UnreachableState,
};

/**
 * This class can store a Tic-Tac-Toe board and evaluate its state.
 */
class Board {
 public:
  /**
   * Constructs a Board from a string consisting of 9 characters in row-major
   * order (i.e. the first three characters specify the first row).
   *
   * An 'X' or 'x' represents that the corresponding square is filled with an X,
   * an 'O' or 'o' represents that the corresponding square is filled with an O,
   * and any other character represents that the corresponding square is empty.
   *
   * This method throws a std::invalid_argument exception if the string provided
   * is not a valid board.
   */
  Board(const std::string& board);

  /**
   * Evaluates the state of the board.
   */
  BoardState EvaluateBoard() const;

 private:
  std::string board;
  double board_size;
  std::vector<std::vector<char>> board_matrix;

  /**
   * Analyze each individual row of a TicTacToeBoard to check whether the row
   * contains a winner or not. Used to check columns by transposing the board
   * matrix and then checking the rows for a winner.
   *
   * @param row_vector This is each individual row of the board.
   * @param character Character that is being used to search for.
   * @return boolean of whether the row contains a winner or not.
   */
  bool CheckRowsForWinner(std::vector<char> row_vector, char character) const;

  /**
   * This checks all of the win combinations that are possible and checks if
   * the board has valid win combinations or not.
   *
   * @return BoardState that tells you whether x wins, o wins, unreachable
   * state, or no board wins.
   */
  BoardState CheckBoardWinCombinations() const;

  /**
   * Transpose the array in order to check the columns by using the checkRows
   * helper function above by inputting a transposed 2D character array instead
   * of the original.
   *
   * @param board_matrix This is the 2D vector that is going to be transposed
   * @return the transposed board matrix.
   */
  std::vector<std::vector<char>> TransposeMatrix(
      std::vector<std::vector<char>> board_matrix) const;

  /**
   * This function is utilized to turn the string into a 2D character vector.
   */
  void InitializeBoardMatrix();

  /**
   * This returns the difference between the number of x's and o's that are
   * in the board.
   *
   * @return integer of count_x - count_o.
   */
  int GetXAndOCountDifference() const;

  /**
   * This checks our instance board_matrix variables diagonal and anti-diagonal
   * for a win.
   *
   * @param character this is the desired character that we are searching for in
   * the diagonal and anti-diagonal.
   * @return boolean of whether the character won the diagonal or anti-diagonal.
   */
  bool CheckDiagonalsForWinner(char character) const;
};

}  // namespace tictactoe
