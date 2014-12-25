/*
 * nDash - A simple dashboard for Assetto Corsa, for external displays or other
 *         systems on the network.
 ******************************************************************************
 * Copyright (c) 2014 Anthony Goins
 *
 */

#ifndef ACPLUGIN_H
#define ACPLUGIN_H

#if defined(_MSC_VER)
    #if defined(ACLPLUGIN_STATICLIB)
        #define ACPLUGIN_API
    #else
        #if defined(ACPLUGIN_SOURCE)
            #define ACPLUGIN_API __declspec(dllexport)
        #else
            #define ACPLUGIN_API __declspec(dllimport)
        #endif
    #endif
#elif defined(__GNUC__)
    #if defined(ACPLUGIN_STATICLIB)
        #define OPENGLPLUGIN_API
    #else
        #if defined(ACPLUGIN_SOURCE)
            #define ACPLUGIN_API __attribute__ ((visibility ("default")))
        #else
            #define ACPLUGIN_API __attribute__ ((visibility ("default")))
        #endif
    #endif
#else
    #error Unknown compiler, please implement shared library macros
#endif

#endif // ACPLUGIN_H
