# Copyright 2016 <https://github.com/spelcaster>
# Created by: Hugo Augusto Freitas do Carmo
#
# Last modified at     | Modified by     | Description

includedir=/usr/local/include/cpuinfo
binfile=/usr/local/bin/cpuinfo

# compiler flags
CFLAGS = -Wall -Wextra -pedantic

ifdef RELEASE
CFLAGS += -O2
else
CFLAGS += -g
endif

CXXFLAGS = $(CFLAGS) -std=c++11

# define any directories containing header files other than /usr/include
INCLUDES  =

# define library paths in addition to /usr/lib
LFLAGS =

# define any libraries to link
LIBS = -ljsoncpp

TEST_LIBS += -lgmock -lgtest -lpthread

# define the program source files
SOURCES = $(wildcard src/*.cpp)

MAIN_FILES = src/main.cpp
TEST_SOURCES  = $(filter-out $(MAIN_FILES),$(SOURCES))
TEST_SOURCES += $(wildcard tests/*.cpp)

# define the program object files
OBJECTS = $(addprefix obj/, $(notdir $(SOURCES:.cpp=.o)))

TEST_OBJECTS = $(addprefix obj/, $(notdir $(TEST_SOURCES:.cpp=.o)))

# define the executable
EXECUTABLE = build/cpuinfo
TEST_EXECUTABLE = build/test_cpuinfo

.PHONY: install uninstall clean clean-test

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LFLAGS) -o $@ $(OBJECTS) $(LIBS)

test: $(TEST_SOURCES) $(TEST_EXECUTABLE)

$(TEST_EXECUTABLE): $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LFLAGS) -o $@ $(TEST_OBJECTS) $(TEST_LIBS)

install: uninstall
	mkdir $(includedir)
	cp -rfv $(EXECUTABLE) $(binfile)
	cp -rfv res $(includedir)
	cp -rfv include $(includedir)

uninstall:
	$(RM) -rfv $(includedir) $(binfile)

# this is a suffix replacement rule for buildings .o's from .cpp's
# it uses automatic variables:
# $< - the name of the prerequisite of the rule (a .cpp file)
# $@ - the name of the target of the rule (a .o file)
# (see the GNU make manual section about automatic variables)
obj/%.o:src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/%.o:tests/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(RESOURCES) $(OBJECTS) $(EXECUTABLE)

clean-test:
	$(RM) $(RESOURCES) $(TEST_OBJECTS) $(TEST_EXECUTABLE)

