#pragma once

#include <string>

#include "Cpu.hpp"

#include "EmuBaseWindow.hpp"

#include "WindowUtilities/InputTextLineHelper.hpp"

class EmuMemoryWindow : public EmuBaseWindow {
public:
    EmuMemoryWindow(std::string && window_title, EmuBaseWindow::WindowPos && window_pos, uint32_t window_flags);
    void EmuRenderWindow() override;
    ~EmuMemoryWindow() = default;
private:
    struct MemoryRange {
        uint32_t start;
        uint32_t size;
    };

    void LineChecker(const std::string&);

    InputTextLineHelper _input_text_line_helper;
    std::shared_ptr<Cpu> _cpu;
    MemoryRange _mem_range;
};