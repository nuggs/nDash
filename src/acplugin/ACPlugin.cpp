/*
 * nDash - A simple dashboard for Assetto Corsa, for external displays or other
 *         systems on the network.
 ******************************************************************************
 * Copyright (c) 2014 Anthony Goins
 *
 */

#define ACPLUGIN_SOURCE 1

#include "ACPlugin.h"
#include "../kernel/Kernel.h"
#include <cstdio>

#if defined(NDASH_WIN32)
#include <winsock2.h>
#include <ws2tcpip.h>
#elif defined(NDASH_LINUX)
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>
const int INVALID_SOCKET = -1;
#endif

using namespace std;

#define AC_ADDRESS "10.0.0.8"
#define AC_PORT 9996

namespace nDash {
    class ACPlugin : public GameServer::GamePlugin {
        public: ACPLUGIN_API virtual const string &pluginInfo() const {
            static string name("Assetto Corsa UDP Interface");
            return name;
        }

        public: ACPLUGIN_API virtual ~ACPlugin() {
            closeConnection();
        }

        public: ACPLUGIN_API virtual void closeConnection() {
            handshake.dismiss();
            if (sendto(sockfd, (char *) &handshake, sizeof(handshake), 0, (struct sockaddr *)&ServerAddr, sizeof(struct sockaddr_in)) > 0)
                cout << "Sent dismiss operation" << endl;

#if defined(NDASH_WIN32)
            closesocket(sockfd);
            WSACleanup();
#elif defined(NDASH_LINUX)
            close(sockfd);
#endif      
        }
        public: ACPLUGIN_API virtual const std::string &getName() const {
            static string sName("ACPlugin");
            return sName;
        }

        public: ACPLUGIN_API virtual int initGame() {
#if defined(NDASH_WIN32)
            WSADATA WSA;
#endif

#if defined(NDASH_WIN32)
            if (WSAStartup(0x0202,&WSA)) return false;
            if (WSA.wVersion != 0x0202) return false;
#endif

            if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == (int)INVALID_SOCKET)
                return -1;

            ServerAddr.sin_family = AF_INET;
            ServerAddr.sin_port = htons(AC_PORT);
            ServerAddr.sin_addr.s_addr = inet_addr(AC_ADDRESS);
            cout << "ACPlugin: Socket Initialized" << endl;

            handshake.set_handshake();
            if (sendto(sockfd, (char *) &handshake, sizeof(handshake), 0, (struct sockaddr *)&ServerAddr, sizeof(struct sockaddr_in)) <= 0)
                return -1;
            cout << "ACPlugin: Sent Handshake" << endl;

            if ((hs = recv(sockfd, (char *) &hs_response, sizeof(hs_response), 0)) <= 0)
                return -1;

            cout << "ACPlugin: Received Handshake" << endl;

            handshake.set_update();
            if (sendto(sockfd, (char *) &handshake, sizeof(handshake), 0, (struct sockaddr *) &ServerAddr, sizeof(struct sockaddr_in)) <= 0)
                return -1;

            cout << "ACPlugin: Sent update operation" << endl << "ACPlugin: Initialized" << endl;
            return 0;
        }

        public: ACPLUGIN_API virtual int updateGame(void) {
            if ((ci = recv(sockfd, (char *) &car_info, sizeof(car_info), 0)) <= 0)
                return -1;

            return 0;
        }

        struct handshaker {
            int identifier;
            int version;
            int operationId;

            void set_handshake() {
                identifier = 1;
                version = 1;
                operationId = 0;
            };

            void dismiss() {
                identifier = 1;
                version = 1;
                operationId = 3;
            };

            void set_update() {
                identifier = 1;
                version = 1;
                operationId = 1;
            };

            void set_spot() {
                identifier = 1;
                version = 1;
                operationId = 2;
            };
        };

        struct handshake_response {
            char carName[100];
            char driverName[100];
            int identifier;
            int version;
            char trackName[100];
            char trackConfig[100];

            void get_driver(void) {
                cout << "Driver: ";
                string driver = "";
                for (int i = 0; driverName[i+1] != '%'; i++) {
                    if ((i & 1) != 0) continue;
                    driver = driver + driverName[i];
                }
                cout << driver << endl;
            }

            void get_car(void) {
                cout << endl << "Car: ";
                string car = "";
                for (int i = 0; carName[i+1] != '%'; i++) {
                    if ((i & 1) != 0) continue;
                    car = car + carName[i];
                }
                cout << car << endl;
            }
        };

        struct rtcar_info {
            char identifier;
            int size;

            float speed_Kmh;
            float speed_Mph;
            float speed_Ms;

            bool isAbsEnabled;
            bool isAbsInAction;
            bool isTcInAction;
            bool isTcEnabled;
            bool isInPit;
            bool isEngineLimiterOn;

            float accG_vertical;
            float accG_horizontal;
            float accG_frontal;

            int lapTime;
            int lastLap;
            int bestLap;
            int lapCount;

            float gas;
            float brake;
            float clutch;
            float engineRPM;
            float steer;
            int gear;
            float cgHeight;

            float wheelAngularSpeed[4];
            float slipAngle[4];
            float slipAngle_ContactPatch[4];
            float slipRatio[4];
            float tyreSlip[4];
            float ndSlip[4];
            float load[4];
            float Dy[4];
            float Mz[4];
            float tyreDirtyLevel[4];

            float camberRAD[4];
            float tyreRadius[4];
            float tyreLoadedRadius[4];

            float suspensionHeight[4];

            float carPositionNormalized;

            float carSlope;

            float carCoordinates[3];
        };

        private: int sockfd;
        private: int ci;
        private: int hs;
        private: struct sockaddr_in ServerAddr;
        private: struct handshaker handshake;
        private: struct handshake_response hs_response;
        private: struct rtcar_info car_info;
    };

    extern "C" ACPLUGIN_API int getEngineVersion() {
        return 1;
    }

    extern "C" ACPLUGIN_API void registerPlugin(Kernel &kernel) {
        kernel.getGameServer().addGamePlugin(unique_ptr<GameServer::GamePlugin>(new ACPlugin()));
    }
} // nDash
