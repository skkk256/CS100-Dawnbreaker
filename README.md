# CS100-Dawnbreaker
HW8/9

**DDL:** 
- HW8 - 6/6 总进度30%
- HW9 - 6/20 总进度70%
## Daily Log
#### 5/31
- 新建仓库
- 读题

#### 6/1
- 数分 quiz。。。。寄了😭😭😭😭😭

#### 6/2
- HW8 ✅

#### 6/3
- 端午安康
- HW8submission 开放
- 过了✌

#### 6/4
- nnd 傻\*OJ怎么regrade了？？
- 修 bug....
- 为什么会有傻宝少放了一颗 Star 呀
- 为什么会有傻宝初始 upgradeTimes 是1啊
- ( 应该是0
- 改着改着开始叠屎山了💩💩
- done✅
- enemy 已加入
- 浅浅地做了点碰撞检测

#### 6/5
- descrete_mathing
- 摸鱼🐟🐟

#### 6/11
- 堆屎山
- 似乎差不多了✌🔦

#### 6/12
- 本地能跑了
- OJ 还没开...
- 但是 HW10 开了😅😅...
- HW10 不会做🌿🌿🌿

#### 6/22
- 似乎很久没更新了来着
- hw9 OJ大寄
- 幸好在 ddl 前把 hw9/10 de完了
- 还留了两天摆烂 and 开了把群星👽
- 虽然提交次数有点感人(x
- private->public
- bug来源如下
- case ... : GameWorld.Update() 函数中各子项执行的顺序有问题，更新 bar 没有在遍历各对象 update 函数之后
- case 9: alphatron 通过添加 tag 方式发射子弹，使加入子弹的位置是基于移动后的飞机坐标
- case 19: Enemy 类在撞击 dawnbreaker 后没有判断 dawnbreaker 血量是否小于 0，并摧毁
