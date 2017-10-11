#pragma once

void heapify_min(int *data, int len);
int heap_pop_min(int *data, int *len); // extract min element
void sift_up_min(int *data, int len); // move a node up in the tree, as long as needed
void sift_down_min(int *data, int len); // move a node down in the tree, similar to sift-up; 


void heapify_max(int *data, int len);
int heap_pop_max(int *data, int *len); // extract max element
void sift_up_max(int *data, int len); // move a node up in the tree, as long as needed
void sift_down_max(int *data, int len); // move a node down in the tree, similar to sift-up; 
