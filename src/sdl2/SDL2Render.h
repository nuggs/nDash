/*
 * nDash - A simple dashboard for Assetto Corsa, for external displays or other
 *         systems on the network.
 ******************************************************************************
 * Copyright (c) 2014 Anthony Goins
 *
 */

#ifndef SDL2RENDER_H
#define SDL2RENDER_H

// Decides whether symbols are imported from a dll (client app) or exported to
// a dll (SDL2Render library). The SDL2PLUGIN_SOURCE symbol is defined by
// all source files of the library, so you don't have to worry about a thing.
#if defined(_MSC_VER)
    #if defined(SDL2PLUGIN_STATICLIB)
        #define SDL2PLUGIN_API
    #else
        #if defined(SDL2PLUGIN_SOURCE)
            // If we are building the DLL, export the symbols tagged like this
            #define SDL2PLUGIN_API __declspec(dllexport)
        #else
            // If we are consuming the DLL, import the symbols tagged like this
            #define SDL2PLUGIN_API __declspec(dllimport)
        #endif
    #endif
#elif defined(__GNUC__)
    #if defined(SDL2PLUGIN_STATICLIB)
        #define SDL2PLUGIN_API
    #else
        #if defined(SDL2PLUGIN_SOURCE)
            #define SDL2PLUGIN_API __attribute__ ((visibility ("default")))
        #else
            // If you use -fvisibility=hidden in GCC, exception handling and RTTI
            // would break if visibility wasn't set during export _and_ import
            // because GCC would immediately forget all type infos encountered.
            // See http://gcc.gnu.org/wiki/Visibility
            #define SDL2PLUGIN_API __attribute__ ((visibility ("default")))
        #endif
    #endif
#else
    #error Unknown compiler, please implement shared library macros
#endif

#endif // SDL2RENDER_H
