#DIRECTORIES
BUILDDIR=build
TESTDIR=test
GTESTDIR=googletest/googletest
GMOCKDIR=googletest/googlemock
SRCDIR=src
PROJNAME=main

#RULES
all: $(BUILDDIR)/test $(BUILDDIR)/$(PROJNAME)

build_test: $(BUILDDIR)/test

build: $(BUILDDIR)/$(PROJNAME)

run_test: build_test
	./$(BUILDDIR)/test --gmock_verbose=info

run: build
	./$(BUILDDIR)/$(PROJNAME)

clean:
	rm -f $(BUILDDIR)/*

#GOOGLE TEST LIB
$(BUILDDIR)/gtest-all.o:
	g++ -std=c++11 -pthread -I$(GTESTDIR) -I$(GTESTDIR)/include -c $(GTESTDIR)/src/gtest-all.cc -o $@

#GOOGLE MOCK LIB
$(BUILDDIR)/gmock-all.o:
	g++ -std=c++11 -pthread -I$(GTESTDIR)/include -I$(GMOCKDIR) -I$(GMOCKDIR)/include -c $(GMOCKDIR)/src/gmock-all.cc -o $@

$(BUILDDIR)/libgmock.a: $(BUILDDIR)/gtest-all.o $(BUILDDIR)/gmock-all.o
	ar -rv $@ $^

#TEST FILES
TEST_CPPS = $(wildcard $(TESTDIR)/*.cpp) 
TEST_OBJS = $(patsubst $(TESTDIR)/%.cpp,$(BUILDDIR)/%.o,$(TEST_CPPS))

#PROJECT FILES
PROJECT_CPPS = $(wildcard $(SRCDIR)/*.cpp) 
PROJECT_OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(PROJECT_CPPS))

#ALL FILES
CPPS = $(TEST_CPPS) $(PROJECT_CPPS)
OBJS = $(TEST_OBJS) $(PROJECT_OBJS)
NON_MAIN_OBJS = $(patsubst $(BUILDDIR)/$(PROJNAME).o, ,$(OBJS))

#COMPILE ALL CPP FILES
$(BUILDDIR)/%.o: $(TESTDIR)/%.cpp
	g++ -g -std=c++11 -I$(GTESTDIR)/include -I$(GMOCKDIR)/include -I. -c $< -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	g++ -g -std=c++11 -I$(GTESTDIR)/include -I$(GMOCKDIR)/include -I. -c $< -o $@

#TEST BINARY
$(BUILDDIR)/test: $(NON_MAIN_OBJS) $(BUILDDIR)/libgmock.a
	g++ -std=c++11 -pthread -I$(GTESTDIR)/include -I$(GMOCKDIR)/include ${GTESTDIR}/src/gtest_main.cc $^ -o $@

#PROJECT BINARY
$(BUILDDIR)/$(PROJNAME): $(PROJECT_OBJS)
	g++ -std=c++11 -g $^ -o $@