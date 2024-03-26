#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  struct Node *p, *child, *sibling;
  int key;
  int id;
  int degree;
} node;

node *printer[1000001] = {};
int sz[1000001] = {};

node *merge(node *h1, node *h2) {
  node *h = NULL, *last = NULL, *nxt = NULL;
  while(h1 || h2) {
    if(!h1) {
      nxt = h2;
      h2 = h2 -> sibling;
    }
    else if(!h2) {
      nxt = h1;
      h1 = h1 -> sibling;
    }
    else if(h1 -> degree > h2 -> degree) {
      nxt = h2;
      h2 = h2 -> sibling;
    }
    else {
      nxt = h1;
      h1 = h1 -> sibling;
    }
    if(!h) {
      h = nxt;
      last = nxt;
    }
    else {
      last -> sibling = nxt;
      last = nxt;
    }
  }
  if(last) last -> sibling = NULL;
  return h;
}

node *link(node *y, node *z) {
  y -> sibling = z -> child;
  z -> degree ++;
  y -> p = z;
  z -> child = y;
  return z;
}

node *Union(node *h1, node *h2) {
  node *h = merge(h1, h2);
  if(!h) {
    return h;
  }
  node *prev = NULL;
  node *x = h;
  node *next = x -> sibling;
  while(next) {
    if(x -> degree != next -> degree || (next -> sibling && next -> sibling -> degree == x -> degree)) {
      prev = x;
      x = next;
    }
    else {
      if(x -> key > next -> key) {
        x -> sibling = next -> sibling;
        link(next, x);
      }
      else {
        if(!prev) {
          h = next;
        }
        else {
          prev -> sibling = next;
        }
        link(x, next);
        x = next;
      }
    }
    next = x -> sibling;
  }
  return h;
}

node *insert(node *h, int pri, int id) {
  node *tmp = (node*) malloc(sizeof(node));
  tmp -> degree = 0;
  tmp -> key = pri;
  tmp -> id = id;
  tmp -> sibling = NULL;
  tmp -> child = NULL;
  tmp -> p = NULL;
  h = Union(h, tmp);
  return h;
}

node *pop(node *h) {
  node *mx_ptr = h, *cur = h, *pre = NULL, *prev_cur = NULL;
  if(!mx_ptr) {
    printf("no documents in queue\n");
    return h;
  }
  while(cur != NULL) {
    if(mx_ptr -> key < cur -> key) {
      mx_ptr = cur;
      pre = prev_cur;
    }
    prev_cur = cur;
    cur = cur -> sibling;
  }
  if(!pre) {
    h = h -> sibling;
  }
  else {
    pre -> sibling = mx_ptr -> sibling;
  }
  node *h1 = mx_ptr -> child;
  printf("%d printed\n", mx_ptr -> id);
  cur = h1;
  pre = NULL;
  while(cur != NULL) {
    node *nxt = cur -> sibling;
    cur -> sibling = pre;
    cur -> p = NULL;
    h1 = cur;
    pre = cur;
    cur = nxt;
  }
  h = Union(h, h1);
  return h;
}

int main (int argc, char** argv) {

  int n, m;
  scanf("%d%d", &n, &m);
  for(int i = 0; i < m; i++) {
    int op;
    scanf("%d", &op);
    if(op == 1) {
      int job_id, priority, printer_id;
      scanf("%d%d%d", &job_id, &priority, &printer_id);
      printer[printer_id] = insert(printer[printer_id], priority, job_id);
      sz[printer_id]++;
      printf("%d jobs waiting on printer %d\n", sz[printer_id], printer_id);
    }
    else if(op == 2) {
      int printer_id;
      scanf("%d", &printer_id);
      printer[printer_id] = pop(printer[printer_id]);
      if(sz[printer_id] > 0) {
        sz[printer_id]--;
      }
    }
    else {
      int printer_id1, printer_id2;
      scanf("%d%d", &printer_id1, &printer_id2);
      printer[printer_id2] = Union(printer[printer_id1], printer[printer_id2]);
      printer[printer_id1] = NULL;
      sz[printer_id2] += sz[printer_id1];
      sz[printer_id1] = 0;
      printf("%d jobs waiting on printer %d after moving\n", sz[printer_id2], printer_id2);
    }
  }
  return 0;
}
