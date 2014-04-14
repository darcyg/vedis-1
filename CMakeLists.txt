# ==============================================================
# vedis cmake v.0.0.1
#
# Created by Taka Wang (taka@cmwang.net) on 2014/04/14
#
# gcc -W -Wall -O2 cli.c vedis.c -o cli
#
# ==============================================================

cmake_minimum_required(VERSION 2.8)

# cmake . -DOPENWRT=ON
option(OPENWRT "OPENWRT" OFF)
if (OPENWRT)
    add_definitions(-DOPENWRT)
endif()

project(redis C)
set(CMAKE_C_FLAGS "-Wall -g -O2")

# NON-VOLATILE CLI
set(NV-CLI vli)
add_executable(${NV-CLI} cli.c vedis.c)
INSTALL(TARGETS ${NV-CLI} RUNTIME DESTINATION /usr/bin/)

# VOLATILE CLI
set(V-CLI vvli)
add_executable(${V-CLI} cli.c vedis.c)
set_target_properties (${V-CLI} PROPERTIES COMPILE_DEFINITIONS "VOLATILE")
INSTALL(TARGETS ${V-CLI} RUNTIME DESTINATION /usr/bin/)
