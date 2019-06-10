刷题代码与笔记
---

## 1. Longest Increasing Subsequence

输入为nums[0:LEN-1]

- 1.1 dp[i]表示以nums[i]结尾的增子序列的长度

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

- 1.2 从前往后遍历记录其他的信息

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


## 2. IsContinuous 扑克牌中的顺子
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


## 3. minNumberInRotateArray 旋转数组的最小数字
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

- 3.1 二维数组的查找
```c++
class Solution {
public:
    bool Find(int target, vector<vector<int> > array) {
        // search from the right-top
        int Right = array[0].size()-1;
        int Top = 0;
            
        int col = Right, row = Top;
        while(Right>=0 && Top<array.size())
        {
            col = Right; row = Top;
            if (target == array[row][col]) break;
            // if smaller than the smallest element along the certain column
            //    then, delete the column
            if (target < array[Top][Right]){Right--; continue;}
            // if bigger than the boggest element along the certain row
            //    then, delete the row
            if (target > array[Top][Right]){Top++; continue;}
            
        }
        
        if (Right>=0 && Top<array.size()) return true;
        else return false;
    }
};
```

## 4. 整型数组中a[i], a[j]最大乘积、最大差值
相关系列O(N)

## 5. lowestCommonAncestor 树中两个节点的最低公共祖先
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

## 6. 矩阵中的路劲 back track
感觉就是一种深搜 dfs
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

## 7. 机器人的运动范围 dfs
```c++
class Solution {
public:
    int movingCount(int threshold, int rows, int cols)
    {
        if (threshold<0 || rows<=0 || cols<=0) return 0;
        this->R = rows;
        this->C = cols;
        this->CNT = 0;
        this->T = threshold;
        
        int** next = new int*[4];
        next[0] = new int[2]{-1, 0};
        next[1] = new int[2]{1, 0};
        next[2] = new int[2]{0, -1};
        next[3] = new int[2]{0, 1};
        
        bool **Marked = new bool*[R];
        for (int i=0; i<R; i++) Marked[i] = new bool[C];
        
        backtrack (0, 0, Marked, next);
        
        return CNT;
    }
private:
    int R, C, CNT, T;
    
    void backtrack (int r, int c, bool** marked, int** next) {
        
        if (r<0 || r>=R || c<0 || c>=C || marked[r][c] || !addup(r, c)) return;
        
        marked[r][c] = true;
        CNT++;
        
        for (int i=0; i<4; i++) {
            int *n = next[i];
            backtrack(r+n[0], c+n[1], marked, next);
        }
        return;
    }
    
    bool addup(int x, int y) {
        int sum=0;
        while (x>0) {
            sum += x%10;
            x /= 10;
        }
        while (y>0) {
            sum += y%10;
            y /= 10;
        }        
        return (sum <= T);
    }
};
```
- 7.1 回溯法 打印１到n位数字
```c++
void printNumber(vector<char> &number) {
    int index=0;
    while (index < number.size() && number[index] == '0') {index++;}
    while (index < number.size()) {cout << number[index++];}
    cout << "\n";
}

void backtrackPrint(vector<char> &number, int digit) {
    // the final state
    if (digit == number.size()) {
        printNumber(number);
        return;
    }

    for (int i=0; i<10; i++) {
        number[digit] = (char)(i+'0');
        backtrackPrint(number, digit+1);
    }
}

void print1ToMaxOfNDigits(int n) {
    if (n<=0) return;

    vector<char > number(n, '0');
    backtrackPrint(number, 0);
}

int main () {

    print1ToMaxOfNDigits(2);
    return 0;
}
```
- 7.2 回溯法 字符串的排列
```c++
class Solution {
private:
    vector<string> ans;
public:
    vector<string> Permutation(string str) {
        int LEN = str.length();
        if (LEN < 1) return ans;
        
        sort(str.begin(), str.end());
        string path = "";
        backtracking(str, path);
        return ans;
    }
    void backtracking (string s, string path) {
        int LEN = s.length();
        if (LEN == 1) {
            path += s;
            ans.push_back(path);
        }
        else {
            set<char> used; // remember repeated char
            for (int i=0; i<LEN; i++) {
                if (used.find(s[i]) != used.end()) continue;
                used.insert(s[i]);
                path += s[i];
                string left = s.substr(0, i) + s.substr(i+1, LEN-i-1);
                backtracking(left, path);
                // step back for back track
                path = path.substr(0, path.length()-1);
            }
        }
    }
};
```


