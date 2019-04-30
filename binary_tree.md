

```c++
/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
```

#### 0. 二叉树的遍历

##### 0.1 层次遍历

```c++
class Solution {
public:
    vector<int> PrintFromTopToBottom(TreeNode* root) {
        // hierachical traversal using queue
        vector<int> ans;
        if (!root) {return ans;}
        
        queue<TreeNode*> Q;
        Q.push(root);
        while (!Q.empty()) {
            TreeNode *tmp = Q.front();
            Q.pop();
            ans.push_back(tmp->val);
            if (tmp->left) {Q.push(tmp->left);}
            if (tmp->right) {Q.push(tmp->right);}
        }
        
        return ans;
    }
};
```
还可以按每层打印出来：
```c++
class Solution {
public:
        vector<vector<int> > Print(TreeNode* pRoot) {
            vector<vector<int> > ans;
            if (pRoot == nullptr) return ans;
            
            bool reverse = false;
            queue<TreeNode *> Q;
            Q.push(pRoot);
            
            while (!Q.empty()) {
                int cnt = Q.size();
                vector<int> layer;
                while (cnt > 0) {
                    TreeNode *curr = Q.front();
                    layer.push_back(curr->val);
                    if (curr->left) {Q.push(curr->left);}
                    if (curr->right) {Q.push(curr->right);}
                    Q.pop();
                    cnt--;
                }
                if (reverse) {
                    std::reverse(layer.begin(), layer.end());
                }
                //reverse = !reverse;
                ans.push_back(layer);
                
            }   
            return ans;
        }
};
```

##### 0.2 前序遍历
非递归
```c++
class Solution {
public:
    vector<int> preorderTraversal (TreeNode *pRoot) {
        vector<int> ans;
        stack<TreeNode *> stk;
        TreeNode *curr = pRoot;
        while (!stk.empty() || curr) {
            if (curr) {
                ans.push_back(curr->val);
                stk.push(curr);
                curr = curr->left;
            }
            else {
                curr = stk.top()->right;
                stk.pop();
            }
        }
        return ans;
    }    
}
```

#### 0.3 中序遍历
非递归
```c++
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        stack<TreeNode *> stk;
        TreeNode *curr = root;
        while (!stk.empty() || curr) {
            if (curr) {
                stk.push(curr);
                curr = curr->left;
            }
            else {
                ans.push_back(stk.top()->val);
                curr = stk.top()->right;
                stk.pop();
            }
        }
        return ans;
    }
};
```

#### 0.4 后续遍历
非递归
```c++
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;
        stack<TreeNode *> stk;
        TreeNode *curr=root;
        TreeNode *last=root;
        while (!stk.empty() || curr) {
            if (curr) {
                stk.push(curr);
                curr = curr->left;
            }
            else if (!stk.top()->right || stk.top()->right==last) {
                ans.push_back(stk.top()->val);
                last = stk.top();
                stk.pop();
                curr = NULL;
            }
            else {
                curr = stk.top()->right;
            }
        }
        return ans;
    }
};
```

#### 1. 二叉树中和为某一值的路劲

```c++
class Solution {
public:
    vector<vector<int> > FindPath(TreeNode* root,int expectNumber) {
        if (!root) {return ans;}
        this->target = expectNumber;
        vector<int> tmp;
        dfs(root, tmp, 0);
        
        return ans;
    }
private:
    int target;
    vector<vector<int> > ans;
    
    void dfs (TreeNode* t, vector<int> &vec, int sum) {
        
        vec.push_back(t->val);
        sum += t->val;
        if (!t->left && !t->right && sum==target) {ans.push_back(vec);}
        
        if (t->left) {dfs(t->left, vec, sum);}
        
        if (t->right) {dfs(t->right, vec, sum);}
        
        // clear the vec
        sum -= t->val;
        vec.pop_back();
    }
};
```

#### 2. 二叉树中两节点的最低公共祖先

```c++
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        
        int minSize=0x7FFFFFFF;
        bool pVisit=false, qVisit=false;
        TreeNode *ancestor = nullptr;
        
        // based on PostOrder
        stack<TreeNode *> stk;
        TreeNode *curr = root, *last=root;
        TreeNode *visit=nullptr;
        while ((!stk.empty() || curr) && (!pVisit || !qVisit)) {
            if (curr) {
                stk.push(curr);
                curr = curr->left;
            }
            else if (!stk.top()->right || stk.top()->right==last) {
                visit = stk.top();
                stk.pop();
                last = visit;
                curr = nullptr;
                if (visit == p) {pVisit = true;}
                if (visit == q) {qVisit = true;}
            }
            else {
                curr = stk.top()->right;
            }
            // the point
            if (pVisit+qVisit == 1) {
                if (stk.size() < minSize) {
                    minSize=stk.size(); 
                    ancestor=stk.top();
                } 
            }
            
        }
        
        return ancestor;
    }
};
```



####