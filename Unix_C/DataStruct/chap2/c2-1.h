#ifndef C2_1_H
#define C2_1_H

#define LIST_INIT_SIZE 10 //
#define LIST_INCREMENT 2 //
typedef int ElemType;

struct SqList {
	ElemType *elem;
	int length;
	int listsize;
};

#endif //C2-1_h

