

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
一个拓展的问题：如何利用哈希表，将限定取值范围的排序任务的时间复杂度降到O(N).





