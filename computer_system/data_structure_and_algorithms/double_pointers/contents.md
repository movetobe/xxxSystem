## 双指针
双指针是指使用两个指针对线性数据结构进行遍历/搜索的方法。
双指针方法包括：  
* 首尾指针
* 快慢指针
* 前后指针

## 双指针方法解析

### 首尾指针
首指针从线性表从前往后遍历，尾指针从线性表尾部往前遍历。

#### *[剑指offer-57] 和为s的数字*
*输入一个递增排序的数组和一个数字s，在数组总查找两个数，使得他们的和正好是s。
如果有多对数字的和等于s，则输出任意一对即可。
如：输入数组[1, 2, 4, 7, 11, 15]和数字15，由于4 + 11 = 15，则输出[4, 11]即可*  

采用首尾指针的双指针方法，如图所示：  
<img src="front-tail.png" width="300" align=center/>  
* 若nums[front] + nums[tail] < s, 则说明nums[front]太小了，需要增大，故front++;  
* 若nums[front] + nums[tail] > s，则说明nums[tail]太大了，需要减小，故tail--;  
* 若nums[front] + nums[tail] == s，得到解；  
* 结束条件front >= tail，无解  

```
/* front-tail pointers to solve the problem. */                                    
int target_sum(int *nums, int nums_size, int target, int *ret_array)               
{                                                                                  
    int front = 0;                                                                 
    int tail = nums_size - 1;                                                      
                                                                                   
    if ((!nums) || (!ret_array) || (nums_size < 2)) {                              
        return -1;                                                                 
    }                                                                              
                                                                                   
    while (front < tail) {                                                         
        if ((nums[front] + nums[tail]) == target) {                                
            /* find the solution */                                                
            ret_array[0] = nums[front];                                            
            ret_array[1] = nums[tail];                                             
            break;                                                                 
        }                                                                          
        if ((nums[front] + nums[tail]) < target) {                                 
            /* increase left part */                                               
            front++;                                                               
        } else if((nums[front] + nums[tail]) > target) {                           
            /* decrease left part */                                               
            tail--;                                                                
        }                                                                          
    }                                                                              
                                                                                   
    return (front < tail) ? 0 : -1;                                                
} 
```
对于上述方法，由于最多遍历整个数组的所有元素，故时间复杂度是$$O(n)$$。  
如果数组是没有排序的，且可以改变数组，则可以先qsort()排序，然后再用首尾指针。  
同理，对于三数之和的题目[\[leetcode-15\]](https://leetcode-cn.com/problems/3sum/),
就可以排序，然后固定一个数，然后就是上述的两数之和了，这样的话，可以在$$O(n^2)$$
的时间复杂度内解决。  

### 前后指针
前指针先走k步，然后前后指针同步往后遍历。  

#### *[剑指offer-22] 链表中倒数第k个节点*
*输入一个链表，输出该链表中倒数第k个节点。如1->2->3->4->5->6，则倒数第3个节点
就是4所在的节点。*  

采用前后指针方法，如图所示：  
<img src="before-after.png" width="500" align=center/>
* 前指针先走k步
* 前后指针一起走，直到前指针走到NULL
* 此时后指针指向的节点就是链表的倒数第k个节点
* 注意：如果链表长度小于k，该如何处理  

```
/* before-after pointers to solve the problem */
struct list_node {                                                                 
    int value;                                                                     
    struct list_node *next;                                                        
};                                                                                 
                                                                                   
struct list_node *find_last_kth_node(struct list_node *head, int k)                
{                                                                                  
    int step = 0;                                                                  
    struct list_node *before = head;                                               
    struct list_node *after = head;                                                
                                                                                   
    /* before pointer move k step */                                               
    for (step = 0; step < k; step++) {                                             
        if (!before) {                                                             
            break;                                                                 
        }                                                                          
        before = before->next;                                                     
    }                                                                              
                                                                                   
    /* list length < k */                                                          
    if ((!before) && (step < k)) {                                                 
        return NULL;                                                               
    }                                                                              
                                                                                   
    /* traverse until before is NULL */                                            
    while (before) {                                                               
        before = before->next;                                                     
        after = after->next;                                                       
    }                                                                              
                                                                                   
    return after;                                                                  
}
```  
从前指针的角度看，前指针从链表头遍历一遍到链表尾，故时间复杂度为$$O(n)$$。  
类似的题目如删除链表倒数第N个节点[\[leetcode-19\]](https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/)，  
需要注意的是，删除节点需要另外考虑头节点/中间节点/尾节点删除之后，节点之间指针的变化。  

### 快慢指针
顾名思义，就是双指针中一个指针快一个指针慢，通常都是让快指针一次走2步，慢指针一次走1步。

#### *[剑指offer-23] 链表中环的入口节点*
*如果链表中包含环，如何找出环的入口节点？如图所示，环的入口点为4的节点*。
<img src="list-circle.png" width="400" align=center/>

此问题分为**如何判断是否有环？**和**有环的情况下，如何得到环的入口点。**两个字问题。  

**如何判断有环？**  
这里就要使用快慢指针。我们想象，两个同学以不同的速度，同时从教室跑到操场，
然后开始绕操场跑圈。  
如果操场是直线的操场，那么跑得快的永远都在前面，直到尽头。  
如果操场是圆圈的操场，那么跑的慢的同学和跑的快的同学总会相遇，而且肯定是在操场上相遇。  
回到题目中，我们就可以这样来判断链表中是否有环：  
* 快指针一次走2步，慢指针一次走1步，两个同时从头指针处开始走
* 如果快指针走到了NULL，那说明没有环
* 如果快指针与慢指针相遇了，说明存在环


