#pragma once

#include <string>

#include "EmuBaseWindow.hpp"
#include "EmuTextInputHelper.hpp"
#include "Cpu.hpp"

class EmuMemoryWindow : public EmuBaseWindow, public EmuTextInputHelper {
private:
    struct MemoryRange {
        uint32_t start;
        uint32_t size;
    };

    void LineChecker() override;

    std::shared_ptr<Cpu> _cpu;
    MemoryRange _mem_range;
public:
    EmuMemoryWindow(std::string && window_title, EmuBaseWindow::WindowPos && window_pos, uint32_t window_flags);
    void EmuRenderWindow() override;
    ~EmuMemoryWindow() = default;
};