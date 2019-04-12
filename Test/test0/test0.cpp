
#include <iostream>
#include <cstring>
#include <stack>

using namespace std;

class Solution {
public:
    string decodeString(string s) {
        int LEN = s.length();

        string left="[", right="]";
        stack<string > stk;
        
        for (int i=0; i<LEN;) {
            //
            int start=i;
            while (i<LEN && s.substr(i, 1)<="9" && s.substr(i, 1)>="0") {
                i++;
            }
            //
            string cur;
            if (start == i) {cur = s.substr(start, i-start+1), i++;}
            else {cur = s.substr(start, i-start);}
            //cout << cur << endl;

            if (cur != right) {stk.push(cur);}
            else {
                string tmp = stk.top();
                string codes = "";
                while (tmp!=left) {
                    codes = tmp + codes;
                    stk.pop();
                    tmp = stk.top();        
                }
                stk.pop();
                int digit = stoi(stk.top());
                string decodes = "";
                for (int j=0; j<digit; j++) {decodes += codes;}
                stk.pop();
                stk.push(decodes); 
            }
        }

        //
        string ans = "";
        while (stk.empty() == false) {
            ans = stk.top() + ans;
            stk.pop();
        }

        return ans;
    }
};



int main () {

    string a="2[abc]3[cd]ef";

    Solution sol;
    string d = sol.decodeString(a);

    cout << a << endl;
    cout << d << endl;

    return 0;
}


