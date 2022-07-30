#include <iostream>
#include <memory.h>

#include "EmuWindows/WindowManager.hpp"
#include "EmuWindows/FileLoadingWindow.hpp"

static void func(std::fstream file, std::string file_path)
{
    std::cout << file_path << std::endl;
    file.close();
}

int main()
{
    WindowManager m;
    std::shared_ptr<FileLoadingWindow> win = std::make_shared<FileLoadingWindow>(std::bind(&func, std::placeholders::_1, std::placeholders::_2));
    m.AddNewWindow(win);
    m.EmuWindowManagerEventLoop();
    return 0;
}