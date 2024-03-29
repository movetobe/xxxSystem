## 第九章 虚拟内存
### 虚拟内存
<image src="virtual-addressing-system.png" align=center/>

* 内存管理单元(Memory Management Unit, MMU): CPU芯片上的专用硬件，利用存放在主存中的查询表来动态翻译虚拟地址，该表的内容由操作系统管理。

* 虚拟内存系统将虚拟内存分割为虚拟页(virtual page)，物理内存分割为物理页(physical page)，也称页帧(page frame)，两者大小一致

* 虚拟页面集合包括三个子集:
    * 未分配：虚拟内存系统还未分配/创建的页，没有任何数据关联，不占任何磁盘空间
    * 缓存的：当前已缓存在物理内存中的已分配页
    * 未缓存的：未缓存在物理内存中的已分配页

* SRAM缓存：位于CPU与主存之间的L1/L2/L3高速缓存
* DRAM缓存：位于主存中的缓存虚拟页

### 页表
* 页表(page table)，虚拟页/地址映射到物理页/地址
    * 页表条目(page table entry, PTE)
    * 每个PTE通常由有效位(valid bit)和n位地址组成，有效位标记虚拟页是否缓存在DRAM中。没有设置有效位，则地址指向虚拟页在磁盘的起始位置，否则一个空地址表示虚拟页未分配。

* 多级页表：
    * 一级页表：一个4KB的页表，每个PTE有4B，可以指向1K个4KB页面，则总共能指向4MB内存空间。
    * 两级页表：一个4KB的页表，每个PTE有4B，指向1K个4KB的页表。
* 多级页表减少了内存要求：
    * 如果一级页表的PTE是空的，那么对应的二级页表也是空的
    * 只有一级页表4KB总是在主存中，虚拟内存系统需要时才创建/页面调度/页面调出二级页表

<image src="multi-level-page-table.png" align=center/>

* 缺页(page fault)，产生缺页异常，调用内核缺页异常处理函数，进行页面交换(swapping)/页面调度(paging)，处理完回到产生异常的指令继续执行。

* 内存保护：页表PTE上增加许可位sup/r/w，sup表示进程是否运行在内核模式下才能访问，r/w表示进程对该页面的读写控制

### 地址翻译
* 缺页操作
<image src="page-table-translation-no-tlb.png" align=center/>

* 带TLB的缺页操作
<image src="page-table-translation-tlb.png" align=center/>

### Intel Core i7/Linux
* core i7 地址翻译：
<image src="corei7-address-translation.png" align=center/>

* Linux 虚拟内存管理
<image src="linux-virtual-memory-management.png" align=center/>

### 内存映射(memory mapping)
* 共享对象：映射共享对象到进程中
    * 不进行修改，则都引用到同一块物理内存中
    * 如果映射作为私有对象，都映射到相同的物理内存，但是标记为只读且私有的写时复制(copy-on-write)。即任何进程试图写操作，都会处罚保护故障，保护故障将创建新的物理页面副本，更新页表，标记可写等操作，该进程将对新页面进行写。
    * 典型的应用即为fork操作，两个进程每个区域都是写时复制，任何一个进程写操作都会触发新页面的创建。

### 动态内存分配
* Linux内核为每个进程维护一个堆，指针brk指向堆顶，动态内存从堆中分配而来。

* 碎片
    * 内部碎片(internal fragmentation): 为了字节对齐等原因，分配大小比实际有效载荷大
    * 外部碎片(external fragmentation): 空闲内存足够，但是没有一个单独的空闲块足够

* 如何实现
    * 空闲块组织: 如何记录空闲块
    * 放置: 如何选择一个合适的空闲块来放置一个新分配的块
    * 分割: 新分配的块放置在空闲块之后，如何处理剩余部分
    * 合并: 如何处理刚被释放的块

* 分离的空闲链表：维护多个空闲链表，将块分成大小类(size class)
    * 简单分离存储：每个链表块大小一致，如32/64/128/...，直接找对应链表进行分配
    * 分离适配：简单分离的基础上，如果小块不够，会进行大块的分割，小块也会进行合并成大块
    * 伙伴系统：buddy system, 分离适配的特例，类大小按2的幂进行分割