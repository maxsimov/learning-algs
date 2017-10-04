.PHONY: all clean

SOURCES=deque.c \
		merge_sort.c \
		quick_sort.c \
		insertion_sort.c \
		bin-tree.c \
		hash.c
APPS=test_deque \
	 test_sort \
	 test_bin_tree \
	 test_hash \
	 task-find-min-depth \
	 task-max-path-sum-bin-tree

CC=gcc
CFLAGS=-Wall -std=c99 -D_XOPEN_SOURCE_EXTENDED -D_XOPEN_SOURCE=500
LDFLAGS=
OBJDIR=obj
OBJECTS=$(patsubst %.c, $(OBJDIR)/%.o, $(SOURCES))
EXECUTABLES=$(patsubst %, $(OBJDIR)/%, $(APPS))

.PRECIOUS: $(OBJDIR)/%.o

$(shell mkdir -p $(OBJDIR))

all: $(EXECUTABLES)

clean:
	rm -fr $(OBJDIR)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%: $(OBJDIR)/%.o $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
