#pragma once 

#include <unordered_map>
#include <string>
#include <functional>

#include <SDL2/SDL.h>

#include "EmuInterfaceSetupHelper.hpp"

class EmuTextInputHelper : public EmuInterfaceSetupHelper<std::unordered_map<SDL_EventType, std::function<void (const SDL_Event& e)>>& > {
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

    void InterfaceSetup(std::unordered_map<SDL_EventType, std::function<void (const SDL_Event& e)>>& event_mapper) override
    {
        event_mapper.insert(std::make_pair(SDL_EventType::SDL_TEXTINPUT, std::bind(&EmuTextInputHelper::TextHandler, this, std::placeholders::_1)));
        event_mapper.insert(std::make_pair(SDL_EventType::SDL_KEYDOWN, std::bind(&EmuTextInputHelper::TextHandler, this, std::placeholders::_1)));
    }
};