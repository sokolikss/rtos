# Target specific macros
TARGET = Turning_with_Compass_-_NXTosek
TARGET_SOURCES := \
	Turning_with_Compass_-_NXTosek.c
TOPPERS_OSEK_OIL_SOURCE := ./Turning_with_Compass_-_NXTosek.oil

O_PATH ?= build

include ../../ecrobot/ecrobot.mak
