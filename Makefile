.PHONY: all clean

SOURCES=util.c \
		deque.c \
		merge_sort.c \
		quick_sort.c \
		insertion_sort.c \
		bin-tree.c \
		hash.c \
		stack.c \
		queue.c \
		darray.c \
		graph.c \
		heap.c \
		avl-tree.c \
		rb-tree.c \
    longest-palindromic-substring.c \
    heap_inplace.c

APPS=test_deque \
	 test_sort \
	 test_bin_tree \
	 test_hash \
	 test_darray \
	 test_graph \
	 test_queue \
	 test_heap \
	 test_avl_tree \
	 task-merge-k-sorted-lists \
	 task-find-min-depth \
	 task-max-path-sum-bin-tree \
	 task-check-array-preorder \
	 task-check-btree-is-full \
	 task-bottom-view-btree \
	 task-top-view-btree \
	 task-rm-nodes-pathlen \
	 task-lca-bst \
	 task-btree-sub \
	 task-reverse-alt-levels \
	 task-graph-simple-bfs \
	 task-graph-simple-dfs \
	 task-graph-cycle \
	 task-graph-union-find \
	 task-graph-mst-kruskal \
	 task-graph-dijkstra \
	 task-graph-a-star \
   problem-longest-palindromic-substring \
   test_heap_inplace

CC=gcc
CFLAGS=-Wall -Werror -std=c99 -D_XOPEN_SOURCE_EXTENDED -D_XOPEN_SOURCE=500 \
	   -Wno-pointer-to-int-cast \
	   -Wno-int-to-pointer-cast
LDFLAGS=-lm
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
	$(CC) $(CFLAGS)  -o $@ $^ $(LDFLAGS)
