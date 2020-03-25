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
    heap_inplace.c \
    guess-word-master.cpp \
    guess-word-solution.cpp \
    guess-word-rand.cpp \
    guess-word-minmax.cpp \
    guess-word-freq.cpp

C_APPS=test_deque \
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

CXX_APPS= \
   test-guess-word

FMT=thirdparty/fmt-6.1.2

CXX=g++
CXXFLAGS=-Wall -Werror -I$(FMT)/include

CC=gcc
CFLAGS=-Wall -Werror -std=c99 -D_XOPEN_SOURCE_EXTENDED -D_XOPEN_SOURCE=500 \
	   -Wno-pointer-to-int-cast \
	   -Wno-int-to-pointer-cast
LDFLAGS=-L$(FMT) -lm -lfmt
OBJDIR=obj

C_OBJECTS=$(patsubst %.c, $(OBJDIR)/%.o, $(filter %.c,$(SOURCES)))
CXX_OBJECTS=$(patsubst %.cpp, $(OBJDIR)/%.o, $(filter %.cpp,$(SOURCES)))

C_EXECUTABLES=$(patsubst %, $(OBJDIR)/%, $(C_APPS))
CXX_EXECUTABLES=$(patsubst %, $(OBJDIR)/%, $(CXX_APPS))

.PRECIOUS: $(OBJDIR)/%.o 

$(shell mkdir -p $(OBJDIR))

all: $(C_EXECUTABLES) $(CXX_EXECUTABLES)

clean:
	rm -fr $(OBJDIR)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/%: $(OBJDIR)/%.o $(C_OBJECTS) $(CXX_OBJECTS) $(FMT)/libfmt.a
	$(CXX)  -o $@ $^ $(LDFLAGS)

$(FMT)/libfmt.a:
	(cd $(FMT) && cmake . && make fmt)