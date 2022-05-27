/**
 * This class has not been created by the author of this project
 * @author David Bernhauer <bernhdav@fit.cvut.cz>
 * @website https://gitlab.fit.cvut.cz/bernhdav/pa2-bomb-tag/blob/master/src/CInteractiveBuffer.h
 */

#pragma once

#include <cstdlib>
#include <list>
#include <termios.h>
#include "KeyboardDirection.h"
#include "KeyboardControls.h"

class InteractiveBuffer {
public:
    explicit InteractiveBuffer(size_t maxSize = 0);

    InteractiveBuffer(const InteractiveBuffer &) = delete;

    InteractiveBuffer &operator=(const InteractiveBuffer &) = delete;

    ~InteractiveBuffer();

    InteractiveBuffer &Start();

    KeyboardDirection Retrieve(const KeyboardControls &controls);

    InteractiveBuffer &Stop();

private:
    constexpr static const size_t DEFAULT_SIZE = 100;

    size_t maxSize;

    std::list<char> buffer;

    struct termios oldTermios;

    static bool has();

    static int get();
};
