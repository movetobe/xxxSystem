## 第一章 计算机系统漫游

### 编译系统

源程序hello.c -> 预处理器(cpp) -> 修改了的源程序hello.i -> 编译器(ccl) -> 汇编程序hello.s -> 汇编器(as) -> 可重定位目标程序hello.o -> 链接器(ld) -> 可执行目标程序hello

* 预处理：修改源程序，如#include展开，宏处理等
* 编译阶段：将文件文件hello.i翻译成hello.s，包含汇编语言程序
* 汇编阶段：将hello.s翻译成机器语言指令，打包成可重定位目标程序格式，二进制格式
* 链接阶段：合并可重定位目标程序，即多个.o链接合并成可执行程序

### 处理器

处理器核心是一个程序计数器(PC)，其实就是一个寄存器。任何时候，PC都指向主存中的一条机器语言指令。处理器的操作围绕主存、寄存器、算术/逻辑单元(ALU)进行：

* 加载：从主存中复制一个字节/字道寄存器
* 存储：从寄存器复制一个字节/字到主存中
* 操作：两个寄存器中的内容复制到ALU，对这两个数进行操作，并将结果放入一个寄存器中
* 跳转：从指令中抽取一个字，并将这个字复制到PC中

### Unix进程虚拟内存空间

从低地址往高地址：
* 只读的代码和数据
* 可读写数据
* 堆
* 共享库内存映射区域
* 栈
* 内核虚拟内存

### 并发(Concurrency)与并行(Parallelism)

* 线程级并发
* 指令级并行
* 单指令、多数据并行：即SIMD并行，允许一条指令产生多个可以并行执行的操作。