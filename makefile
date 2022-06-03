
# Makefile Options
# ----------------------------

NAME = SLOPEFLD
DESCRIPTION = "CE program to graph slope fields"
COMPRESSED = NO
ARCHIVED = NO
CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)