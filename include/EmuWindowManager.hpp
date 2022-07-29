#pragma once

#include "EmuBaseWindow.hpp"

class EmuWindowManager {
private:
    void EventMapperHelpr(uint32_t win_id, const SDL_Event& e);

    std::unordered_map<uint32_t, std::shared_ptr<EmuBaseWindow>> _window_mapper;
public:
    EmuWindowManager();

    void AddNewWindow(std::shared_ptr<EmuBaseWindow> window);

    void EmuWindowManagerEventLoop();
};