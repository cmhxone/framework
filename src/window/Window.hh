#ifndef _FRAMEWORK_WINDOW_HEADER_
#define _FRAMEWORK_WINDOW_HEADER_

#include <SDL2/SDL.h>
#include <string_view>
#include <vector>
#include <functional>

class Window
{
public:
    Window();
    ~Window();

    void SetTitle(const std::string_view title);
    void SetSize(const unsigned int width, const unsigned int height);
    void SetPos(const unsigned int x, const unsigned int y);
    void SetWindowFlags(const SDL_WindowFlags flags);
    void PushRenderFunction(std::function<void()> fn);

    void StartGameLoop();

    constexpr const std::string_view GetTitle();
    constexpr const unsigned int GetWidth();
    constexpr const unsigned int GetHeight();
    constexpr const unsigned int GetPosX();
    constexpr const unsigned int GetPosY();
    constexpr const SDL_WindowFlags GetWindowFlags();

protected:
private:
    SDL_Window *window = nullptr;
    std::string_view title = "framework";
    unsigned int width = 800;
    unsigned int height = 640;
    unsigned int x = SDL_WINDOWPOS_UNDEFINED;
    unsigned int y = SDL_WINDOWPOS_UNDEFINED;
    SDL_WindowFlags flags = SDL_WINDOW_SHOWN;
    SDL_Event event;

    std::vector<std::function<void()>> rendering_functions;
};

#endif