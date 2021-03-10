#include <string>

#include <catch2/catch.hpp>
#include <tictactoe/tictactoe.h>

using tictactoe::Board;
using tictactoe::BoardState;

TEST_CASE("Invalid String to Board Constructor") {
  SECTION("Short String") {
    REQUIRE_THROWS_AS(Board("x"), std::invalid_argument);
  }

  SECTION("Empty String") {
    REQUIRE_THROWS_AS(Board(""), std::invalid_argument);
  }

  SECTION("Not Perfect Square String") {
      REQUIRE_THROWS_AS(Board("xxxOOO"), std::invalid_argument);
  }
}

TEST_CASE("Unreachable State when Evaluating Board") {
  SECTION("O goes first") {
    REQUIRE(Board("Ooo--xxxo").EvaluateBoard() == BoardState::UnreachableState);
  }
  SECTION("More X's than O's") {
    REQUIRE(Board("XXx---xoo").EvaluateBoard() == BoardState::UnreachableState);
  }
  SECTION("More O's than X's") {
    REQUIRE(Board("--OOO--xo").EvaluateBoard() == BoardState::UnreachableState);
  }
  SECTION("O wins but X goes again") {
    REQUIRE(Board("oooxx-x-x").EvaluateBoard() == BoardState::UnreachableState);
  }
  SECTION("X wins but O goes again") {
    REQUIRE(Board("o-oxxx--o").EvaluateBoard() == BoardState::UnreachableState);
  }
}

TEST_CASE("Boards with O wins") {
  SECTION("O wins by rows") {
    REQUIRE(Board("-x-OoOx-x").EvaluateBoard() == BoardState::Owins);
  }
  SECTION("O wins by columns"){
    REQUIRE(Board("xOX-Ow-Ox").EvaluateBoard() == BoardState::Owins);
  }
  SECTION("O wins by anti-diagonal"){
    REQUIRE(Board("x-OxO-Ox-").EvaluateBoard() == BoardState::Owins);
  }
  SECTION("O wins by diagonal"){
    REQUIRE(Board("OxxxO---O").EvaluateBoard() == BoardState::Owins);
  }
}

TEST_CASE("Boards with X wins") {
  SECTION("X wins by rows") {
    REQUIRE(Board("XXX--o-o-").EvaluateBoard() == BoardState::Xwins);
  }
  SECTION("X wins by columns"){
    REQUIRE(Board("X-ox--Xo-").EvaluateBoard() == BoardState::Xwins);
  }
  SECTION("X wins by diagonal"){
    REQUIRE(Board("X---xO-OX").EvaluateBoard() == BoardState::Xwins);
  }
  SECTION("X wins by anti-diagonal"){
    REQUIRE(Board("o-X-Xox--").EvaluateBoard() == BoardState::Xwins);
  }
  SECTION("X wins by row and column") {
    REQUIRE(Board("xxxooxoox").EvaluateBoard() == BoardState::Xwins);
  }
}

TEST_CASE("Test boards with no winners") {
  SECTION("Empty 3 by 3 Board") {
    REQUIRE(Board("---------").EvaluateBoard() == BoardState::NoWinner);
  }
  SECTION("3 by 3 full board") {
    REQUIRE(Board("x-o--x-o-").EvaluateBoard() == BoardState::NoWinner);
  }
  SECTION("5 by 5 Full Board") {
    REQUIRE(Board("x-o--x-o-xoo--x--oo--xx--").EvaluateBoard() == BoardState::NoWinner);
  }
}

TEST_CASE("Test different board sizes") {
  SECTION("X wins by rows") {
    REQUIRE(Board("o----o-oxxxx----").EvaluateBoard() == BoardState::Xwins);
  }
  SECTION("O wins by columns"){
    REQUIRE(Board("---Ox-x-O----O-x--Ox---Ox").EvaluateBoard() == BoardState::Owins);
  }
  SECTION("X wins by diagonal"){
    REQUIRE(Board("X09O90x888oox!!!!!x%$**ox").EvaluateBoard() == BoardState::Xwins);
  }
  SECTION("O wins by anti-diagonal"){
    REQUIRE(Board("xx-O--O--Ox-O-x-").EvaluateBoard() == BoardState::Owins);
  }
}