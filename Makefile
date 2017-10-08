.PHONY: all clean

SOURCES=deque.c \
		merge_sort.c \
		quick_sort.c \
		insertion_sort.c \
		bin-tree.c \
		hash.c \
		stack.c \
		darray.c \
		graph.c

APPS=test_deque \
	 test_sort \
	 test_bin_tree \
	 test_hash \
	 test_darray \
	 task-find-min-depth \
	 task-max-path-sum-bin-tree \
	 task-check-array-preorder \
	 task-check-btree-is-full \
	 task-bottom-view-btree \
	 task-top-view-btree \
	 task-rm-nodes-pathlen \
	 task-lca-bst \
	 task-btree-sub \
	 task-reverse-alt-levels

CC=gcc
CFLAGS=-Wall -std=c99 -D_XOPEN_SOURCE_EXTENDED -D_XOPEN_SOURCE=500 -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast
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
