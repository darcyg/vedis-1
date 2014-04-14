# ==============================================================
# vedis cmake v.0.0.1
#
# Created by Chia-Ming Wang (taka@bandrich.com) on 2014/04/14
# Copyright 2014 Bandrich Inc. All rights reserved.
#
# gcc -W -Wall -O2 cli.c vedis.c -o cli
#
# ==============================================================

cmake_minimum_required(VERSION 2.8)

project(redis C)

set(CMAKE_C_FLAGS "-Wall -g -O2")

add_executable(cli cli.c vedis.c)