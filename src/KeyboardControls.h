/**
 * This class has not been created by the author of this project
 * @author David Bernhauer <bernhdav@fit.cvut.cz>
 * @website https://gitlab.fit.cvut.cz/bernhdav/pa2-bomb-tag/blob/master/src/CControls.h
 */

#pragma once

#include <array>
#include "KeyboardDirection.h"

struct KeyboardControls
{
    std::array<char, DIRECTIONS> keybinds;
};
