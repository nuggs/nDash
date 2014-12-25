/*
 * nDash - A simple dashboard for Assetto Corsa, for external displays or other
 *         systems on the network.
 ******************************************************************************
 * Copyright (c) 2014 Anthony Goins
 *
 */

#include "../kernel/Kernel.h"
#include <cstdlib>
#include <iostream>
#include <thread>
#include <stdexcept>

using namespace std;
using namespace nDash;

/**
 * Example method that lists available graphics drivers
 * @param graphicsServer Graphics server
 */
void listGraphicsDrivers(GraphicsServer &graphicsServer) {
  for(size_t index = 0; index < graphicsServer.getDriverCount(); ++index) {
    cout << "\t" << graphicsServer.getDriver(index).getName() << " - " << graphicsServer.getDriver(index).pluginInfo() << endl;
  }

  if(graphicsServer.getDriverCount() == 0) {
    cout << "\t" << "None" << endl;
  }

  cout << endl;
}

/**
 * Example method that lists available game Plugins
 * @param graphicsServer Game server
 */
void listGamePlugins(GameServer &gameServer) {
  for(size_t index = 0; index < gameServer.getPluginCount(); ++index) {
    cout << "\t" << gameServer.getPlugin(index).getName() << " - " << gameServer.getPlugin(index).pluginInfo() << endl;
    gameServer.getPlugin(index).initGame();
  }

  if(gameServer.getPluginCount() == 0) {
    cout << "\t" << "None" << endl;
  }

  cout << endl;
}

/**
 * Program entry point
 */
#if defined(NDASH_WIN32)
INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) {
#else
int main(int argc, char *argv[]) {
#endif
    Kernel Core;
    bool running = true;

    try {
        cout << "Loading plugins..." << endl;
        Core.loadPlugin("SDL2");
        Core.loadPlugin("ACPlugin");
        cout << endl;

        cout << string(79, '*') << endl;
        cout << endl;

        cout << "Available graphics drivers:" << endl;
        listGraphicsDrivers(Core.getGraphicsServer());
        cout << "Available game plugins:" << endl;
        listGamePlugins(Core.getGameServer());
    } catch(const exception &exception) {
        cout << "Unhandled error: " << exception.what() << endl;
    }

    /* Update the plugins */
    while (running) {
        if (Core.getGameServer().getPlugin(0).updateGame()) {
            Core.getGameServer().getPlugin(0).closeConnection();
        }
    }

    return EXIT_SUCCESS;
}
