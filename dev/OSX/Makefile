CXX = g++
CXXFLAGS = -Wall -MMD -g -I../../inc -I/usr/X11/include
LDFLAGS = -I../../inc -lX11 -L/usr/X11/lib -I/usr/X11/include
EXEC = pp9k

SRCDIR = ../../src
INCDIR = ../../inc
OBJDIR = ../../obj
BINDIR = ../../bin

SOURCES  := $(wildcard $(SRCDIR)/*.cc)
INCLUDES := $(wildcard $(SRCDIR)/*.h)   
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cc=$(OBJDIR)/%.o)
rm = rm -f

$(BINDIR)/$(EXEC): $(OBJECTS)
	$(CXX) -o $@ $(LDFLAGS) $(OBJECTS)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cc
	@$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONEY: clean
clean:
	$(rm) $(OBJECTS)

.PHONEY: remove
remove: clean
	$(rm) $(BINDIR)