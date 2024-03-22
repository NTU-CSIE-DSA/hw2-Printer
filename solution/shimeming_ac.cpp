#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define MAXN 1000006
#define MAXM 1000006

typedef struct Job {
  int pri, id;
} Job;

typedef struct Node {
  Job job;
  struct Node *fchild;
  struct Node *prev, *nxt;
  unsigned int n_child;
} Node;

typedef struct Bheap {
  int size;
  Node *bt[20];
} Bheap;

Bheap printer[MAXN]; // printer[0]: tmp_printer for job adding

Node *add_subtree(Node *r1, Node *r2) {
  // merge r2 to r1
  if (r1->fchild) r1->fchild->prev = r2;
  r2->nxt = r1->fchild;
  r1->fchild = r2;
  r1->n_child++;
  // printf("pri: %d\n", r1->job.pri);
  return r1;
}

Node *btree_merge(Node *r1, Node *r2) {
  assert(r1->n_child == r2->n_child);
  // printf("%d, %d\n", r1->job.pri, r2->job.pri);
  if (r1->job.pri >= r2->job.pri) return add_subtree(r1, r2);
  else return add_subtree(r2, r1);
}

void heap_merge(int h1, int h2) {
  // merge h2 to h1
  Bheap tmp;
  tmp.size = printer[h1].size + printer[h2].size;
  for (int i = 0; i < 20; i++) tmp.bt[i] = NULL;
  for (int ord = 0; ord < 20; ord++) {
    if (tmp.bt[ord] == NULL) tmp.bt[ord] = printer[h1].bt[ord];
    else if (printer[h1].bt[ord] != NULL) {
      tmp.bt[ord+1] = btree_merge(tmp.bt[ord], printer[h1].bt[ord]);
      tmp.bt[ord] = NULL;
    }
    if (tmp.bt[ord] == NULL) tmp.bt[ord] = printer[h2].bt[ord];
    else if (printer[h2].bt[ord]) {
      tmp.bt[ord+1] = btree_merge(tmp.bt[ord], printer[h2].bt[ord]);
      tmp.bt[ord] = NULL;
    }
  }
  printer[h1] = tmp;
  printer[h2].size = 0;
  for (int i = 0; i < 20; i++) printer[h2].bt[i] = NULL;
}

int heap_pop(int h) {
  if (printer[h].size == 0) return -1;
  int max_pri = -1;
  int max_ord = -1;
  for (int ord = 0; ord < 20; ord++) {
    if (printer[h].bt[ord] == NULL) continue;
    int p = printer[h].bt[ord]->job.pri;
    if (p > max_pri) {
      max_pri = p;
      max_ord = ord;
    }
  }
  int max_id = printer[h].bt[max_ord]->job.id;
  // printf("%d, %d\n", max_pri, max_ord);
  printer[0].size = -1;
  for (int i = 0; i < 20; i++) printer[0].bt[i] = NULL;
  Node *tmpn = printer[h].bt[max_ord]->fchild;
  while (tmpn) {
    printer[0].bt[tmpn->n_child] = tmpn;
    // printf("%d\n", tmpn->n_child);
    tmpn = tmpn->nxt;
  }
  printer[h].bt[max_ord] = NULL;
  heap_merge(h, 0);
  return max_id;
}

void heap_insert(int h, Job job) {
  printer[0].size = 1;
  printer[0].bt[0] = (Node*) calloc(1, sizeof(Node));
  printer[0].bt[0]->job = job;
  heap_merge(h, 0);
}

int main() {
  int N, M;
  scanf("%d%d", &N, &M);
  while (M--) {
    int op;
    scanf("%d", &op);
    if (op == 1) {
      int job_id, priority, printer_id;
      scanf("%d%d%d", &job_id, &priority, &printer_id);
      Job new_job;
      new_job.id = job_id;
      new_job.pri = priority;
      heap_insert(printer_id, new_job);
      printf("%d jobs waiting on printer %d\n", printer[printer_id].size, printer_id);
    }
    if (op == 2) {
      int printer_id;
      scanf("%d", &printer_id);
      int job_id = heap_pop(printer_id);
      if (job_id == -1) printf("no documents in queue\n");
      else printf("%d printed\n", job_id);
    }
    if (op == 3) {
      int printer_id1, printer_id2;
      scanf("%d%d", &printer_id1, &printer_id2);
      heap_merge(printer_id2, printer_id1);
      printf("%d jobs waiting on printer %d after moving\n", printer[printer_id2].size, printer_id2);
    }
  }
  return 0;
}
