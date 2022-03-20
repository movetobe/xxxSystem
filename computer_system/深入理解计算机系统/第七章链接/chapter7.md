## 第七章 链接

### 编译器驱动程序
1. C预处理器(cpp)将源程序.c翻译成ASCII码的中间文件.i
1. C编译器(ccl)将.i翻译成ASCII汇编语言文件.s
1. 汇编器(as)将.s翻译成可重定位目标文件(relocatable object file).o
1. 链接器(ld)将.o链接成可执行目标文件(executable object file)
1. 加载器(loader)将可执行程序的代码和数据复制到内存，然后控制转移到程序开头

### 静态链接(static linker)
链接器两个主要任务：
* 符号解析(symbol resolution): 目标文件定义和引用符号，每个符号对应一个函数、一个全局变量或者一个静态变量。符号解析的目的就是将每个符号引用正好和一个符号定义关联起来
* 重定位(relocation): 编译器和汇编器生成从0开始的代码和数据节。链接器通过把每个符号定义与一个内存位置关联起来，从而重定位这些节，然后修改所有对这些符号的引用，使得它们执行这个内存位置。

### 目标文件
目标文件三种形式：
* 可重定位目标文件: .o
* 可执行目标文件: 可执行文件
* 共享目标文件: .so

### ELF(Executable and Linkable Format)
典型的ELF可重定位目标文件包含：
* .text
* .rodata
* .data
* .bss
* .symtab: 在程序中定义和引用的全局变量的信息，每个可重定位目标文件无需-g选项，在.symtab中都有一张符号表，除非用strip命令去掉。
* .rel.text: 当链接器把这个目标文件与其他文件组合时，需要修改这些位置。
* .rel.data: 被模块引用或定义的所有全局变量的重定位信息
* .debug: -g选项得到的调试符号表

### 重定位条目
* 重定位相对引用：通常是函数调用，得到相对当前PC的offset值，运行时执行PC + offset的指令
* 重定位绝对引用：通常是全局变量的引用，得到的全局变量的绝对地址

### 动态链接共享库
* 动态链接器(dynamic linker)执行动态链接，将共享库/共享目标(shared object)加载到任意内存地址
* Linux提供dlopen/dlsym/dlclose等接口进行动态共享库的引用
* -fpic加载无需重定位的位置无关代码(Position-Independent Code)
* 动态链接过程：
    * PIC数据引用：在数据段开始的地方创建一个全局偏移量表(Global Offset Table, GOT)，每个被这个目标模块引用的全局数据目标都有一个条目，动态链接器会重定位GOT中的每个条目，使它包含正确的绝对地址。
    * PIC函数调用：GNU编译系统使用延迟绑定(lazy binding)技术，在第一次调用时，才会动态链接进行绑定解析，其中用到了GOT和过程链接表(Procedure Linkage Table, PLT)
        * PLT: PLT是一个数组，每个条目16字节代码，PLT[0]是一个特殊条目，跳转到动态链接器。每个被可执行程序调用的库函数都有它自己的PLT条目
        * GOT: GOT[0]和GOT[1]包含动态链接器在解析函数地址时会使用的信息，GOT[2]是动态链接器在ld-linux.so模块中的入口点，其余每个条目对应一个被调用的函数，其地址需要在运行时被解析。

* 动态链接第一个和后续过程：
    <image src="pic-function-call.png" align=center/>


### 库打桩
* 编译时打桩: 增加编译选项，-DCOMPILETIME，自己代码中实现对应的库函数

* 链接时打桩: 增加编译选项-DLINKTIME，链接选项-Wl, --wrap,f。Linux静态链接器支持用--wrap_f标志进行链接时打桩，告诉链接器，把对f的引用解析成__wrap_f，还要把对符号__real_f的应用解析成f

* 运行时打桩: -DRUNTIME，设置LD_PRELOAD，运行时将优先搜索LD_PRELOAD库，然后才搜索其他库。