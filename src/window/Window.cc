#include <chrono>
#include <thread>
#include <iomanip>

#include <glog/logging.h>

#include "Window.hh"

Window::Window()
{
    this->window = SDL_CreateWindow(this->title.data(), this->x, this->y, this->width, this->height, this->flags);
    this->PushRenderer(-1, SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED));
}

Window::~Window()
{
    for (std::pair<int, SDL_Renderer *> renderer : this->renderers)
    {
        SDL_DestroyRenderer(renderer.second);
    }
    SDL_DestroyWindow(this->window);
}

/**
 * @brief Set window title name
 *
 * @param title
 */
void Window::SetTitle(const std::string_view title)
{
    this->title = title;
    SDL_SetWindowTitle(this->window, title.data());
}

/**
 * @brief Set window screen size
 *
 * @param width
 * @param height
 */
void Window::SetSize(const unsigned int width, const unsigned int height)
{
    this->width = width;
    this->height = height;
    SDL_SetWindowSize(this->window, width, height);
}

/**
 * @brief Set window displaying position(top-left)
 *
 * @param x
 * @param y
 */
void Window::SetPos(const unsigned int x, const unsigned int y)
{
    this->x = x;
    this->y = y;
    SDL_SetWindowPosition(this->window, x, y);
}

/**
 * @brief Set window displaying frame per seconds
 *
 * @param fps
 */
void Window::SetFPS(const unsigned int fps)
{
    this->fps = fps;
}

/**
 * @brief Set window displaying option flags
 *
 * @param flags
 */
void Window::SetWindowFlags(const SDL_WindowFlags flags)
{
    this->flags = flags;

    SDL_SetWindowFullscreen(this->window, flags & (SDL_WindowFlags::SDL_WINDOW_FULLSCREEN | SDL_WINDOW_FULLSCREEN_DESKTOP));
    SDL_SetWindowAlwaysOnTop(this->window, (flags & SDL_WINDOW_ALWAYS_ON_TOP) > 0 ? SDL_bool::SDL_TRUE : SDL_bool::SDL_FALSE);
}

/**
 * @brief Push render-function to member vector
 *
 * @param fn
 */
void Window::PushRenderFunction(std::function<void(Window *window)> fn)
{
    this->rendering_functions.push_back(fn);
}

/**
 * @brief Push renderer to member map
 *
 * @param renderer
 */
void Window::PushRenderer(const int idx, SDL_Renderer *renderer)
{
    if (renderers.find(idx) == renderers.end())
    {
        this->renderers.insert({idx, renderer});
    }
    else
    {
        SDL_DestroyRenderer(this->renderers.at(idx));
        this->renderers.at(idx) = renderer;
    }
}

/**
 * @brief Start window's gameloop
 *
 */
void Window::StartGameLoop()
{
    std::chrono::system_clock::time_point start_time;
    std::chrono::system_clock::time_point end_time;
    std::chrono::duration<double> duration;
    double frame_capping_ms = (1.0 / this->fps) * 1'000.0;

    while (true)
    {
        start_time = std::chrono::system_clock::now();

        while (SDL_PollEvent(&this->event) != 0)
        {
            switch (this->event.type)
            {
            // Quit and terminate gameloop
            case SDL_QUIT:
                return;

            default:
                break;
            }
        }

        // Call render-functions
        for (auto fn : this->rendering_functions)
        {
            fn(this);
        }

        end_time = std::chrono::system_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

        // Debug logging delaytime
        DLOG(INFO) << "gameloop delaytime: " << std::fixed << std::setprecision(5) << duration.count() << "(ms)";

        // Frame capping
        if (duration.count() < frame_capping_ms)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds((long long)(frame_capping_ms - duration.count())));

            // Debug logging capping time
            DLOG(INFO) << "gameloop capping time: " << std::fixed << std::setprecision(5) << (long long)(frame_capping_ms - duration.count()) << "(ms)";
        }
    }
}
