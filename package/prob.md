## Problem Description

In this problem, we ask you to design a system to emulate the job queues of several printers. This system needs to support the following three operations: 

- Add Operation: Insert a job into the printer's queue.
- Print Operation: Print the document with the highest priority from the queue. This is a typical need for the priority queue (i.e. what the binary heap is designed for).
- Move Operation: Transfer all jobs from one printer to another. This happens when one printer "fails'' for some reason, such as running out of paper or toner.

### Inputs

Assuming that the printers' queues are initially empty, the input begins with two space-separated integers $N$ and $M$, representing the number of printers and the total number of operations, respectively. Printers are 1-indexed. Each of the next $M$ lines is given in one of the following formats:

- **1 `job_id` `priority` `printer_id`**: add operation
Insert a job with `job_id` into the queue of printer `printer_id`, assigning it the priority `priority`.

- **2 `printer_id`**: print operation
Instruct printer `printer_id` to print the document with the highest priority from its queue, removing the job from the queue in the process.

- **3 `printer_id1` `printer_id2`**: move operation
Transfer all jobs from printer `printer_id1` to printer `printer_id2`, maintaining their respective priorities. The two printers will have different IDs.

### Outputs

For each **add** operation, a line is printed indicating the number of jobs waiting on printer `printer_id` in the format: `{num_of_jobs} jobs waiting on printer {printer_id}`.

For each **print** operation, if there is a job to be printed, a line is output displaying `{job_id} printed`. Otherwise, if the queue is empty, the output will be `no documents in queue`.

For each **move** operation, a line is printed indicating the number of jobs waiting on printer `printer_id2` after the move, in the format: `{num_of_jobs} jobs waiting on printer {printer_id2} after moving`.

### Constraints

- $1\le N,M\le 10^6$
- $1\le\text{printer\_id, printer\_id1, printer\_id2}\le N$
- $1\le\text{job\_id, priority}\le 10^9$

It is guaranteed that all priority values and job IDs will be distinct, and all operations will be legal (i.e., all IDs will be within the specified range).

## Subtask 

### Subtask 1 (15 pts)

- $N=1$
- There are no move operation, which means that the task can be solved with the basic heap taught in class. 

### Subtask 2 (15 pts)

- $1\le N,M\le 5000$

(不需要用mergable heap也可以過)

### Subtask 3 (70 pts)

- no other constraints

## Sample Test Cases

### Sample Input 1

```
1 5
1 1 1 1
1 2 2 1
2 1
2 1
2 1
```

### Sample Output 1

```
1 jobs waiting on printer 1
2 jobs waiting on printer 1
2 printed
1 printed
no documents in queue
```

### Sample Input 2

```
2 15
1 1 5 1
1 2 4 1
1 3 3 1
1 4 2 2
1 5 1 2
3 1 2
2 1
2 2
2 2
3 2 1
2 2
2 1
2 1
2 1
2 1
```

### Sample Output 2

```
1 jobs waiting on printer 1
2 jobs waiting on printer 1
3 jobs waiting on printer 1
1 jobs waiting on printer 2
2 jobs waiting on printer 2
5 jobs waiting on printer 2 after moving
no documents in queue
1 printed
2 printed
3 jobs waiting on printer 1 after moving
no documents in queue
3 printed
4 printed
5 printed
no documents in queue
```
