#pragma once
#include "legalMove.hpp"
#include <vector>
class Rook
{
public:
    static std::vector<LegalMove> getPseudoMoves(int col, int row, int piece, std::array<std::array<int, 8U>, 8U> &boardState, bool capturesOnly = false);
    static int getNumberOfMoves(int col, int row, const std::array<std::array<int, 8U>, 8U> &boardState);
};