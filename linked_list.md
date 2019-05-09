
#### 0. 两种链表删除的方法
删除链表中指定的一个（或多个）元素

###### 0.1 采用记录前一个节点的双指针方法
```c++
typedef struct node {
    struct node *next;
    ...
}node;

typedef bool (* remove_fn)(node const *V);
// Remove all nodes from the supplied list for which the 
// supplied remove function returns true.
// Returns the new head of the list.
```
常规操作
```c++
node *remove_if (node *head, remove_fn rm) {
    node *prev=NULL, *curr=head;
    while (curr != NULL) {
        node *next = curr->next;
        if (rm(curr)) {
            // is head
            if (prev == NULL) {
                head = head->next;
            }
            // remove the certain node
            else {
                prev->next = next;
                free(curr);
                curr = next;
            }
        }
        // pass
        else {
            prev = curr;
            curr = next;
        }
    }
}
```

###### 0.2 二级指针直接修改一级指针的值 (Linus Torvald)

```c++
void remove_if (node **head, remove_fn rm) {
    node **curr=head;
    while (*curr != NULL) {
        node *entry=*curr;
        // 
        if (rm(entry)) {
            *curr = entry->next;
            free(entry);
        }
        else {
            curr = &entry->next;
        }
    }
}
```
curr存的是节点next指针的地址（刚开始存的是指向头结点的指针的地址）．因为删除操作的本质是修改对应指针的值，所以可以通过curr找到对应的next指针，然后修改该指针的值．（指针的值便是指针所指向的内存空间的地址）

#### 1 删除链表的重复节点
归结为：(采用二级指针直接修改一级指针的值，实现对符合条件的节点进行删除操作)
<br>记录之前删除的值 currVal, 以及判断当前值是否和下面的值相等</br>
```c++
/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
*/
class Solution {
public:
    ListNode* deleteDuplication(ListNode* pHead)
    {
        ListNode **curr = &pHead;
        int currVal = -1; // choose a singular value
        
        while (*curr != NULL && (*curr)->next != NULL) {
            ListNode *entry = *curr;
            
            if (entry->val == entry->next->val) {
                //
                currVal = entry->val;
                *curr = entry->next;
                free(entry);
            }
            else if (entry->val == currVal) {
                *curr = entry->next;
                free(entry);
            }
            
            else curr = &entry->next;
        }
        // consier the last element
        if (*curr != NULL && (*curr)->val == currVal) {
            ListNode *entry = *curr;
            *curr = entry->next; // set as NULL equally
            free(entry);
        }
        
        return pHead;
    }
};
```


#### 2. 反转链表
```c++
/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/
class Solution {
public:
    ListNode* ReverseList(ListNode* pHead) {
        ListNode *curr=pHead, *prev=nullptr;
        
        while (curr) {
            ListNode *entry=curr->next;
            curr->next = prev;
            prev = curr;
            curr = entry;
        }
        
        return prev;
    }
};
```


#### 3. 复杂链表的复制
```c++
/*
struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};
*/
class Solution {
public:
    RandomListNode* Clone(RandomListNode* pHead)
    {
        if (!pHead) return nullptr;
        
        // first round: clone along the next
        RandomListNode *curr=pHead;
        while (curr) {
            RandomListNode *entry=curr->next;
            curr->next = new RandomListNode(curr->label);
            curr->next->next = entry;
            curr = entry;
        }
        
        // second round: set *random
        curr = pHead;
        while (curr) {
            RandomListNode *clone=curr->next;
            // the random may be nullptr
            clone->random = (curr->random)?curr->random->next:nullptr;
            curr = clone->next;
        }
        
        // third round: split the List
        curr = pHead;
        RandomListNode *newHead=curr->next;
        while (curr) {
            RandomListNode *clone=curr->next;
            curr->next = clone->next;
            curr = clone->next;
            clone->next = (curr!=nullptr)?curr->next:nullptr;
        }
        
        return newHead;
    }
};
```





####




