# ==============================================================
# vedis cmake v.0.0.3
#
# Created by Taka Wang (taka@cmwang.net) on 2014/04/14
#
# gcc -W -Wall -O2 cli.c vedis.c -o cli
#
# ==============================================================

cmake_minimum_required(VERSION 2.8)

PROJECT(vedis_intro C)
SET(CMAKE_C_FLAGS "-Wall -g -O2")

SET(vedis_lib vedis.c)
ADD_LIBRARY(vedis SHARED ${vedis_lib})
INSTALL(TARGETS vedis LIBRARY DESTINATION /usr/lib/)

# NON-VOLATILE CLI
SET(NV-CLI vedis_intro)
ADD_EXECUTABLE(${NV-CLI} vedis_intro.c)
TARGET_LINK_LIBRARIES(${NV-CLI} vedis)
INSTALL(TARGETS ${NV-CLI} RUNTIME DESTINATION /usr/bin/)

# VOLATILE CLI
SET(V-CLI vedis_shell)
ADD_EXECUTABLE(${V-CLI} vedis_shell.c)
TARGET_LINK_LIBRARIES(${V-CLI} vedis)
SET_TARGET_PROPERTIES(${V-CLI} PROPERTIES COMPILE_DEFINITIONS "VOLATILE")
INSTALL(TARGETS ${V-CLI} RUNTIME  DESTINATION /usr/bin/)
