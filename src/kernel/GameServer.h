/*
 * nDash - A simple dashboard for Assetto Corsa, for external displays or other
 *         systems on the network.
 ******************************************************************************
 * Copyright (c) 2014 Anthony Goins
 *
 */

#ifndef GAMESERVER_H
#define GAMESERVER_H

#include "Config.h"
#include <vector>
#include <memory>
#include <string>

namespace nDash {
    class Game {}; // Dummy

    class GameServer {
        public: class GamePlugin {
            public: NDASH_API virtual const std::string &pluginInfo() const = 0;
            public: virtual ~GamePlugin() {}
            public: virtual void closeConnection() {}
            public: virtual const std::string &getName() const = 0;
            public: virtual int initGame() = 0;
            public: virtual int updateGame() = 0;
        };

        private: typedef std::vector<GamePlugin *> GamePluginVector;

        public: NDASH_API ~GameServer() {
            for (GamePluginVector::const_iterator it = this->gamePlugins.begin(); it != this->gamePlugins.end(); ++it) {
                delete *it;
            }
        }

        public: NDASH_API void addGamePlugin(std::unique_ptr<GamePlugin> gamePlugin) {
            this->gamePlugins.push_back(gamePlugin.release());
        }

        public: NDASH_API size_t getPluginCount() const {
            return this->gamePlugins.size();
        }

        public: NDASH_API GamePlugin &getPlugin(size_t Index) {
            return *this->gamePlugins.at(Index);
        }

        private: GamePluginVector gamePlugins;
    };
} // nDash

#endif // GAMESERVER_H
