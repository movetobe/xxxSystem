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
如上图所示，第一个数可以选择1/2/3中的一个，第二个可以选择剩下的两个中的一个，最后就是剩下的那一个。  
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
		/* current "index" number set to be i-th number */
        swap(nums, index, i);                                                      
        permute(nums, nums_size, index + 1, return_array, return_size);       
        /* backtrace */                                                            
        swap(nums, index, i);                                                      
    }                                                                              
    return;                                                                        
}
```   
线性数据结构中使用递归/回溯，如*\[剑指offer-38\]字符串的排列，即输入一个字符串，
输出字符串的所有排列*。只是将上述题目中的数字换成字符。   
还有的题目需要增加每一步是否合法的判断，如*[\[leetcode-47\]](https://leetcode-cn.com/problems/permutations-ii/)
数字全排列，需要考虑重复排列*，这个就可以对数组先排序，如果current "index"跟上一个"index"的值一样，
那么意味着重复，需要排除，即在递归前多一个判断这一步是否要走。
*[\[leetcode-22\]](https://leetcode-cn.com/problems/generate-parentheses/)括号生成*，
也是需要增加合法性的判断，即对左括号和右括号个数的判断。

### 树中的递归应用
树型结构是递归天然的战场。对于树型结构的问题，通常都转化为求解其子树的问题。
树型结构里最经典的就是二叉树，下面我们就以二叉树为例子说明递归/回溯在树型结构中的应用。  
树型结构递归/回溯常见思路：  

* 递归结束条件：到达叶子节点
* options: 左子树和右子树，对于二叉树就这两种选择
* 回溯，是否需要回溯到父节点

#### *[二叉树的前序/中序/后序遍历]*   
*前序遍历*  

```
void preorder(struct tree_node *root)
{
	if (!root) {
		return;
	}

	visit(root->data);
	preorder(root->left);
	preorder(root->right);
}
```  

*中序遍历*

```
void inorder(struct tree_node *root)
{
	if (!root) {
		return;
	}

	inorder(root->left);
	visit(root->data);
	inorder(root->right);
}
```  

*后序遍历*   

```
void postorder(struct tree_node *root)
{
	if (!root) {
		return;
	}

	postorder(root->left);
	postorder(root->right);
	visit(root->data);
}
```  

几乎所有的二叉树的题目都是遍历树，那么就是前序/中序/后序遍历的变形。  

### 图中的递归应用
在图的题目中，最常用的搜索方法就是深度优先搜索(DFS)和广度优先搜索(BFS)。其中，
DFS使用递归/回溯方法实现，使得逻辑清晰，代码简洁。  

#### *[\[leetcode-79\]](https://leetcode-cn.com/problems/word-search/) 单词搜索*
*给定一个二维网格和一个单词，找出该单词是否存在于网格中。方向可以上下左右搜素，
网格字符不能重复*   

仍然是按照前面的三步走：

* 结束条件：搜索的单词完成了。  
* options：判断当前字符满足条件，往上下左右走一步。  
* 回溯：上下左右均没有满足，该字符放弃。  

```
int compare_word(char **board, int row, int col, int x, int y,
					char *word, int index, int **visited)
{                                                                                  
    /* ended position: index is last one */                                        
    if (index == (strlen(word))) {                                                 
        return 1;                                                                  
    }                                                                              
                                                                                   
    /* options */                                                                  
    if ((x >= 0) && (x < row) && (y >= 0) && (y < col)                             
        && (!visited[x][y]) && (word[index] == board[x][y])) {                     
        visited[x][y] = 1;                                                         
        if (compare_word(board, row, col, x + 1, y, word, index + 1, visited)   
            || compare_word(board, row, col, x, y + 1, word, index + 1, visited)
            || compare_word(board, row, col, x - 1, y, word, index + 1, visited)
            || compare_word(board, row, col, x, y - 1, word, index + 1, visited)) {
            return 1;                                                              
        }                                                                          
        /* backtrace */                                                            
        visited[x][y] = 0;                                                         
    }                                                                              
                                                                                   
    return 0;                                                                      
}
```

## 三、总结
三步走：  

* 结束条件
* options：往哪个方向走？
* 是否需要回溯？
