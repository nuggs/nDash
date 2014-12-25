/*
 * nDash - A simple dashboard for Assetto Corsa, for external displays or other
 *         systems on the network.
 ******************************************************************************
 * Copyright (c) 2014 Anthony Goins
 *
 */

#ifndef PLUGIN_H
#define PLUGIN_H

#include "Config.h"
#include "SharedLibrary.h"

#include <string>

namespace nDash {
    class Kernel;

    /**
     * Representation of a plugin
     */
    class Plugin {
        public:
            /**
             * Initializes and loads a plugin
             * @param filename Filename of the plugin to load
             */
            NDASH_API Plugin(const std::string &filename);

            /**
             * Copies an existing plugin instance
             */
            NDASH_API Plugin(const Plugin &other);

            /**
             * Unloads the plugin
             */
            NDASH_API ~Plugin();

            /**
             * Queries the plugin for its expected engine version
             */
            NDASH_API int getEngineVersion() const {
                return this->getEngineVersionAddress();
            }

            /**
             * Register the plugin to a kernel
             * @param kernel Kernel the plugin should register to
             */
            NDASH_API void registerPlugin(Kernel &kernel) {
                this->registerPluginAddress(kernel);
            }

            /**
             * Creates a copy of the plugin instance
             */
            Plugin &operator =(const Plugin &other);

        private:
            /**
             * Signature for the version query function
             */
            typedef int GetEngineVersionFunction();

            /**
             * Signature for the plugin's registration function
             */
            typedef void RegisterPluginFunction(Kernel &);

            /**
             * Handle of the loaded shared library
             */
            SharedLibrary::HandleType sharedLibraryHandle;

            /**
             * Number of references that exist to the shared library
             */
            size_t *referenceCount;

            /**
             * Function to query for the expected engine version
             */
            GetEngineVersionFunction *getEngineVersionAddress;

            /**
             * Registers the plugin with the kernel
             */
            RegisterPluginFunction *registerPluginAddress;
    };
} // nDash

#endif // PLUGIN_H
