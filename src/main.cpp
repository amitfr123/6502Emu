#include <iostream>
#include <memory.h>

#include "EmuWindowManager.hpp"
#include "EmuFileLoadingWindow.hpp"

static void func(std::fstream && file)
{
    std::cout << "cool" << std::endl;
    file.close();
}

int main()
{
    EmuWindowManager m;
    std::string t = "wow";
    EmuBaseWindow::WindowPos pos;
    pos.dim.hight = 24;
    pos.dim.width = 500;
    pos.point.x = 0;
    pos.point.y = 0;
    std::shared_ptr<EmuFileLoadingWindow> win = std::make_shared<EmuFileLoadingWindow>(std::move(t), std::move(pos), SDL_WINDOW_OPENGL, std::bind(&func, std::placeholders::_1));
    win->EmuInitWindow();
    m.AddNewWindow(win);
    m.EmuWindowManagerEventLoop();
    return 0;
}