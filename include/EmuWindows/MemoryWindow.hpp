#pragma once

#include <string>

#include "Cpu.hpp"

#include "BaseWindow.hpp"

#include "WindowUtilities/InputTextLineHelper.hpp"

class MemoryWindow : public BaseWindow {
public:
    MemoryWindow();
    void RenderWindow() override;
    ~MemoryWindow() = default;
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