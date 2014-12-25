/*
 * nDash - A simple dashboard for Assetto Corsa, for external displays or other
 *         systems on the network.
 ******************************************************************************
 * Copyright (c) 2014 Anthony Goins
 *
 */

#ifndef GRAPHICSSERVER_H
#define GRAPHICSSERVER_H

#include "Config.h"
#include <vector>
#include <memory>
#include <string>

namespace nDash {
    class Renderer {}; // Dummy

    /// <summary>Manages graphics related stuff for the engine</summary>
    class GraphicsServer {
        /// <summary>Graphics driver interface for the engine</summary>
        public: class GraphicsDriver {
            public: NDASH_API virtual const std::string &pluginInfo() const = 0;
            /// <summary>Releases resources of a driver after use</summary>
            public: virtual ~GraphicsDriver() {}
            /// <summary>Gets the name of the graphics driver</summary>
            public: virtual const std::string &getName() const = 0;
            /// <summary>Creates a renderer using the driver's rendering API</summary>
            public: virtual std::unique_ptr<Renderer> createRenderer() = 0;
        };

        /// <summary>A vector of graphics drivers</summary>
        private: typedef std::vector<GraphicsDriver *> GraphicsDriverVector;

        /// <summary>Releases the resources of the graphics server</summary>
        public: NDASH_API ~GraphicsServer() {
            for (GraphicsDriverVector::const_iterator it = this->graphicsDrivers.begin(); it != this->graphicsDrivers.end(); ++it) {
                delete *it;
            }
        }

        /// <summary>Allows plugins to add new graphics drivers</summary>
        /// <param name="graphicsDriver">Graphics driver that will be added</param>
        public: NDASH_API void addGraphicsDriver(std::unique_ptr<GraphicsDriver> graphicsDriver) {
            this->graphicsDrivers.push_back(graphicsDriver.release());
        }

        /// <summary>Gets the total number of registered graphics drivers</summary>
        public: NDASH_API size_t getDriverCount() const {
            return this->graphicsDrivers.size();
        }

        /// <summary>Accesses a driver by its index</summary>
        public: NDASH_API GraphicsDriver &getDriver(size_t Index) {
            return *this->graphicsDrivers.at(Index);
        }

        /// <summary>All available graphics drivers</summary>
        private: GraphicsDriverVector graphicsDrivers;
    };
} // nDash

#endif // GRAPHICSSERVER_H
