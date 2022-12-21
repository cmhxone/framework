#include "Window.hh"

Window::Window()
{
    this->window = SDL_CreateWindow(this->title.data(), this->x, this->y, this->width, this->height, this->flags);
}

Window::~Window()
{
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
 * @brief Start window's gameloop
 *
 */
void Window::StartGameLoop()
{
    while (true)
    {
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
    }
}
