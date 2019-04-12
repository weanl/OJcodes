//
// Created by weanl on 4/12/19.
//

#ifndef OJCODES_TREENODE_H
#define OJCODES_TREENODE_H


struct TreeNode {
    int val;
    struct TreeNode *left, *right;

    TreeNode(int x) : (val(x), left(NULL), right(NULL)) {}
};


#endif //OJCODES_TREENODE_H
