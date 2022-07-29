#include "../include/EmuTextInputHelper.hpp"

void EmuTextInputHelper::TextHandler(const SDL_Event& e)
{
    switch (e.type)
    {
    case SDL_EventType::SDL_KEYDOWN:
        if (e.key.keysym.sym == SDL_KeyCode::SDLK_BACKSPACE && _line.length() > 0)
        {
            _line.pop_back();
        }
        if (e.key.keysym.sym == SDL_KeyCode::SDLK_RETURN && _line.length() > 0)
        {
            EnterFunc();
        }
    break;
    case SDL_EventType::SDL_TEXTINPUT:
        _line.append(e.text.text);
    break;
    default:
        break;
    }
}