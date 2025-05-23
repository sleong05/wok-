#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SFML/Graphics.hpp>
#include <tuple>
#include <array>

namespace constants
{
    const float TILE_SIZE = 100.f;
    const float WINDOW_HEIGHT = 800.f;
    const float WINDOW_WIDTH = 800.f;
    const sf::Color creamTileColor(238, 238, 210);
    const sf::Color greenTileColor(118, 150, 86);
    const int WHITE = -1;
    const int BLACK = 1;
    const int PLAYING_PLAYER = constants::WHITE;

    const int WHITE_PAWN = 7;
    const int WHITE_KNIGHT = 8;
    const int WHITE_BISHOP = 9;
    const int WHITE_ROOK = 10;
    const int WHITE_KING = 11;
    const int WHITE_QUEEN = 12;

    const int BLACK_PAWN = 13;
    const int BLACK_KNIGHT = 14;
    const int BLACK_BISHOP = 15;
    const int BLACK_ROOK = 16;
    const int BLACK_KING = 17;
    const int BLACK_QUEEN = 18;

    const int EMPTY = 0;

    static constexpr std::array<std::pair<int, int>, 8> KING_OFFSETS = {{{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {0, -1}, {1, 1}, {1, 0}, {1, -1}}};

    constexpr std::array<std::pair<int, int>, 8> KNIGHT_OFFSETS = {{{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}}};

    constexpr std::array<std::pair<int, int>, 4> BISHOP_OFFSETS = {{{-1, -1}, {-1, 1}, {1, -1}, {1, 1}}};

    constexpr std::array<std::pair<int, int>, 4> ROOK_OFFSETS = {{{0, -1}, {-1, 0}, {0, 1}, {1, 0}}};

    inline const std::tuple<int, int> NO_TILE_SELECTED = {-1, -1};
}

#endif