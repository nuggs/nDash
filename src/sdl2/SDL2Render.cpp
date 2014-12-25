/*
 * nDash - A simple dashboard for Assetto Corsa, for external displays or other
 *         systems on the network.
 ******************************************************************************
 * Copyright (c) 2014 Anthony Goins
 *
 */

#define SDL2PLUGIN_SOURCE 1

#include "SDL2Render.h"
#include "../kernel/Kernel.h"

using namespace std;

namespace nDash {
    /**
     * SDL2+OpenGL graphics driver
     */
    class SDL2GraphicsDriver : public GraphicsServer::GraphicsDriver {
        public: SDL2PLUGIN_API virtual const std::string &pluginInfo() const {
            static string info("SDL2 and OpenGL rendering engine");
            return info;
        }

        /**
         * Destroys SDL2 driver
         */
        public: SDL2PLUGIN_API virtual ~SDL2GraphicsDriver() {}

        /**
         * Gets the name of the graphics driver
         */
        public: SDL2PLUGIN_API virtual const std::string &getName() const {
            static string sName("SDL2");
            return sName;
        }

        /**
         * Creates a renderer
         */
        unique_ptr<Renderer> createRenderer() {
            return unique_ptr<Renderer>(new Renderer());
        }
    };

    /**
     * Retrieve the engine version we're going to expect
     */
    extern "C" SDL2PLUGIN_API int getEngineVersion() {
        return 1;
    }

    /**
     * Register the plugin to an engine kernel
     * @param kernel Kernel the plugin will register to
     */
    extern "C" SDL2PLUGIN_API void registerPlugin(Kernel &kernel) {
        kernel.getGraphicsServer().addGraphicsDriver(unique_ptr<GraphicsServer::GraphicsDriver>(new SDL2GraphicsDriver()));
    }

} // nDash
