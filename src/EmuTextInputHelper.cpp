#include "../include/EmuTextInputHelper.hpp"

void EmuTextInputHelper::SetAfterEnterMessage(std::string && str)
{
    _line.clear();
    _line.append(str);
    _line_state = LineState::POST_ENTER;
}
void EmuTextInputHelper::TextHandler(const SDL_Event& e)
{
    if (_line_state == LineState::POST_ENTER)
    {
        _line.clear();
        _line_state = LineState::READY;
    }
    switch (e.type)
    {
    case SDL_EventType::SDL_KEYDOWN:
        if (e.key.keysym.sym == SDL_KeyCode::SDLK_BACKSPACE && _line.length() > 0)
        {
            _line.pop_back();
        }
        if (e.key.keysym.sym == SDL_KeyCode::SDLK_RETURN && _line.length() > 0)
        {
            LineChecker();
        }
    break;
    case SDL_EventType::SDL_TEXTINPUT:
        _line.append(e.text.text);
    break;
    default:
        break;
    }
}