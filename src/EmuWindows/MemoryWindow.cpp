#include "EmuWindows/MemoryWindow.hpp"
#include "WindowUtilities/SdlColorHelper.hpp"

MemoryWindow::MemoryWindow() :
    BaseWindow("Memory_View_Window", SDL_Rect({0,0,100,100}), 0, COLOR_WHITE),
    _input_text_line_helper(_event_mapper, std::bind(&MemoryWindow::LineChecker, this, std::placeholders::_1)),
    _mem_range({0,0})
{
}

void MemoryWindow::RenderWindow()
{
    // TODO: render window
}

// LineChecker This function checks the line so we will be able to load a new memory range configuration
void MemoryWindow::LineChecker(const std::string& line)
{
    uint32_t start = 0;
    uint32_t size = 0;
    uint8_t num_count;
    bool flag = true;
    std::string tmp;

    if (std::count(line.begin(), line.end(), '_') != 1)
    {
        flag = false;
    }
    for(auto it = line.begin(); it != line.end() && flag; ++it) {
        if (*it == ',')
        {
            if (num_count == 0)
            {
                start = std::stol(tmp, nullptr, 16);
                num_count++;
            }
            else if (num_count == 1)
            {
                size = std::stol(tmp, nullptr, 16);
                num_count++;
            }
            else
            {
                flag = false;
            }
            tmp.clear();
        }
        else
        {
            if (std::isxdigit(*it))
            {
                tmp.push_back(*it);
            }
            else
            {
                flag = false;
            }
        }
    }
    if (flag)
    {
        _mem_range.start = start;
        _mem_range.size = size;
    }
    _input_text_line_helper.SetAfterEnterMessage(((flag)? "SUCCESS" : "FAIL"));
}