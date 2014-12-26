# GNU/Linux Makefile

# Compiler
CC = gcc
CXX = g++

# Some stuff
RM = rm -f
MV = mv
EXE = nDash
MAKE = make

# Install directories
BIN_DIR = ../bin/
LIB_DIR = $(BIN_DIR)libs/
PLUGIN_DIR = $(BIN_DIR)plugins/

# Application configuration
NDASH_CFLAGS = -Wall -ggdb -fPIC
NDASH_LFLAGS = -ldl -Wl,-rpath,./libs -L$(LIB_DIR) -lkernel
NDASH_ODIR = nDash/obj/
NDASH_SRC := $(wildcard nDash/*.cpp)
NDASH_OBJS := $(patsubst nDash/%.cpp,$(NDASH_ODIR)%.o,$(NDASH_SRC))

# Kernel configuration
KERNEL_CFLAGS = -Wall -ggdb -fPIC
KERNEL_LFLAGS = -shared
KERNEL_ODIR = kernel/obj/
KERNEL_SRC := $(wildcard kernel/*.cpp)
KERNEL_OBJS := $(patsubst kernel/%.cpp,$(KERNEL_ODIR)%.o,$(KERNEL_SRC))

###############################################################################
# Plugins
###############################################################################

# Plugin configuration
PLUGIN_CFLAGS = -Wall -ggdb -fPIC
PLUGIN_LFLAGS = -shared -L$(LIB_DIR) -lkernel

# SDL2 + OpenGL
SDL2_ODIR = sdl2/obj/
SDL2_OBJS = $(SDL2_ODIR)SDL2Render.o
SDL2_SRC = sdl2/SDL2Render.cpp

# Assetto Corsa
AC_ODIR = acplugin/obj/
AC_OBJS = $(AC_ODIR)ACPlugin.o
AC_SRC = acplugin/ACPlugin.cpp

# Build the stuff
all: kernel nDash plugins
plugins: sdl2 acplugin

kernel: $(KERNEL_OBJS)
	$(RM) $(LIB_DIR)libkernel.so
	$(CXX) $(KERNEL_CFLAGS) -o $(LIB_DIR)libkernel.so $(KERNEL_OBJS) $(KERNEL_LFLAGS)

$(KERNEL_ODIR)%.o: kernel/%.cpp
	$(CXX) $(KERNEL_CFLAGS) -c -o $@ $<

nDash: $(NDASH_OBJS)
	$(RM) $(BIN_DIR)$(EXE)
	$(CXX) $(NDASH_CFLAGS) -o $(BIN_DIR)$(EXE) $(NDASH_OBJS) $(NDASH_LFLAGS)

$(NDASH_ODIR)%.o: nDash/%.cpp
	$(CXX) $(NDASH_CFLAGS) -c -o $@ $<

sdl2: $(SDL2_OBJS)
	$(RM) $(PLUGIN_DIR)libSDL2.so
	$(CXX) $(PLUGIN_CFLAGS) -o $(PLUGIN_DIR)libSDL2.so $(SDL2_OBJS) $(PLUGIN_LFLAGS)

$(SDL2_ODIR)%.o: sdl2/%.cpp
	$(CXX) $(PLUGIN_CFLAGS) -c -o $@ $<

acplugin: $(AC_OBJS)
	$(RM) $(PLUGIN_DIR)libACPlugin.so
	$(CXX) $(PLUGIN_CFLAGS) -o $(PLUGIN_DIR)libACPlugin.so $(AC_OBJS) $(PLUGIN_LFLAGS)

$(AC_ODIR)%.o: acplugin/%.cpp
	$(CXX) $(PLUGIN_CFLAGS) -c -o $@ $<

mingw:
	@$(MAKE) -f Makefile.mingw

mingw-clean:
	@$(MAKE) -f Makefile.mingw clean

clean:
	$(RM) $(BIN_DIR)$(EXE) $(LIB_DIR)* $(PLUGIN_DIR)* $(NDASH_OBJS) $(KERNEL_OBJS) $(SDL2_OBJS) $(AC_OBJS)
