### 什么是网络管理？
网络管理就是在管理本ECU各条总线逻辑上的通信状态，上一层次的管理模块根据这些逻辑通信状态，进一步去管理ECU各条总线物理上的通信状态。

### 为什么要有网络管理？
* 上层的管理模块可以根据网络管理模块提供的网络逻辑状态，去改变物理状态，比如在网络睡眠的时候，让ECU进入睡眠，从而降低能源消耗。
* 网络管理模块可以承载一定算法，来更好地管理网络的逻辑状态，从而使网络物理状态切换相对较优。

### 网络管理有什么？
* AUTOSAR标准规范的网络各个状态/场景下的处理算法。

### 网络管理的实现？