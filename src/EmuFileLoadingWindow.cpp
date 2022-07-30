#include <SDL2/SDL_ttf.h>

#include "EmuFileLoadingWindow.hpp"
#include "WindowUtilities/SdlColorHelper.hpp"

EmuFileLoadingWindow::EmuFileLoadingWindow(std::string && window_title, EmuBaseWindow::WindowPos && window_pos, uint32_t window_flags, TransferFile transfer_function) :  
    EmuBaseWindow(std::move("File_Load_Window"), std::move(window_pos), std::move(window_flags), COLOR_RED),
    _transfer_function(std::move(transfer_function)),
    _input_text_line_helper(_event_mapper, std::bind(&EmuFileLoadingWindow::LineChecker, this, std::placeholders::_1)),
    _output_text_helper("../fonts/PressStart2P-Regular.ttf", 22, COLOR_WHITE)
{
}

void EmuFileLoadingWindow::EmuRenderWindow()
{
    SDL_RenderClear(_renderer.get());
    const std::string line = _input_text_line_helper.GetLine();
    std::shared_ptr<SDL_Texture> texture(_output_text_helper.CreateTextTexture(line, _renderer));

    SDL_Rect Message_rect = _output_text_helper.GetTrueTextRectangleDim(line);
    Message_rect.x = (_window_pos.dim.width < Message_rect.w)? _window_pos.dim.width - Message_rect.w : 0;
    Message_rect.y = 2;

    SDL_RenderCopy(_renderer.get(), texture.get(), NULL, &Message_rect);
    SDL_RenderPresent(_renderer.get());
}

// LineChecker This function checks the line so we will be able to load a file from the fs
void EmuFileLoadingWindow::LineChecker(const std::string& str)
{
    bool flag = false;
    std::fstream fs(str, std::fstream::in | std::fstream::out | std::fstream::binary);
    if (fs.is_open())
    {
        _transfer_function(std::move(fs));
        flag = true;
    }
    _input_text_line_helper.SetAfterEnterMessage(((flag)? "SUCCESS" : "FAIL"));
}