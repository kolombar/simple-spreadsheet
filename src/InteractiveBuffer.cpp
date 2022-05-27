/**
 * This class has not been created by the author of this project
 * @author David Bernhauer <bernhdav@fit.cvut.cz>
 * @website https://gitlab.fit.cvut.cz/bernhdav/pa2-bomb-tag/blob/master/src/CInteractiveBuffer.cpp
 */

#include <unistd.h>
#include <termios.h>
#include <thread>
#include "InteractiveBuffer.h"
#include "KeyboardDirection.h"

using namespace std;

bool InteractiveBuffer::has() {
    // @inspiredBy https://stackoverflow.com/questions/55906580/how-to-do-non-blocking-keyboard-input-on-console-app-using-swift
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
}

int InteractiveBuffer::get() {
    if (!has())
        return -1;
    return getchar();
}

InteractiveBuffer::InteractiveBuffer(size_t maxSize)
        : maxSize(maxSize ? maxSize : DEFAULT_SIZE) {
    /* store old settings */
    tcgetattr(STDIN_FILENO, &oldTermios);
}

InteractiveBuffer::~InteractiveBuffer() {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
}

InteractiveBuffer &InteractiveBuffer::Start() {
    // @inspiredBy http://www.cplusplus.com/forum/unices/18395/
    struct termios newTermios{};
    newTermios = oldTermios;
    newTermios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
    return *this;
}

KeyboardDirection InteractiveBuffer::Retrieve(const KeyboardControls &controls) {
    using namespace chrono_literals;
    this_thread::sleep_for(500ms);

    int ch = get();
    while (ch != -1) {
        buffer.push_back(static_cast<char>( ch ));
        if (buffer.size() > maxSize)
            buffer.pop_front();

        ch = get();
    }

    KeyboardDirection last = KeyboardDirection::NONE;

    auto it = buffer.begin();
    while (it != buffer.end()) {
        bool find = false;
        for (size_t i = 0; i < controls.keybinds.size(); ++i) {
            if (*it == controls.keybinds[i]) {
                find = true;
                last = static_cast<KeyboardDirection>( i );
                it = buffer.erase(it);
                break;
            }
        }

        if (!find) {
            ++it;
        }
    }

    return last;
}

InteractiveBuffer &InteractiveBuffer::Stop() {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
    return *this;
}
