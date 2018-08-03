#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := Occupancy_sensor
EXTRA_COMPONENT_DIRS = $(PROJECT_PATH)/C $(PROJECT_PATH)/configuration
COMPONENT_DIRS = $(EXTRA_COMPONENT_DIRS) $(PROJECT_PATH)/components $(IDF_PATH)/components $(PROJECT_PATH)/main
include $(IDF_PATH)/make/project.mk
