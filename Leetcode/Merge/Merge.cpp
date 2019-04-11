//
// Created by weanl on 4/11/19.
//


#include "../../DataStructure/ListNode.h"



/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/
class SolutionMerge {
public:
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    {
        ListNode tmp(0);
        ListNode *tail = &tmp;

        while (pHead1 || pHead2) {
            //if ((pHead1 && pHead1->val <= pHead2->val) || !pHead2) {
            if (!pHead2 || (pHead1 && pHead1->val <= pHead2->val)) {
                tail->next = pHead1;
                pHead1 = pHead1->next;
            }
            else {
                tail->next = pHead2;
                pHead2 = pHead2->next;
            }
            tail = tail->next;
        }
        return tmp.next;
    }
};


int main () {


    return 0;
}

