#include "../include/EmuMemoryWindow.hpp"

EmuMemoryWindow::EmuMemoryWindow(std::string && window_title, EmuBaseWindow::WindowPos && window_pos, uint32_t window_flags) :  
    EmuBaseWindow(std::move(window_title), std::move(window_pos), std::move(window_flags)),
    _mem_range({0,0})
{
    _event_mapper.insert(std::make_pair(SDL_EventType::SDL_TEXTINPUT, std::bind(&EmuMemoryWindow::TextHandler, this, std::placeholders::_1)));
    _event_mapper.insert(std::make_pair(SDL_EventType::SDL_KEYDOWN, std::bind(&EmuMemoryWindow::TextHandler, this, std::placeholders::_1)));
}

void EmuMemoryWindow::EmuRenderWindow()
{
    // TODO: render window
}

void EmuMemoryWindow::TextHandler(const SDL_Event& e)
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

void EmuMemoryWindow::LineChecker()
{
    uint32_t start = 0;
    uint32_t size = 0;
    uint8_t num_count;
    bool flag = true;
    std::string tmp;

    if (std::count(_line.begin(), _line.end(), '_') != 1)
    {
        flag = false;
    }
    for(auto it = _line.begin(); it != _line.end() && flag; ++it) {
        if (*it == ',')
        {
            if (num_count == 0)
            {
                start = std::stol(tmp, nullptr, 16);
                num_count++;
            }
            else if (num_count == 1)
            {
                size = std::stol(tmp, nullptr, 16);
                num_count++;
            }
            else
            {
                flag = false;
            }
            tmp.clear();
        }
        else
        {
            if (std::isxdigit(*it))
            {
                tmp.push_back(*it);
            }
            else
            {
                flag = false;
            }
        }
    }
    if (flag)
    {
        _mem_range.start = start;
        _mem_range.size = size;
    }
}