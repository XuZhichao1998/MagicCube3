### Magic Cube3
class Cube3
It is a cpp class to solve problems about Magic Cube(3\*3)

目前（`2021-02-26 12:45`）实现的功能：

1. 生成一个打乱，并且展示打乱后的状态
2. 调用相应的函数，实现R L U D F B和对应的双层，逆向转动
3. 根据给定的打乱公式打乱魔方

打乱的效果如下
```
F' U R B2 L' F' U B' F B U2 L2 R U' B2 D' U' D2 R' U2 
魔方展开图如下：
  上
左前右后
  下
-----------------------------------------
        蓝黄蓝
        白黄黄
        红红白

橙蓝绿  黄黄绿  红蓝红  黄绿黄
白蓝红  绿红黄  橙绿红  蓝橙绿
蓝红白  橙橙黄  橙绿橙  白蓝白

        蓝白绿
        白白橙
        红橙绿
-----------------------------------------
```
