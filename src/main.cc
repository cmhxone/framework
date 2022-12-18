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
    window->SetTitle(Ini::GetInstance()->GetReader().GetString("window", "title", "framework"));
    window->SetSize(Ini::GetInstance()->GetReader().GetInteger("window", "width", 800),
                    Ini::GetInstance()->GetReader().GetInteger("window", "height", 600));
    window->SetPos(Ini::GetInstance()->GetReader().GetInteger("window", "x", 0),
                   Ini::GetInstance()->GetReader().GetInteger("window", "y", 0));

    framework::DestroyFramework();
    return EXIT_SUCCESS;
}