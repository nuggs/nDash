/*
 * nDash - A simple dashboard for Assetto Corsa, for external displays or other
 *         systems on the network.
 ******************************************************************************
 * Copyright (c) 2014 Anthony Goins
 *
 */

#ifndef CONFIG_H
#define CONFIG_H

#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_APP)
    #define NDASH_WINRT 1
#elif defined(WIN32) || defined(_WIN32)
    #define NDASH_WIN32 1
#else
    #define NDASH_LINUX 1
#endif

// Decides whether symbols are imported from a dll (client app) or exported to
// a dll (nDash library). The NDASH_SOURCE symbol is defined by
// all source files of the library, so you don't have to worry about a thing.
#if defined(_MSC_VER)
    #if defined(NDASH_STATICLIB)
        #define NDASH_API
    #else
        #if defined(NDASH_SOURCE)
            // If we are building the DLL, export the symbols tagged like this
            #define NDASH_API __declspec(dllexport)
        #else
            // If we are consuming the DLL, import the symbols tagged like this
            #define NDASH_API __declspec(dllimport)
        #endif
    #endif
#elif defined(__GNUC__)
    #if defined(NDASH_STATICLIB)
        #define NDASH_API
    #else
        #if defined(NDASH_SOURCE)
            #define NDASH_API __attribute__ ((visibility ("default")))
        #else
            // If you use -fvisibility=hidden in GCC, exception handling and RTTI
            // would break if visibility wasn't set during export _and_ import
            // because GCC would immediately forget all type infos encountered.
            // See http://gcc.gnu.org/wiki/Visibility
            #define NDASH_API __attribute__ ((visibility ("default")))
        #endif
    #endif
#else
    #error Unknown compiler, please implement shared library macros
#endif

#endif // CONFIG_H
