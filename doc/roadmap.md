# NEWorld Roadmap

NEWorld 路线图。

**以下所有计划暂时搁置，目前将重写NEWorld并还原至2016/5/1的水平**

本文档中记述关于NEWorld未来发展的一些草案。

0.5.0将会对现有的NEWorld结构做出非常大的修改，创建一个稳定的、可扩展的平台。0.5.0开发代号备选方案：

* Anaviosi (希腊语:复兴)

0.5.x系列在0.5.0平台的基础上，着重在游戏性上添加新特性。

## 完全的跨平台体验

难度  |  计划完成版本  |  钦点开发者
-----|-----|-----
不可预测 | 0.5.0 | 全体

_撰写/2016年4月23日_

在关闭EAX环境音效、网络支持、插件支持的代价之下，NEWorld可以在Mac OS X系统上编译了。但是，运行起来，和Windows版本相比，存在大量的差距，例如

* GUI文本乱码
* Advanced Render不能打开
* (随机地)鼠标移动不平滑
* (随机地)时间忽快忽慢
* (随机地)移动几秒后瞬移回起始点
* (随机地)方块只显示骨架

“(随机地)”表示，该现象有一定概率会发生。运行五六次NEWorld，可能会有一两次出现所描述的现象，重新启动NEWorld之后，一般问题就会消失，当然也有可能连续几次都持续地出现问题。

虽然编写的C/C++代码大部分可以在UNIX-like系统上编译运行，但这和真正意义上的“跨平台”之间还有很大的距离。

## 有完整的注释

难度  |  计划完成版本
-----|-----
易 | 0.5.0

现在的代码缺乏完整的注释，哦不，一点注释都几乎没有。以后所有人写代码，一定要勤注释。以后计划使用Doxygen系统。

## 服务端/客户端分离

难度  |  计划完成版本
-----|-----
较难 | 0.5.0

为了以后可以实现联机特性，客户端和服务端应当分离开。

客户端和服务端将被拆分为两个不同的项目，最终将会编译出两份不同的可执行文件。

### 服务端

服务端是一个命令行程序，实现对世界的逻辑计算，以及处理与客户端的通信。世界的存档在服务端中保存。改变世界类型的MOD(如工业2、Railcraft等)在服务端中运行。

### 客户端

客户端是一个图形化程序，和玩家直接交互，负责输出画面和音效，处理玩家的键盘鼠标输入，并与服务器通信。考虑到网络延迟，客户端需要做一些特殊处理。玩家自身的移动，直接显示在画面中，与服务器通信来修正自己的位置。玩家破坏方块、放置方块，会先直接显示在画面中，与服务器通信来检测是否有权限进行该操作，若无权限则恢复原状。生物和其他玩家的移动，在客户端中做插值计算，通过和服务器通信来修正其各自的位置。光照值等会实时地、直接地影响到最终画面输出的量，也会在客户端上进行计算。改变显示效果的MOD(如小地图等)在客户端运行。

在单人模式中，客户端会调用本地的服务端程序，两者在未来可能通过IPC方式快速地交换数据，节约时间。

### 范例

0. 服务端中的计算决定，世界开始下雨了。服务端将此通知广播到所有客户端上，客户端得知后，开始输出降雨的效果，例如雨滴、雨声等。服务端控制的怪物们的视野会变差，玩家挨得更近，怪物才会发现玩家并追逐，这些计算在服务端完成。

## 跨平台的MOD支持

难度  |  计划完成版本  |  进度
-----|-----|----
较难 | 0.5.0 | 编码完成/等待测试

在0.5.0中至少能够在不同的操作系统(Windows, Linux, Mac OS X)、不同的硬件架构上(x86, ARM)支持基于Native Code的MOD。

之后考虑支持基于Lua、Python的MOD。

## 存档压缩

难度  |  计划完成版本
-----|-----
易 | 0.5.0

Minecraft的存档使用Anvil格式。Anvil格式中，区块以Y Z X的顺序保存世界信息，而在很多时候，同一种类的方块就这样被连续地被保存在了一起。例如高空、海洋、山体内部、隧道、矿洞，在这种存储顺序下，一长条空气、一长条石头会连续地被保存在一块。因此，这种设计下的存档非常便于数据压缩，使用快速低压缩率的压缩算法(如gz、lzf)可以花费极小的时间代价换取非常好的压缩效果。在联机模式中，客户端连接服务器时需要下载地形，经过压缩之后也能极大地节省网络传输时间消耗。

## 工具、武器、食物

难度  |  计划完成版本
-----|-----
中等 | 0.5.0

工具包含斧头、镐子、铲子等。它们各自擅长的功能，例如斧头可以加快对木制品的破坏，铲子可以加快对泥土的破坏。

武器包括剑，相较于拳头可以提供更高的伤害输出。斧头等工具也能用于攻击。“攻击”的功能需要和生物特性联动。

食物包括苹果、面包等。和农业特性联动。

在0.5.0版本中，至少应当完成：在代码中对物品类别建立模型(例如`class Tools : public Objects`)。

## 初步的生物特性

难度  |  计划完成版本
-----|-----
难 | 0.5.0

加入生物，需要绘制生物模型、编写生物相关的代码。

* 通过地图生成器在恰当地点生成野外生物
* 野外生物会在地图上自由乱逛
* 生物拥有自己的血条值，玩家可以攻击生物

在0.5.0版本中，至少应当完成：在代码中对生物建立模型。

## 好用的物品栏

难度  |  计划完成版本
-----|-----
难 | 0.5.0

现在的物品栏太辣鸡。需要实现一个能像Minecraft一样好用的物品栏。

* 改进GUI品相。
* 实现左键拖动、右键分半、Shift取走所有同类方块等功能。

## 改进地图生成器

难度  |  计划完成版本
-----|-----
难 | 0.5.0

加入生物群系的概念，地图生成器先生成“生物群系”分布图，确定哪一个区域是什么生物群系，然后再根据生物群系去生成地形。

* 在“海洋”生物群系中，生成海洋，底部有海床。
* “岛屿”生物群系被“海洋”生物群系包围。表现为一个小型的露出海面的岛屿，以沙子或土地作为表面地形。可能有少量的树结构。
* “河流”生物群系两侧是陆地类型的生物群系，末端和“海洋”生物群系联通。
* 在“草原”生物群系中，生成较为平坦的、以土地方块为表层地形、其上覆盖草的地形，并生成马等动物。
* 在“森林”生物群系中，生成略有高低起伏的、以土地方块为表层地形，其上有茂密的树结构的地形。

## 天气系统与农业

决定于生物群系，可能存在“晴天”、“降雨”、“降雪”、“阴天”、“大风”等天气。

农作物会随着时间生长，天气和光照条件会影响农作物生长的速度，不良条件下农作物会枯萎死亡。

以后可能要内置类似于工业MOD的系统，“大风”可以用于风力发电。

## 矿洞

在地下生成矿洞结构，并可能在地面上表现出几个出口。加入几种类型的矿石。

## 合成台与冶炼炉

Minecraft玩家一定不会陌生。
