/*
 * nDash - A simple dashboard for Assetto Corsa, for external displays or other
 *         systems on the network.
 ******************************************************************************
 * Copyright (c) 2014 Anthony Goins
 *
 */

#ifndef SHAREDLIBRARY_H
#define SHAREDLIBRARY_H

#include "Config.h"
#include <string>
#include <stdexcept>

#if defined(NDASH_WIN32)
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <windows.h>
#elif defined(NDASH_LINUX)
#include <dlfcn.h>
#else
#error No shared library functions detected for your system.
#endif

namespace nDash {
#if defined(NDASH_WIN32)
    /**
     * Shared library loading and access on windows
     */
    class SharedLibrary {
        /**
         * Handle by which DLLs are referenced
         */
        public: typedef HMODULE HandleType;

        /**
         * Loads the DLL from the specified path
         * @param path Path of the DLL that will be loaded
         */
        public: NDASH_API static HandleType Load(const std::string &path) {
            std::string pathWithExtension = std::string(".\\plugins\\") + path + ".dll";

            HMODULE moduleHandle = ::LoadLibraryA(pathWithExtension.c_str());
            if(moduleHandle == NULL) {
                throw std::runtime_error("Could not load DLL");
            }
            return moduleHandle;
        }

        /**
         * Unloads the DLL with the specified handle
         * @param sharedLibraryHandle Handle of the DLL that will be unloaded
         */
        public: NDASH_API static void Unload(HandleType sharedLibraryHandle) {
            BOOL result = ::FreeLibrary(sharedLibraryHandle);
            if(result == FALSE) {
                throw std::runtime_error("Could not unload DLL");
            }
        }

        /**
         * Looks up a function exported by the DLL</summary>
         * @param sharedLibraryHandle Handle of the DLL in which the function will be looked up
         * @param functionName Name of the function to look up
         * @return A pointer to the specified function
         */
        public: template<typename TSignature>
        static TSignature *GetFunctionPointer(HandleType sharedLibraryHandle, const std::string &functionName) {
            FARPROC functionAddress = ::GetProcAddress(sharedLibraryHandle, functionName.c_str());
            if(functionAddress == NULL) {
                throw std::runtime_error("Could not find exported function");
            }
            return reinterpret_cast<TSignature *>(functionAddress);
        }
    };
#endif

#if defined(NDASH_LINUX)
    /**
     * Shared library loading and access on UNIX and GNU/Linux
     */
    class SharedLibrary {
            /**
         * Handle by which shared objects are referenced
         */
        public: typedef void * HandleType;

        /**
         * Loads the shared object from the specified path
         * @param path Path of the shared object that will be loaded
         */
        public: NDASH_API static HandleType Load(const std::string &path) {
            std::string pathWithExtension = std::string("./plugins/lib") + path + ".so";

            void *sharedObject = ::dlopen(pathWithExtension.c_str(), RTLD_NOW);
            if(sharedObject == NULL) {
                throw std::runtime_error(std::string("Could not load '") + pathWithExtension + "'");
            }
            return sharedObject;
        }

        /**
         * Unloads the shared object with the specified handle
         * @param sharedLibraryHandle Handle of the shared object that will be unloaded
         */
        public: NDASH_API static void Unload(HandleType sharedLibraryHandle) {
            int result = ::dlclose(sharedLibraryHandle);
            if(result != 0) {
                throw std::runtime_error("Could not unload shared object");
            }
        }

        /**
         * Looks up a function exported by the DLL</summary>
         * @param sharedLibraryHandle Handle of the shared object in which the function will be looked up
         * @param functionName Name of the function to look up
         * @return A pointer to the specified function
         */
        public: template<typename TSignature>
        static TSignature *GetFunctionPointer(HandleType sharedLibraryHandle, const std::string &functionName) {
            ::dlerror();

            void *functionAddress = ::dlsym(sharedLibraryHandle, functionName.c_str());

            const char *error = ::dlerror();
            if(error != NULL) {
                throw std::runtime_error("Could not find exported function");
            }
            return reinterpret_cast<TSignature *>(functionAddress);
        }
    };
#endif

} // nDash

#endif // SHAREDLIBRARY_H
