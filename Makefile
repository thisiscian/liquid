SRCS=$(wildcard src/*.cpp)
GIFS=$(patsubst src/%.cpp,%.gif,$(SRCS))
OBJS=$(patsubst src/%.cpp,.o/%.o,$(SRCS))
BINS=$(patsubst src/%.cpp,bin/%,$(SRCS))
CPPFLAGS=-lgif -lm -Iinclude -Llib -Wunknown-pragmas

all: init $(GIFS)

init:
	@mkdir -p gifs bin .o

%.gif: bin/%
	$< -o $@

bin/%: .o/%.o lib/libliquid.a
	$(CXX) $(CPPFLAGS) -lliquid $< -o $@

lib/libliquid.a: .o/liquid.o
	ar rcs lib/libliquid.a .o/liquid.o

.o/liquid.o: lib/src/liquid.cpp
	$(CXX) $(CPPFLAGS) -Ilib/src -c -o $@ $^

.o/%.o: src/%.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $^

.SECONDARY: $(OBJS) $(BINS)

clean:
	rm -rf bin gifs lib/libliquid.a .o
