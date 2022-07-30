#include "../include/EmuBaseWindow.hpp"

EmuBaseWindow::EmuBaseWindow(std::string && window_title, WindowPos && window_pos, uint32_t window_flags, SDL_Color && window_background)
    :
    _window_title(window_title),
    _window_pos(window_pos),
    _window_flags(window_flags),
    _window_background(window_background)
{
}

bool EmuBaseWindow::EmuInitWindow()
{
    if (_renderer.get() != nullptr || _window.get() != nullptr)
    {
        return false;
    }
    _window.reset(SDL_CreateWindow(
        _window_title.c_str(),
        _window_pos.point.x,
        _window_pos.point.y,
        _window_pos.dim.width,
        _window_pos.dim.hight,
        _window_flags), &SDL_DestroyWindow);
    if (_window.get() == nullptr)
    {
        return false;
    }
    _renderer.reset(SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED), &SDL_DestroyRenderer);
    if (_renderer.get() == nullptr)
    {
        _window.reset();
        return false;
    }
    SDL_SetRenderDrawColor(_renderer.get(), _window_background.r, _window_background.g, _window_background.b, _window_background.a);
    SDL_RenderClear(_renderer.get());
    return true;
}   

void EmuBaseWindow::EmuHideWindow()
{
    if (_window.get() == nullptr)
    {
        return;
    }
    SDL_HideWindow(_window.get());
    _window_flags = SDL_GetWindowFlags(_window.get());
}

void EmuBaseWindow::EmuShowWindow()
{
    if (_window.get() == nullptr)
    {
        return;
    }
    SDL_ShowWindow(_window.get());
    _window_flags = SDL_GetWindowFlags(_window.get());
}

bool EmuBaseWindow::EmuIsWinodwHidden()
{
    return (_window_flags & SDL_WINDOW_MINIMIZED || _window_flags & SDL_WINDOW_HIDDEN);
}

void EmuBaseWindow::EmuEventHandler(const SDL_Event& e)
{
    auto handler = _event_mapper.find(static_cast<SDL_EventType>(e.type));
    if (handler == _event_mapper.end())
    {
        return;
    }
    handler->second(e);
}

uint32_t EmuBaseWindow::EmuGetWindowId()
{
    if (_window.get() == nullptr)
    {
        return 0;
    }
    return SDL_GetWindowID(_window.get());
}