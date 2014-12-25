/*
 * nDash - A simple dashboard for Assetto Corsa, for external displays or other
 *         systems on the network.
 ******************************************************************************
 * Copyright (c) 2014 Anthony Goins
 *
 */

#ifndef KERNEL_H
#define KERNEL_H

#include "Config.h"
#include "GraphicsServer.h"
#include "GameServer.h"
#include "Plugin.h"

#include <iostream>
#include <string>
#include <map>

namespace nDash {
    /**
     * The engine's core
     */
    class Kernel {
        /**
         * Map of plugins by their associated file names
         */
        typedef std::map<std::string, Plugin> PluginMap;

        public:
            /**
             * Accesses the graphics server
             */
            NDASH_API GraphicsServer &getGraphicsServer() {
                return this->graphicsServer;
            }

            NDASH_API GameServer &getGameServer() {
                return this->gameServer;
            }

            /**
             * Loads a plugin
             * @param filename File the plugin will be loaded from
             */
            NDASH_API void loadPlugin(const std::string &filename) {
                if(this->loadedPlugins.find(filename) == this->loadedPlugins.end()) {
                    this->loadedPlugins.insert(PluginMap::value_type(filename, Plugin(filename))).first->second.registerPlugin(*this);
                    std::cout << "** Loading: " << filename << std::endl;
                }
            }

        private:
            /**
             * All plugins currently loaded
             */
            PluginMap loadedPlugins;

            /**
             * Manages graphics-related tasks for the engine
             */
            GraphicsServer graphicsServer;

            /**
             * Manages game related tasks for the engine
             */
            GameServer gameServer;
    };
} // nDash

#endif // KERNEL_H
