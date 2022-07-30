#pragma once 

#include <string>
#include <fstream>

#include "EmuBaseWindow.hpp"

#include "WindowUtilities/InputTextLineHelper.hpp"
#include "WindowUtilities/OutputTextHelper.hpp"

class EmuFileLoadingWindow : public EmuBaseWindow {
public:
    using TransferFile = std::function<void (std::fstream file)>;
    EmuFileLoadingWindow(std::string && window_title, EmuBaseWindow::WindowPos && window_pos, uint32_t window_flags, TransferFile transfer_function);

    void EmuRenderWindow() override;
    ~EmuFileLoadingWindow() = default;
private:
    void LineChecker(const std::string&);

    InputTextLineHelper _input_text_line_helper;
    OutputTextHelper _output_text_helper;
    TransferFile _transfer_function;
};