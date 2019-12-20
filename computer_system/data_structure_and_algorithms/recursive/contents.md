## 一、递归
递归通常用在可以把一个问题分解成子问题求解，最终由子问题的解可以合成问题的解。  
举个例子来理解递归，假如问题的解是[a0, a1, a2, ..., an]，那么用递归求解就是：
* 求解[a0]和[a1, a2, ..., an]；  
* 求解[a1]和[a2, a3, ..., an];  
* ...  
* 直到求解出[an]，最后由[a0], [a1], ..., [an]得到最终解。  

递归方法优缺点明显。  
优点：  
* 逻辑清晰，代码简洁。

缺点：  
* 递归层次较深时，函数调用多，性能较差。  
* 递归过程中会重复求解相同的子问题，性能较差。    
* 递归实质上是利用了系统栈的空间，如果层次较深，容易产生栈溢出。  

当然，对于重复子问题，可以通过申请一定的空间保存已经计算出来的子问题，从而提高性能。  

## 二、递归应用
递归在线性数据结构、树、图都有应用，涵盖较广。  
递归应用中通常伴随回溯，当然有时候是不需要回溯的。  
递归思想上可以用三板斧来思考：  
* 递归结束的条件。  
* 子问题求解。  
* 子问题求解完毕，是否需要回溯。       
在实际求解中，可以转换成如下三步：  
* 递归结束的条件。  
* options，广度上从哪里更进一步？递归函数参数总需要有一个index，来表示走到哪一步？  
* 是否需要回溯。  

### 线性数据结构中的递归应用
#### *[\[leetcode-46\]](https://leetcode-cn.com/problems/permutations/) 全排队*  
*给定一个没有重复数字的序列，返回其所有可能的全排列。  
输入: [1,2,3]  
输出: [[1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], [3,2,1]]*   

首先分析题目，全排列数组，就是每次确定一个数，直到最后一个。  
<img src="permutations.png" width=500 align=center />  
按上述递归/回溯的思路：
* 递归结束的条件：最后一个数找到   
* options，确定这个数有哪些选择？那就是剩下的数里面选一个，然后继续下一个数的选择   
* 回溯，把上次选的数放回去，重新来选   

```
void permute(int *nums, int nums_size, int index, int **return_array, int *return_size)
{                                                                                  
    int i = 0;                                                                     
                                                                                   
    /* index indicates which step we arrived, ended position: final element */                                            
    if (index == nums_size) {                                                      
        return_array[*return_size] = calloc(1, sizeof(int) * nums_size);           
        memcpy(return_array[*return_size], nums, sizeof(int) * nums_size);         
        *return_size = *return_size + 1;                                           
        return;                                                                    
    }                                                                              
                                                                                   
    /* options: in permutations, what options does current "index" can be ? */  
    for (i = index; i < nums_size; i++) {                                          
        swap(nums, index, i);                                                      
        permute(nums, nums_size, index + 1, return_array, return_size);       
        /* backtrace */                                                            
        swap(nums, index, i);                                                      
    }                                                                              
    return;                                                                        
}
```

### 树中的递归应用

### 图中的递归应用

## 三、总结
