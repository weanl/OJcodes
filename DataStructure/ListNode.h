//
// Created by weanl on 4/11/19.
//

#ifndef OJCODES_LISTNODE_H
#define OJCODES_LISTNODE_H


struct ListNode {
    int val;
    struct ListNode *next;

    ListNode(int x) : (val(x), next(NULL)) {}
};


#endif //OJCODES_LISTNODE_H
