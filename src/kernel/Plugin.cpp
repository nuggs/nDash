/*
 * nDash - A simple dashboard for Assetto Corsa, for external displays or other
 *         systems on the network.
 ******************************************************************************
 * Copyright (c) 2014 Anthony Goins
 *
 */

#define NDASH_SOURCE 1

#include "Plugin.h"
#include <stdexcept>

using namespace std;

namespace nDash {
    Plugin::Plugin(const std::string &filename) : sharedLibraryHandle(0), referenceCount(0), getEngineVersionAddress(0), registerPluginAddress(0) {
        /* Try to load the plugin as a shared library */
        this->sharedLibraryHandle = SharedLibrary::Load(filename);

        /* Locate the plugin's exported functions */
        try {
            this->getEngineVersionAddress = SharedLibrary::GetFunctionPointer<GetEngineVersionFunction>(this->sharedLibraryHandle, "getEngineVersion");
            this->registerPluginAddress = SharedLibrary::GetFunctionPointer<RegisterPluginFunction>(this->sharedLibraryHandle, "registerPlugin");

            /* Initialize a new shared library reference counter */
            this->referenceCount = new size_t(1);
        } catch(std::exception &) {
            SharedLibrary::Unload(this->sharedLibraryHandle);
            throw;
        }
    }

    /**
     * Creates a copy of a plugin that has already been loaded.
     * Required to provide correct semantics for storing plugins in
     * an STL map container.
     * @param other Other plugin instance to copy
     */
    Plugin::Plugin(const Plugin &other) : sharedLibraryHandle(other.sharedLibraryHandle), referenceCount(other.referenceCount),
        getEngineVersionAddress(other.getEngineVersionAddress), registerPluginAddress(other.registerPluginAddress) {

        /* Increase shared object reference counter */
        if(this->referenceCount) {
            ++(*this->referenceCount);
        }
    }

    /**
     * Destroys the plugin, unloading its library when no more references to it exist.
     */
    Plugin::~Plugin() {
        int remainingReferences = --*(this->referenceCount);
        if(remainingReferences == 0) {
            delete this->referenceCount;
            SharedLibrary::Unload(this->sharedLibraryHandle);
        }
    }
} // nDash
