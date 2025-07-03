CC=gcc
CCFLAGS=-Wall -Wextra -Wpedantic -Werror
SOURCEDIR=source
BUILDDIR=build
INCLUDEDIR=include
TESTDIR=test

# all .c files should be compiled into .o files
SOURCEFILES = $(shell find $(SOURCEDIR) -name *.c)
OBJFILES = $(patsubst %.c, $(BUILDDIR)/%.o, $(notdir $(SOURCEFILES)))
EXE=life

$(EXE): $(BUILDDIR)/$(EXE)
$(BUILDDIR)/$(EXE): $(OBJFILES)
	$(CC) $(CCFLAGS) -o $@ $^

$(OBJFILES): $(BUILDDIR)/%.o: $(SOURCEDIR)/%.c
	$(CC) $(CCFLAGS) -I $(INCLUDEDIR) -c $< -o $@

run: $(EXE)
	./$(BUILDDIR)/$(EXE)

FORCE:

clean:
	-rm $(BUILDDIR)/*.o
	-rm $(BUILDDIR)/$(EXE)
