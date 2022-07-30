#pragma once

#include <SDL2/SDL.h>

#include <unordered_map>
#include <memory>
#include <string>
#include <functional>

class EmuBaseWindow {
public:
    struct WindowPos
    {
        struct WindowPosPoint
        {
            uint32_t x;
            uint32_t y;
        };
        struct WindowPosDim
        {
            uint32_t width;
            uint32_t hight;
        };
        WindowPosPoint point;
        WindowPosDim dim;
    };

    bool EmuInitWindow();
    void EmuHideWindow();
    void EmuShowWindow();
    bool EmuIsWinodwHidden();
    void EmuEventHandler(const SDL_Event& e);
    uint32_t EmuGetWindowId();
    virtual void EmuRenderWindow(){}
    virtual ~EmuBaseWindow() = default;

protected:
    using EventHandlerFunction = std::function<void (const SDL_Event& e)>;

    EmuBaseWindow(std::string && window_title, WindowPos && window_pos, uint32_t window_flags, SDL_Color && window_background);
    
    std::unordered_map<SDL_EventType, EventHandlerFunction> _event_mapper;
    std::shared_ptr<SDL_Window> _window;
    std::shared_ptr<SDL_Renderer> _renderer;
    std::string _window_title;
    WindowPos _window_pos;
    uint32_t _window_flags;
    SDL_Color _window_background;
};