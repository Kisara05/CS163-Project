TARGET := Dictionary
TEST_TARGET := TestDictionary

SRC := src
TEST := test
BUILD := build
BUILD_TEST := build_test

SRCS := $(shell find $(SRC) -type f -name '*.cpp')
OBJS := $(subst $(SRC)/,$(BUILD)/,$(addsuffix .o,$(basename $(SRCS))))

TEST_SRCS := $(shell find $(TEST) -type f -name '*.cpp')
TEST_OBJS := $(subst $(TEST)/,$(BUILD_TEST)/,$(addsuffix .o,$(basename $(TEST_SRCS))))


OS := $(shell uname -s)
COMPILE_FLAGS := -std=c++14 -Iinclude -c
TEST_FLAGS := -lgtest -lgtest_main -pthread


all: $(TARGET)

$(TARGET): $(OBJS)
ifeq ($(OS),Windows_NT)
	mkdir -p $(dir $@)
	g++ $(OBJS) -o $@ -Llib -lraylib -lopengl32 -lgdi32 -lwinmm -lcomdlg32 -lole32
else
	mkdir -p $(dir $@)
	g++ $(OBJS) -o $@ -lGL -lGLU -lglut -Llib -lraylib
endif

$(TEST_TARGET): $(TEST_OBJS)
	g++ $(TEST_OBJS) -o $@ $(TEST_FLAGS)

$(BUILD)/%.o: $(SRC)/%.cpp
	mkdir -p $(dir $@)
	g++ $(COMPILE_FLAGS) -o $@ $<

$(BUILD)/%.o: $(TEST)/%.cpp
	mkdir -p $(dir $@)
	g++ $(COMPILE_FLAGS) -o $@ $<

.PHONY: clean test

clean:
	rm -rf $(BUILD)
	rm -rf $(BUILD_TEST)
	rm -f $(TARGET)
	rm -f $(TEST_TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)
