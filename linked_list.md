
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
            *cur = entry->next;
            free(entry);
        }
        else {
            cur = &entry->next;
        }
    }
}
```




