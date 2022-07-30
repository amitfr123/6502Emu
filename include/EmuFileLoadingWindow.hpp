#pragma once 

#include <string>
#include <fstream>

#include "EmuBaseWindow.hpp"
#include "EmuTextInputHelper.hpp"
#include "EmuTextOutputHelper.hpp"

class EmuFileLoadingWindow : public EmuBaseWindow, public EmuTextInputHelper, public EmuTextOutputHelper {
public:
    using TransferFile = std::function<void (std::fstream && file)>;
    EmuFileLoadingWindow(std::string && window_title, EmuBaseWindow::WindowPos && window_pos, uint32_t window_flags, TransferFile transfer_function);

    void EmuRenderWindow() override;
    ~EmuFileLoadingWindow() = default;
private:
    void LineChecker() override;

    TransferFile _transfer_function;
};