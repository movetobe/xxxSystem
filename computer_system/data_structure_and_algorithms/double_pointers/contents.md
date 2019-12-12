## 双指针
双指针是指使用两个指针对线性数据结构进行遍历/搜索的方法。
双指针方法包括：  
* 首尾指针
* 快慢指针
* 前后指针

## 双指针方法解析

### 首尾指针
首指针从线性表从前往后遍历，尾指针从线性表尾部往前遍历。

#### *[剑指offer-57] <small>和为s的数字</small>*
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



### 快慢指针

### 前后指针
