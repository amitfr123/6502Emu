#pragma once 

#include <string>

#include <SDL2/SDL.h>

class EmuTextInputHelper {
protected:
    enum class LineState
    {
        READY,
        POST_ENTER
    };
    void SetAfterEnterMessage(std::string && str);
    void TextHandler(const SDL_Event& e);

    virtual void LineChecker() = 0;
    LineState _line_state = LineState::READY;
    std::string _line;
};