## 8. Integer Break (不等式+求导)
```c++
class Solution {
public:
    int integerBreak(int n) {
        if (n<2) return 0;
        if (n==2) return 1;
        if (n==3) return 2;
        
        // n>=4 (the point is to avoid 1)
        int times3=n/3, times2=0;
        if (n-3*times3 == 1) {
            times3--;
            times2 = 2;
        }
        if (n-3*times3 == 2) {
            times2 = 1;
        }
        
        return (int)pow(3, times3) * (int)pow(2, times2);
    }
};
```
另外可以采用O(N^2)的动态规划方法，可以考虑下。

## 9. 二进制中1的个数 位运算
```c++
class Solution {
public:
     int  NumberOf1(int n) {
         int cnt=0;
         if (n<0) {cnt++;}
         for (int i=0; i<31; i++) {
             if ((n>>i)%2!=0) {
                 cnt++;
             }
         }
         return cnt;
     }
};
```
或者采用 n&(n-1),作用是将 n 的二进制表示中最后一个1置为0.
```c++
class Solution {
public:
     int  NumberOf1(int n) {
         int cnt=0;
         while (n) {
             cnt++;
             // delete the last 1
             n &= n-1;
         }
         return cnt;
     }
};
```
类似于leetcode 191求hammingWeight(uint32_t n)．

## 10. 数值的整数次方
O(N)的方法：
```c++
class Solution {
public:
    double Power(double base, int exponent) {
        if (exponent==0) {return 1;}
        
        int E = (exponent>0)?(exponent):(-exponent);
        double ans=1;
        for (int i=E; i>0; i--) {
            ans *= base;
        }
        
        return (exponent>=0)?(ans):(1/ans);
    }
};
```
O(logN)的方法：{x_{n} = (n%2==0)?((x*x)^(n/2)) : ((x*x)^(n/2))*x }
```c++
class Solution {
public:
    double Power(double base, int exponent) {
        if (exponent == 0) return 1;
        if (exponent == 1) return base;
        
        bool isNegtive = false;
        if (exponent < 0) {
            exponent = -exponent;
            isNegtive = true;
        }
        
        double power = Power(base*base, exponent/2);
        if (exponent%2 == 1) power *= base;
        
        return isNegtive?(1/power):power;
    }
};
```

## 11. 栈问题

- 11.1 包含 min函数的栈
用另一个栈记录每一步 push(), pop(), min(), 用额外的空间取得 O(1)的时间复杂度。
```c++
class Solution {
private: 
    stack<int> minstk, stk;
public:
    void push(int value) {
        stk.push(value);
        // if is empty, the min operation will cause segment error
        minstk.empty() ? minstk.push(value) : minstk.push(std::min(value, minstk.top()));
    }
    void pop() {
        minstk.pop();
        stk.pop();
    }
    int top() {
        return stk.top();
    }
    int min() {
        return minstk.top();
    }
};
```

- 11.2 栈的压入、弹出序列
```c++
class Solution {
public:
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        stack<int> S;
        
        int LEN = pushV.size();
        int A=0, B=0;
        
        while (B<LEN) {
            if (!S.empty() && popV[B]==S.top()) {B++;S.pop();}
            else {
                if (A<LEN) {S.push(pushV[A]); A++;}
                else {return false;}
            }
        }
        
        return true;
    }
};
```

## 12. 最小的k个数 (快速选择算法)

