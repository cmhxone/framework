#ifndef _FRAMEWORK_FRAMEWORK_HEADER_
#define _FRAMEWORK_FRAMEWORK_HEADER_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <glog/logging.h>

/**
 * @brief framework namespace
 *
 */
namespace framework
{

    /**
     * @brief Initialize libraries
     *
     * @param argc
     * @param argv
     * @return true
     * @return false
     */
    bool InitFramework(int *argc, char *argv[])
    {
        bool result = false;

        // init glog library
        google::InitGoogleLogging(argv[0]);
        gflags::ParseCommandLineFlags(argc, &argv, true);
        LOG(INFO) << "glog Initialized";

        // init SDL library
        LOG(INFO) << "Initializing SDL";
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            LOG(INFO) << "Failed to initialize SDL, msg: " << SDL_GetError();
            return result;
        }
        LOG(INFO) << "SDL Initialized";

        // init SDL_image library
        LOG(INFO) << "Initializing SDL_image";
        if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != (IMG_INIT_JPG | IMG_INIT_PNG))
        {
            LOG(INFO) << "Failed to initialize SDL_image, msg: " << IMG_GetError();
            return result;
        }
        LOG(INFO) << "SDL_image Initialized";

        // init SDL_mixer library
        LOG(INFO) << "Initializing SDL_mixer";
        if (Mix_Init(MIX_INIT_OGG) != MIX_INIT_OGG)
        {
            LOG(INFO) << "Failed to initialize SDL_mixer, msg: " << Mix_GetError();
            return result;
        }
        LOG(INFO) << "SDL_mixer Initialized";

        // init SDL_ttf library
        LOG(INFO) << "Initializing SDL_ttf";
        if (TTF_Init() != 0)
        {
            LOG(INFO) << "Failed to initialize SDL_ttf, msg: " << TTF_GetError();
            return result;
        }
        LOG(INFO) << "SDL_ttf Initialized";

        result = true;
        return result;
    }

    /**
     * @brief Destroy libraries
     *
     */
    void DestroyFramework()
    {
        google::ShutdownGoogleLogging();
        TTF_Quit();
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
    }
}

#endif