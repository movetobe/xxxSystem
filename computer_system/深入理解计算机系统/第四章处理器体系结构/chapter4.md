## 第四章 处理器体系结构

### 处理器顺序实现

* 取指(fetch): 从内存读取指令字节，地址为程序计数器(PC)的值
* 译码(decode): 从寄存器文件读入操作数
* 执行(execute): 算术/逻辑单元(ALU)要么执行指令指明的操作，计算内存引用的有效地址，要么增加或减少栈指针。
* 访存(memory): 从内存读出，或者写入
* 写回(write back): 结果写回寄存器文件
* 更新PC(PC update): 将PC设置成下一个指令的地址。