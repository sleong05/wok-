#include "pieces/king.hpp"
#include "squareAttacker.hpp"
#include "constants.hpp"
#include "identifier.hpp"
#include <array>
#include "pieces/king.hpp"

std::vector<LegalMove> King::getPseudoMoves(int col, int row, int piece, Board &board, bool capturesOnly)
{
    int color = Identifier::getTeam(piece);
    auto boardState = board.getSquares();
    std::vector<LegalMove> pseudoMoves;
    auto from = std::make_tuple(col, row);
    auto moveState = board.getMovesArray();
    // castling
    auto castleMoves = checkCastling(moveState, boardState, color, from);
    for (auto const &move : castleMoves)
    {
        pseudoMoves.push_back(move);
    }
    // normal moves
    for (auto &direction : constants::KING_OFFSETS)
    {
        auto [dCol, dRow] = direction;
        int tempCol = dCol + col;
        int tempRow = dRow + row;
        if (Identifier::inBounds(tempCol) and Identifier::inBounds(tempRow))
        {
            if (boardState[tempRow][tempCol] == constants::EMPTY or Identifier::getTeam(boardState[tempRow][tempCol]) != color)
            {
                if (!capturesOnly || boardState[tempRow][tempCol])
                    pseudoMoves.emplace_back(std::make_tuple(tempCol, tempRow), from, piece, boardState[tempRow][tempCol]);
            }
        }
    }
    return pseudoMoves;
}

std::vector<LegalMove> King::checkCastling(std::array<std::array<bool, 8U>, 8U> &moveState, std::array<std::array<int, 8U>, 8U> &boardState, int color, const std::tuple<int, int> &from)
{
    auto [col, row] = from;
    std::vector<LegalMove> castleMoves;
    int startingCol = 4;
    int piece = (color == constants::WHITE) ? constants::WHITE_KING : constants::BLACK_KING;
    int startingRow = (Identifier::getTeam(piece) == constants::WHITE) ? 7 : 0;
    if (not moveState[row][col] and startingCol == col and startingRow == row)
    {
        // short castle
        if (not moveState[row][7]) // check if rook has moved
        {
            if (boardState[row][6] == constants::EMPTY and boardState[row][5] == constants::EMPTY)
            {
                // check if safe
                bool castleSpotsSafe = true;
                for (int i = 4; i < 7; i++)
                {

                    if (squareAttacker::isSquareUnderAttack(i, row, color, boardState))
                    {
                        castleSpotsSafe = false;
                    }
                }
                if (castleSpotsSafe)
                {
                    LegalMove shortCastle = LegalMove(std::make_tuple(6, startingRow), from, piece, constants::EMPTY);
                    shortCastle.isCastle = true;
                    castleMoves.push_back(shortCastle);
                }
            }
        }
        // long castle
        if (not moveState[row][0]) // check if rook has moved
        {
            if (boardState[row][1] == constants::EMPTY and boardState[row][2] == constants::EMPTY and boardState[row][3] == constants::EMPTY)
            {
                // check if safe
                bool castleSpotsSafe = true;
                for (int i = 2; i < 5; i++)
                {

                    if (squareAttacker::isSquareUnderAttack(i, row, color, boardState))
                    {
                        castleSpotsSafe = false;
                    }
                }
                if (castleSpotsSafe)
                {
                    LegalMove shortCastle = LegalMove(std::make_tuple(2, startingRow), from, piece, constants::EMPTY);
                    shortCastle.isCastle = true;
                    castleMoves.push_back(shortCastle);
                }
            }
        }
    }
    return castleMoves;
}