#pragma once 

#include <string>

#include <SDL2/SDL.h>

class EmuTextInputHelper {
protected:
    void TextHandler(const SDL_Event& e);

    virtual void EnterFunc() = 0;
    std::string _line;
};