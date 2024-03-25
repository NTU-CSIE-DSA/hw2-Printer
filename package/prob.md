## Problem Description

Please refer to the PDF on NTU COOL.

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
