CC=g++
CPPFLAGS=-g -DNDEBUG $(OPTGLAGS)
LIBS=-ldl $(OPTLIBS)

SOURCES=$(wildcard src/**/*.cpp src/*.cpp)
OBJECTS=$(patsubst %.cpp,%o,$(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.cpp)
TESTS=$(patsubst %.cpp,%,$(TEST_SRC))

TARGET=build/qvslib.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

#The Target Build

all: $(TARGET) $(SO_TARGET) tests

dev: CPPFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@
$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CPP) -shared -o $@ $(OBJECTS)

build:

	@md build
	@md bin

#The Unit Tests

.PHONY: tests
tests: CPPFLAGS += $(TARGET)
tests: $(TESTS)
	./tests/runtests.bat

clean:
	rd /s /q build $(OBJECTS) $(TESTS)
#rm -f tests/tests.log
#find . 
