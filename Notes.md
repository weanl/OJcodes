

#### 1. Longest Increasing Subsequence

输入为nums[0:LEN-1]

###### 1.1 dp[i]表示以nums[i]结尾的增子序列的长度

```c++
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int LEN=nums.size();
        if (LEN==0) return 0;
        if (LEN==1) return 1;
        
        vector<int> dp(LEN, 1);
        int i=1, ans=1;
        while (i<LEN) {
            for (int j=0; j<i; j++) {
                if (nums[j]<nums[i]) {
                    dp[i] = max(dp[j]+1, dp[i]);
                }
                else {continue;}
            }
            ans = max(ans, dp[i]);
            i++;
        }
        
        return ans;
    }
};
```

###### 1.2 从前往后遍历记录其他的信息
vecor<int> dp;//空初始化

dp[0]:dp[i]表示当前遍历步下最长增子序列长度为i+1,且对应的最小的结束元素为dp[i]=nums[somewhere].
```c++
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp;
        int i=0, LEN=nums.size();
        while (i<LEN) {
            auto it = std::lower_bound(dp.begin(), dp.end(), nums[i]);
            if (it == dp.end()) {dp.push_back(nums[i]);}
            else {*it = nums[i];}
            i++;
        }
        
        return dp.size();
    }
};
```
这个题目可以抽象为 Dynamic Program + Binary Search


#### 2. IsContinuous 扑克牌中的顺子
```c++
class Solution {
public:
    bool IsContinuous( vector<int> numbers ) {
        int LEN=numbers.size();
        if (LEN<5) return false;
        
        int zeros=0;
        sort(numbers.begin(), numbers.end());
        
        for (int i=1; i<numbers.size(); i++) {
            int dist = dist=numbers[i]-numbers[i-1];
            if (numbers[i-1] == 0) {zeros++;}
            else if (dist==0) {return false;}
            else if (dist > 1) {
                if (zeros-dist+1>=0) {zeros = zeros-dist+1;}
                else return false;
            }
        }
        
        return true;
    }
};
```
(待续)一个拓展的问题：如何利用哈希表，将限定取值范围的排序任务的时间复杂度降到O(N).


#### 3. minNumberInRotateArray 旋转数组的最小数字
```c++
class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        int LEN = rotateArray.size();
        if (LEN < 1) {return 0;}
        // binary search
        
        int left=0, right=LEN-1;
        while (left<right) {
            int mid = left + (right-left)/2;
            if (rotateArray[mid] < rotateArray[right]) {right = mid;}
            else {left = mid + 1;}
        }
        
        // here, right=left
        return rotateArray[left];
    }
};
```
需要注意的是:

while(left<right)定义的查找区间为[left, right)，所以上述left和right的更新：left=mid+1, right=mid.新的查找区间是[left, right)。

#### 4. 整型数组中a[i], a[j]最大乘积、最大差值
相关系列O(N)

#### 5. lowestCommonAncestor 树中两个节点的最低公共祖先
```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // no assume that p->val <= q->val
        if (root==NULL) return root;
        
        if (root->val < p->val && root->val < q->val) {
            return lowestCommonAncestor(root->right, p, q);
        }
        else if (root->val > p->val && root->val > q->val) {
            return lowestCommonAncestor(root->left, p, q);
        }
        
        return root;
    }
};
```

#### 6. 矩阵中的路劲 back track
```c++
class Solution {
public:
    bool hasPath(char* matrix, int rows, int cols, char* str)
    {
        string pattern(str);
        this->R = rows;
        this->C = cols;
        this->L = pattern.length();
        if (R==0 || C==0) return false;
        this->Pattern = str;
        
        int** next = new int*[4];
        next[0] = new int[2]{-1, 0};
        next[1] = new int[2]{1, 0};
        next[2] = new int[2]{0, -1};
        next[3] = new int[2]{0, 1};
        
        // cannot new char[R][C] ??
        char **Matrix = new char*[R];
        for (int i=0; i<R; i++) Matrix[i] = new char[C];
        bool **Marked = new bool*[R];
        for (int i=0; i<R; i++) Marked[i] = new bool[C];
        
        for (int i=0, idx=0; i<R; i++) {
            for (int j=0; j<C; j++) Matrix[i][j] = matrix[idx++];
        }
        
        for (int i=0, idx; i<R; i++) {
            for (int j=0; j<C; j++) {
                if (backtrack(i, j, 0, Matrix, Marked, next)) {
                    return true;
                }
            }
        }        
        
        return false;
    }
private:
    int R, C, L;
    char *Pattern;
    
    bool backtrack(int r, int c, int pos, char** matrix, bool** marked, int** next) {
        
        // the final state is true
        if (pos==L) return true;
        // the final state is false
        if (r<0 || r>=R || c<0 || c>=C || matrix[r][c]!=Pattern[pos] || marked[r][c]) {
            return false;
        }
        
        // go on
        marked[r][c] = true;
        for (int i=0; i<4; i++) {
            int *n = next[i];
            if (backtrack(r+n[0], c+n[1], pos+1, matrix, marked, next)) {
                return true;
            }
        }
        
        // back track
        marked[r][c] = false;
        return false;
    }
    

};
```




