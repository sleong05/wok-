#include "chengine/staticBoardAnalyzer.hpp"
#include "chengine/theoryEvaluator.hpp"
#include "board.hpp"
#include "constants.hpp"

using namespace constants;

double SBAnalyzer::evaluateBoard(const Board &board)
{
    if (board.isThreefoldRepetition())
        return 0;

    double boardValue = 0;
    const auto boardState = board.getSquares();
    const auto moveState = board.hasMovedArray;

    for (const auto &position : board.blackPositions)
    {
        auto [col, row] = position;
        boardValue -= getPieceValue(boardState[row][col], col, row, board);
    }

    for (const auto &position : board.whitePositions)
    {

        auto [col, row] = position;
        boardValue += getPieceValue(boardState[row][col], col, row, board);
    }
    return boardValue;
}

double SBAnalyzer::getPieceValue(int piece, int col, int row, const Board &board)
{
    const auto boardState = board.getSquares();
    const auto moveState = board.hasMovedArray;
    int movesDone = board.getMoveCount();
    if (piece == constants::EMPTY)
    {
        std::cerr << "Invalid piece ID: " << piece << std::endl;
        return 0; // or some safe default
    }
    double hasNotMoved = (moveState[row][col] == false) ? 1.0 / 3.0 : 0.0;
    switch (piece)
    {
    case WHITE_PAWN:
    case BLACK_PAWN:
    {
        double notMovedValue = (col != 5) ? 0 : -.5;                                      // kings pawn shouldnt move
        return 1.0 + TheoryEvaluator::getPawnValue(col, row, boardState) - notMovedValue; // moveState is 0 or 1. hasMoved = true =1
    }

    case WHITE_KNIGHT:
    case BLACK_KNIGHT:
        return 3.0 + TheoryEvaluator::getKnightValue(col, row) - hasNotMoved;

    case WHITE_BISHOP:
    case BLACK_BISHOP:
        return 3.1 + TheoryEvaluator::getBishopValue(col, row, boardState) - hasNotMoved;

    case WHITE_ROOK:
    case BLACK_ROOK:
        return 5.0 + TheoryEvaluator::getRookValue(col, row, boardState); // we dont want these peices to move unless they arleady have

    case WHITE_QUEEN:
    case BLACK_QUEEN:
        return 9.0 + TheoryEvaluator::getQueenValue(col, row, boardState); // we dont want these peices to move unless they arleady have

    case WHITE_KING:
    case BLACK_KING:
        return 0.0 + TheoryEvaluator::getKingValue(col, row, boardState, moveState, movesDone) - hasNotMoved;

    default:
        std::cerr << "Invalid piece ID: " << piece << '\n';
        throw std::runtime_error("tried to evalaute not a piece");
        return 0;
    }
}