## 第五章 优化程序性能

### 优化程序性能

* 消除循环的低效率：即将非必要循环的计算放到循环外，不需要每次循环都进行计算
* 减少过程调用：即减少不必要的循环内调用
* 消除不必要的内存引用：减少全局变量的引用，通过局部变量，最后统一赋值全局变量
* 循环展开
* 分支预测：尽可能写出对编译器没有歧义的语句，可以帮助编译器优化代码，应该给编译器确定性的代码
* 性能分析：gprof