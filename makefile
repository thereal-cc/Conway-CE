# ----------------------------
# Makefile Options
# ----------------------------

NAME = CONWAY
ICON = icon.png
DESCRIPTION = "Conway's Game Of Life for TI 84+ CE"
COMPRESSED = YES
ARCHIVED = YES

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
