#include <SDL2/SDL_ttf.h>

#include "../include/EmuFileLoadingWindow.hpp"
#include "EmuSdlColorHelper.hpp"

EmuFileLoadingWindow::EmuFileLoadingWindow(std::string && window_title, EmuBaseWindow::WindowPos && window_pos, uint32_t window_flags, TransferFile transfer_function) :  
    EmuBaseWindow(std::move("File_Load_Window"), std::move(window_pos), std::move(window_flags), COLOR_RED),
    _transfer_function(transfer_function)
{
    EmuTextInputHelper::InterfaceSetup(_event_mapper);
    EmuTextOutputStyle s;
    s.font_path = "../fonts/PressStart2P-Regular.ttf";
    s.font_size = 24;
    s.text_color = COLOR_WHITE;
    EmuTextOutputHelper::InterfaceSetup(std::move(s));
}

void EmuFileLoadingWindow::EmuRenderWindow()
{
    SDL_RenderClear(_renderer.get());

    std::shared_ptr<SDL_Texture> texture(std::move(CreateTextTexture(_line, _renderer)));

    SDL_Rect Message_rect = EmuTextOutputHelper::GetTrueTextRectangleDim(_line);
    Message_rect.x = (_window_pos.dim.width < Message_rect.w)? _window_pos.dim.width - Message_rect.w : 0;
    Message_rect.y = 0;

    SDL_RenderCopy(_renderer.get(), texture.get(), NULL, &Message_rect);
    SDL_RenderPresent(_renderer.get());
}

// LineChecker This function checks the line so we will be able to load a file from the fs
void EmuFileLoadingWindow::LineChecker()
{
    bool flag = false;
    std::fstream fs(_line, std::fstream::in | std::fstream::out | std::fstream::binary);
    if (fs.is_open())
    {
        _transfer_function(std::move(fs));
        flag = true;
    }
    SetAfterEnterMessage(std::move(((flag)? "SUCCESS" : "FAIL")));
}