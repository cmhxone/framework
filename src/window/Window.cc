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
 * @brief Get window title name
 *
 * @return const std::string_view
 */
constexpr const std::string_view Window::GetTitle()
{
    return this->title;
}

/**
 * @brief Get window screen width
 *
 * @return const unsigned int
 */
constexpr const unsigned int Window::GetWidth()
{
    return this->width;
}

/**
 * @brief Get window screen height
 *
 * @return const unsigned int
 */
constexpr const unsigned int Window::GetHeight()
{
    return this->height;
}

/**
 * @brief Get window displaying position(left)
 *
 * @return const unsigned int
 */
constexpr const unsigned int Window::GetPosX()
{
    return this->x;
}

/**
 * @brief Get window displaying position(top)
 *
 * @return const unsigned int
 */
constexpr const unsigned int Window::GetPosY()
{
    return this->y;
}

/**
 * @brief Get window displaying option flags
 *
 * @return const SDL_WindowFlags
 */
constexpr const SDL_WindowFlags Window::GetWindowFlags()
{
    return this->flags;
}