- 基于快排的 _Partition_ 修改原数组
```c++
class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        int LEN=input.size();
        if (LEN<=0 || k>LEN || k<=0) {
            vector<int> ans;
            return ans;
        }
        
        int start=0, end=LEN-1;
        int index = Partition(input, start, end);
        while (index != k-1) {
            if (index >k-1) {
                end = index-1;
                index = Partition(input, start, end);
            }
            else {
                start = index+1;
                index = Partition(input, start, end);
            }
        }
        vector<int> ans(input.begin(), input.begin()+k);
        return ans;
    }
    
    // 填坑法
    int Partition (vector<int> &array, int start, int end) {
        int pivot=array[start];
        int i=start, j=end;
        while (i < j) {
            while (array[j]>=pivot && j>i) {j--;}
            if (i < j) {array[i++] = array[j];}
            
            while (array[i]<=pivot && i<j) {i++;}
            if (i < j) {array[j--] = array[i];}
            
        }
        array[i] = pivot;
        return i;
    }
    
};
```
## 13. 堆的相关问题
- 数据流的中位数
```c++
class Solution {
private:
    priority_queue<int, vector<int>, less<int>> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
public:
    void Insert(int num)
    {
        int size1=maxHeap.size(), size2=minHeap.size();
        if (size1 == size2) {
            if (size2==0 || minHeap.top()>num) {
                maxHeap.push(num);
            }
            else {
                minHeap.push(num);
                maxHeap.push(minHeap.top());
                minHeap.pop();
            }
        }
        // size1 = size2 + 1
        else {
            if (num>maxHeap.top()) {
                minHeap.push(num);
            }
            else {
                maxHeap.push(num);
                minHeap.push(maxHeap.top());
                maxHeap.pop();
            }
        }
    }
    double GetMedian()
    { 
        int len = maxHeap.size() + minHeap.size();
        if ((len&1) == 0) {
            return ((double)maxHeap.top() + (double)minHeap.top()) / 2;
        }
        else {
            return (double)maxHeap.top();
        }
    }
};
```
实际上 priority_queue 底层也是通过封装 push_heap 和 pop_heap 实现的。下面关注一些原理。

采用`vector + push_heap + pop_heap + less + greater` 实现最大(小)堆。`less` 对应的最大堆，即 vector 插入元素后用 push_heap + less 进行调整，且堆顶元素为 vector[0]；在删除元素时，先用 pop_heap + less 将堆顶元素调整到 vector[-1]，再执行 vector 的 pop_back 操作。
```c++
class Solution {
private:
    vector<int> maxHeap;
    vector<int> minHeap;
    
public:
    void Insert(int num)
    {
        int size1=maxHeap.size(), size2=minHeap.size();
        if (size1 == size2) {
            if (size2==0 || minHeap[0]>num) {
                maxHeap.push_back(num);
                push_heap(maxHeap.begin(), maxHeap.end(), less<int>());
            }
            else {
                minHeap.push_back(num);
                push_heap(minHeap.begin(), minHeap.end(), greater<int>());
                
                maxHeap.push_back(minHeap[0]);
                push_heap(maxHeap.begin(), maxHeap.end(), less<int>());
                
                pop_heap(minHeap.begin(), minHeap.end(), greater<int>());
                minHeap.pop_back();
            }
        }
        // size1 = size2 + 1
        else {
            if (num>maxHeap[0]) {
                minHeap.push_back(num);
                push_heap(minHeap.begin(), minHeap.end(), greater<int>());
            }
            else {
                maxHeap.push_back(num);
                push_heap(maxHeap.begin(), maxHeap.end(), less<int>());
                
                minHeap.push_back(maxHeap[0]);
                push_heap(minHeap.begin(), minHeap.end(), greater<int>());
                
                pop_heap(maxHeap.begin(), maxHeap.end(), less<int>());
                maxHeap.pop_back();
            }
        }
    }
    double GetMedian()
    { 
        int len = maxHeap.size() + minHeap.size();
        if ((len&1) == 0) {
            return ((double)maxHeap[0] + (double)minHeap[0]) / 2;
        }
        else {
            return (double)maxHeap[0];
        }
    }
};
```

## 14. 最大值队列
- 最大值滑动窗口计算

(leetcode: 239. Sliding Window Maximum; nowcoder: maxInWindows)
```c++
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> ans;
        int len = nums.size();
        if (len<1 || len<k) return ans;
        
        deque<int> index;
        
        // initialize
        for (unsigned int i=0; i<k; i++) {
            while (!index.empty() && nums[i]>=nums[index.back()]) {
                index.pop_back();
            }
            index.push_back(i);
        }
        
        for (unsigned int i=k; i<len; i++) {
            ans.push_back(nums[index.front()]);
            while (!index.empty() && nums[i]>=nums[index.back()]) {
                index.pop_back();
            }
            if (!index.empty() && index.front()<=(int)(i-k)) {
                index.pop_front();
            }
            index.push_back(i);
        }
        ans.push_back(nums[index.front()]);
        return ans;
    }
};
```
采用双端队列记录元素的下标，方便判断队头元素是否被移除当前的滑动窗口。


- 实现最大值队列


