cmake_minimum_required(VERSION 2.8)

PROJECT(vedis_test C)
SET(CMAKE_C_FLAGS "-Wall -g -O2")

SET(vedis_lib vedis.c)
ADD_LIBRARY(vedis SHARED ${vedis_lib})
INSTALL(TARGETS vedis LIBRARY DESTINATION /usr/lib/)

SET(INTRO vedis_intro)
ADD_EXECUTABLE(${INTRO} vedis_intro.c)
TARGET_LINK_LIBRARIES(${INTRO} vedis)
INSTALL(TARGETS ${INTRO} RUNTIME DESTINATION /usr/bin/)

SET(SHELL vedis_shell)
ADD_EXECUTABLE(${SHELL} vedis_shell.c)
TARGET_LINK_LIBRARIES(${SHELL} vedis)
INSTALL(TARGETS ${SHELL} RUNTIME  DESTINATION /usr/bin/)
