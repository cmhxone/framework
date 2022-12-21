#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <glog/logging.h>

#include "framework/Framework.hh"
#include "window/Window.hh"
#include "ini/Ini.hh"

int main(int argc, char *argv[])
{

    if (!framework::InitFramework(&argc, argv))
    {
        return EXIT_FAILURE;
    }

    std::unique_ptr<Window> window(new Window());
    std::string title = Ini::GetInstance()->GetReader().GetString("window", "title", "framework").data();
    unsigned int width = Ini::GetInstance()->GetReader().GetInteger("window", "width", 800);
    unsigned int height = Ini::GetInstance()->GetReader().GetInteger("window", "height", 600);
    unsigned int pos_x = Ini::GetInstance()->GetReader().GetInteger("window", "x", 0);
    unsigned int pos_y = Ini::GetInstance()->GetReader().GetInteger("window", "y", 0);
    unsigned int fps = Ini::GetInstance()->GetReader().GetInteger("window", "fps", 60);

    window->SetTitle(title);
    window->SetSize(width, height);
    window->SetPos(pos_x == 0 ? SDL_WINDOWPOS_UNDEFINED : pos_x, pos_y == 0 ? SDL_WINDOWPOS_UNDEFINED : pos_y);
    window->SetFPS(fps == 0 ? 60 : fps);

    window->PushRenderFunction([](Window* window) {
        SDL_RenderClear(window->GetRenderer(-1));
        SDL_SetRenderDrawColor(window->GetRenderer(-1), 0x10, 0x20, 0x50, 0xFF);
        SDL_RenderFillRect(window->GetRenderer(-1), nullptr);
        SDL_RenderPresent(window->GetRenderer(-1));
    });

    window->StartGameLoop();

    framework::DestroyFramework();
    return EXIT_SUCCESS;
}