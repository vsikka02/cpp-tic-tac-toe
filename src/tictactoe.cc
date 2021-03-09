#include "tictactoe/tictactoe.h"

#include <string>
#include <vector>

namespace tictactoe {

using std::string;
using std::vector;

Board::Board(const string& board) {
  if (sqrt(board.size()) - floor(sqrt(board.size())) != 0) {
    throw std::invalid_argument("The string provided is not a valid board.");
  }
  if (sqrt(board.size()) < 3) {
    throw std::invalid_argument("The string provided is not a valid board.");
  }

  board_size = sqrt(board.size());
  this->board = board;
  std::transform(this->board.begin(), this->board.end(), this->board.begin(), ::toupper);
  board_matrix = vector<vector<char>>(board_size, vector<char>(board_size));
  InitializeBoardMatrix();
}

BoardState Board::EvaluateBoard() const {
  if (!(GetXAndOCountDifference() <= 1 && GetXAndOCountDifference() >= 0)) {
    return BoardState::UnreachableState;
  }
  return CheckBoardWinCombinations();
}

BoardState Board::CheckBoardWinCombinations() const {
  bool x_winner = false;
  bool o_winner = false;

  for (int row = 0; row < board_size; row++) {
    if (CheckRowsForWinner(board_matrix[row], 'X')) {
      x_winner = true;
    }
    if (CheckRowsForWinner(board_matrix[row], 'O')) {
      o_winner = true;
    }
    if (CheckRowsForWinner(TransposeMatrix(board_matrix)[row], 'X')) {
      x_winner = true;
    }
    if (CheckRowsForWinner(TransposeMatrix(board_matrix)[row], 'O')) {
      o_winner = true;
    }
  }

  if (CheckDiagonalsForWinner('X')) {
    x_winner = true;
  }
  if (CheckDiagonalsForWinner('O')) {
    o_winner = true;
  }

  if (o_winner && x_winner) {
    return BoardState::UnreachableState;
  } else if (o_winner) {
    /**if ((GetXAndOCountDifference() == 0)) {
      return BoardState::Owins;
    }**/
    return BoardState::UnreachableState;
  } else if (x_winner) {
    if (GetXAndOCountDifference() == 1) {
      return BoardState::Xwins;
    }
    return BoardState::UnreachableState;
  }
  return BoardState::NoWinner;
}

int Board::GetXAndOCountDifference() const {
  int count_x = 0;
  int count_o = 0;
  for (int row = 0; row < board_size; row++) {
    for (int column = 0; column < board_size; column++) {
      if (board_matrix[row][column] == 'X') {
        count_x++;
      }
      if (board_matrix[row][column] == 'O') {
        count_o++;
      }
    }
  }
  return count_x - count_o;
}

void Board::InitializeBoardMatrix() {
  int char_counter = 0;

  for (int row = 0; row < board_size; row++) {
    for (int col = 0; col < board_size; col++) {
      board_matrix[row][col] = board.at(char_counter);
      char_counter++;
    }
  }
}

bool Board::CheckRowsForWinner(std::vector<char> row_vector, char character) const {
  for (int row_index = 0; row_index < board_size; row_index++) {
    if (row_vector[row_index] != character) {
      return false;
    }
  }
  return true;
}

std::vector<std::vector<char>> Board::TransposeMatrix(
    vector<vector<char>> board_2d) const {
  std::vector<std::vector<char>> transposed_matrix =
      vector<vector<char>>(board_size, vector<char>(board_size));
  for (int row = 0; row < board_size; row++) {
    for (int column = 0; column < board_size; column++) {
      transposed_matrix[row][column] = board_2d[column][row];
    }
  }
  return transposed_matrix;
}

bool Board::CheckDiagonalsForWinner(char character) const {
  bool diagonal_win = true;
  bool anti_diagonal_win = true;

  for (int i = 0; i < board_size; i++) {
    if (board_matrix[i][i] != character) {
      diagonal_win = false;
    }
    if (board_matrix[i][board_matrix.size() - i - 1] != character) {
      anti_diagonal_win = false;
    }
  }
  return diagonal_win || anti_diagonal_win;
}

} // namespace tictactoe
