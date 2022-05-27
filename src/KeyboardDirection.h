/**
 * This class has been mostly inspired by
 * @author David Bernhauer <bernhdav@fit.cvut.cz>
 * @website https://gitlab.fit.cvut.cz/bernhdav/pa2-bomb-tag/blob/master/src/EDirection.h
 */

#pragma once

enum class KeyboardDirection : size_t {
    NONE = static_cast<size_t>( -1 ),
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3,
    EDIT = 4,
    QUIT = 5,
    DELETE = 6,
    SAVE = 7,
    LOAD = 8,
};

constexpr const size_t DIRECTIONS = 9;

