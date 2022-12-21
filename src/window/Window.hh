#ifndef _FRAMEWORK_WINDOW_HEADER_
#define _FRAMEWORK_WINDOW_HEADER_

#include <SDL2/SDL.h>

#include <string_view>
#include <map>
#include <functional>

class Window
{
public:
    Window();
    ~Window();

    void SetTitle(const std::string_view title);
    void SetSize(const unsigned int width, const unsigned int height);
    void SetPos(const unsigned int x, const unsigned int y);
    void SetFPS(const unsigned int fps);
    void SetWindowFlags(const SDL_WindowFlags flags);
    void PushRenderFunction(std::function<void(Window *window)> fn);
    void PushRenderer(const int idx, SDL_Renderer* renderer);

    void StartGameLoop();

    constexpr const std::string_view GetTitle() { return this->title; };
    constexpr const unsigned int GetWidth() { return this->width; };
    constexpr const unsigned int GetHeight() { return this->height; };
    constexpr const unsigned int GetPosX() { return this->x; };
    constexpr const unsigned int GetPosY() { return this->y; };
    constexpr const unsigned int GetFPS() { return this->fps; };
    constexpr const SDL_WindowFlags GetWindowFlags() { return this->flags; };

    SDL_Renderer *GetRenderer(int idx) { return this->renderers.at(idx); };

protected:
private:
    SDL_Window *window = nullptr;
    std::string_view title = "framework";
    unsigned int width = 800;
    unsigned int height = 640;
    unsigned int x = SDL_WINDOWPOS_UNDEFINED;
    unsigned int y = SDL_WINDOWPOS_UNDEFINED;
    unsigned int fps = 60;
    SDL_WindowFlags flags = SDL_WINDOW_SHOWN;
    SDL_Event event;

    std::vector<std::function<void(Window *window)>> rendering_functions;
    std::map<int, SDL_Renderer *> renderers;
};

#endif