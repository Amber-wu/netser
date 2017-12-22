.PHONY: all
all: preBuild server

CC=g++
MKDIR=mkdir
CPPFLAG=-c -g -Wall -Wextra

TARGET_NAME=netser

PROJECT_ROOT = $(PWD)
INCLUDE_PATH=-I${PROJECT_ROOT}/include
LIB_PATH=-L${PROJECT_ROOT}/lib

_OBJS := 
_OBJS += server.o
_OBJS += listener.o
_OBJS += utils.o
_OBJS += service_base.o

OBJDIR = $(PROJECT_ROOT)/obj
SRCDIR = $(PROJECT_ROOT)/src
OBJS = $(patsubst %, $(OBJDIR)/%, $(_OBJS))

preBuild:
	$(MKDIR) -p $(OBJDIR)

# generate the final target
server: $(OBJS)
	$(CC) -o $(TARGET_NAME) $(INCLUDE_PATH) $(LIB_PATH) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -o $@ $(CPPFLAG) $< $(INCLUDE_PATH)

.PHONY: clean
clean:
	find $(PROJECT_ROOT) -name *.o | xargs rm
	rm $(TARGET_NAME)
	rmdir $(OBJDIR)
