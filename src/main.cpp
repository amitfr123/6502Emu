#include <iostream>
#include <memory.h>

#include "EmuWindows/WindowManager.hpp"
#include "EmuWindows/FileLoadingWindow.hpp"

static void func(std::fstream && file)
{
    std::cout << "cool" << std::endl;
    file.close();
}

int main()
{
    WindowManager m;
    std::shared_ptr<FileLoadingWindow> win = std::make_shared<FileLoadingWindow>(std::bind(&func, std::placeholders::_1));
    m.AddNewWindow(win);
    m.EmuWindowManagerEventLoop();
    return 0;
}