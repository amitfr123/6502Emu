#include <iostream>
#include "../include/EmuFileLoadingWindow.hpp"

EmuFileLoadingWindow::EmuFileLoadingWindow(std::string && window_title, EmuBaseWindow::WindowPos && window_pos, uint32_t window_flags, TransferFile transfer_function) :  
    EmuBaseWindow(std::move(window_title), std::move(window_pos), std::move(window_flags)),
    _transfer_function(transfer_function)
{
    _event_mapper.insert(std::make_pair(SDL_EventType::SDL_TEXTINPUT, std::bind(&EmuFileLoadingWindow::TextHandler, this, std::placeholders::_1)));
    _event_mapper.insert(std::make_pair(SDL_EventType::SDL_KEYDOWN, std::bind(&EmuFileLoadingWindow::TextHandler, this, std::placeholders::_1)));
}

void EmuFileLoadingWindow::EmuRenderWindow()
{
    // TODO: render window
}

// LineChecker This function checks the line so we will be able to load a file from the fs
void EmuFileLoadingWindow::LineChecker()
{
    bool flag = false;
    std::fstream fs(_line, std::fstream::in | std::fstream::out | std::fstream::binary);
    if (fs.is_open())
    {
        _transfer_function(std::move(fs));
    }
    SetAfterEnterMessage(std::move(((flag)? "SUCCESS" : "FAIL")));
}