## 第三章 程序的机器级表示

### x86-64操作数格式 (AT&T格式汇编)
#### 立即数寻址
* 格式: $\$Imm$
* 操作数值: $Imm$

#### 寄存器寻址
* 格式: $r_a$
* 操作数值: $R[r_a]$

#### 绝对寻址
* 格式: $Imm$
* 操作数值: $M[Imm]$

#### 间接寻址
* 格式: $(r_a)$
* 操作数值: $M[R[r_a]]$

#### (基址 + 偏移量)寻址
* 格式: $Imm(r_b)$
* 操作数值: $M[Imm + R[r_b]]$

#### 变址寻址
* 格式: $(r_b, r_i)$
* 操作数值: $M[R[r_b] + R[r_i]]$

* 格式: $Imm(r_b, r_i)$
* 操作数值: $M[Imm + R[r_b] + R[r_i]]$

#### 比例变址寻址, s必须是1/2/4/8
* 格式: $(, r_i, s)$
* 操作数值: $M[R[r_i] \cdot s]$

* 格式: $Imm(, r_i, s)$
* 操作数值: $M[Imm + R[r_i] \cdot s]$

* 格式: $(r_b, r_i, s)$
* 操作数值: $M[R[r_b] + R[r_i] \cdot s]$

* 格式: $Imm(r_b, r_i, s)$
* 操作数值: $M[Imm + R[r_b] + R[r_i] \cdot s]$


### 数据传送指令MOV
#### MOV S, D
* movb/movw/movl/movq分别传送1/2/4/8字节数据
* movabsq传送绝对的8字节
* 源操作数是一个立即数，存储在寄存器或者内存中
* 目的操作数要么是寄存器或者内存地址
* x86-64要求不能两个操作数都是内存地址，内存-####内存需要两条指令完成
* movl指令以寄存器作为目的时，会把该寄存器的高4字节置0

#### MOVZ S, R
* 把目的中剩余字节填充0
* movzbw/movzbl/movzbq/movzwl/movzwq

#### MOVS S, R
* 把目的剩余字节填充符号位
* movsbw/movsbl/movsbq/movswl/movswq/movslq
* cltq 将%eax符号拓展到%rax

### 压栈和弹栈指令
#### pushq S
* 将8字节压栈，栈指针保存在$\%rsp$中
* $R[\%rsp] = R[\%rsp] - 8$
* $M[R[\%rsp]] = S$

#### popq D
* 将8字节出栈
* $D = M[R[\%rsp]]$
* $R[\%rsp] = R[\%rsp] + 8$

### 算术与逻辑指令
#### leaq S, D
* 将S的地址加载到D中，即$D = \&S$

#### INC D
* $D = D + 1$

#### DEC D
* $D = D - 1$

#### NEG D
* $D = -D$

#### NOT D
* $D = ~D$

#### ADD S, D
* $D = D + S$

#### SUB S, D
* $D = D - S$

#### IMUL S, D
* $D = D * S$

#### XOR S, D
* $D = D ^ S$

#### OR S, D
* $D = D | S$

#### AND S, D
* $D = D \& S$

#### SAL k, D
* $D = D << k$

#### SHL k, D
* $D = D << k$

#### SAR k, D
* $D = D >> k$
* 算术右移

#### SHR k, D
* $D = D >> k$
* 逻辑右移

### 控制指令
#### CMP S1, S2
* 比较S1和S2的值
* 条件码寄存器：CF(进位标志)/ZF(零标志)/SF(符号标志)/OF(溢出标志)

#### jmp Label
* 直接跳转

#### jmp *Operand
* 间接跳转

#### je/jz/jne/jnz Label
* 相等/零 或者 不相等/非零的时候跳转
* 条件控制转移涉及分支预测，一旦预测失败，影响流水线，进而影响性能。
* 可以采用条件传送指令

#### 条件控制转移：
```
if (test-express) {
    then-express;
} else {
    else-express;
}
```
#### 条件传送：
```
v = then-express;
ve = else-express;
if (!test-express) v = ve;
```

### switch语句
* switch语句通过跳转表直接跳转到对应的分支上

### 对抗缓冲区溢出攻击
#### 栈随机化
* 栈随机化的思想是使栈的位置在程序每次运行时都有变化。
* 实现原理：
    * 程序开始时，在栈上分配0-n字节之间的随机大小的空间，程序不使用这段空间，但是它会导致程序每次执行时，后续的栈位置发生变化。
    * 分配的范围n必须足够大，才能获得足够多的栈地址变化，又要足够小，不至于浪费程序太多的空间。
* Linux中该类技术成为标准，称为地址空间布局随机化(Address-Space Layout Randomization, ASLR)，每次运行时，程序代码/库代码/栈/全局变量/堆数据都会被加载到内存的不同区域。

#### 栈破坏检测
* 栈保护(stack protector)机制，其思想是在栈帧中任何局部缓冲区与栈状态之间存储一个特殊的金丝雀(canary)值。
* 金丝雀值是运行时随机产生的，当恢复寄存器状态和从函数返回前，检查金丝雀值是否被改变。
* gcc中编译选项-fstack-protector会在相应位置产生金丝雀检查代码，如果检查失败，会执行__stack_chk_fail

#### 限制可执行代码区域
* 通过限制内存区域的可执行权限，可以消除攻击者在内存区域插入可执行代码的能力。