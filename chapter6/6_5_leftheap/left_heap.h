#ifndef _LEFT_HEAP_H_
#define _LEFT_HEAP_H_

struct TreeNode;
typedef struct TreeNode * PriorityQueue;

PriorityQueue Initialize(void);
int FindMin(PriorityQueue H);
int IsEmpaty(PriorityQueue H);
PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2);

#define Insert(X, H) (H = Insert1((X), H))

PriorityQueue Insert1(int X, PriorityQueue H);
PriorityQueue DeleteMin1(PriorityQueue H);

#endif