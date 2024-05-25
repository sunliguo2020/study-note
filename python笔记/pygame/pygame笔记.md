### pygame坐标
原点在左上角（0,0）
x轴水平方向向右，逐渐增加
y轴垂直方向向下，逐渐增加
右下角的坐标为窗口设置的宽高值
### 游戏刷新率
### Demo演示
加载一张背景图片，一张英雄图片及一张怪物图片到pygame的游戏窗口中，并进行显示。
```python
import pygame
from pygame.locals import *
import sys

# 使用pygame之前必须初始化
pygame.init()
# 设置用于显示的窗口，单位为像素
screen = pygame.display.set_mode((800, 400))
# 设置标题
pygame.display.set_caption("MyGame")

# 加载图片
bg_img = pygame.image.load("bg.jpg").convert()  # 背景图片
hero_img = pygame.image.load("new_hero.png").convert_alpha()  # 人物图片
monster_img = pygame.image.load("new_monster.png").convert_alpha()  # 怪物图片

# 渲染图片
screen.blit(bg_img, (0, 0))  # 绘制背景
screen.blit(hero_img, (180, 180))  # 绘制人物
screen.blit(monster_img, (560, 180))  # 绘制怪物

while True:
    for event in pygame.event.get():  # 循环获取事件
        if event.type == QUIT:  # 若检测到事件类型为退出，则退出系统
            pygame.quit()
            sys.exit()
    pygame.display.update()  # 刷新屏幕内容
```
### pygame加载图片
1、加载图片

```python
# 加载图片
image = "background.png"
backgroud_img = pygame.image.load(image) # 加载方式1（适用于任何普通图像）
backgroud_img  = pygame.image.load(image).convert() # 加载方式2（适用于普通图像，提高渲染速度）
```
```
plan = pygame.image.load('plane.png')
WindowSurface.blit(plane,(40,30))
```

2、渲染图片

第一个参数代表要渲染的对象，第二个参数代表对象要渲染到窗口的哪个位置。

```
# blit(要渲染的对象，（x坐标，y坐标）)
screen.blit(bg_img, (0, 0))  # 绘制背景
screen.blit(hero_img, (180, 180))  # 绘制人物
screen.blit(monster_img, (560, 180))  # 绘制怪物
```

渲染顺序

在渲染多张图片的时候，其实是有渲染顺序的。先渲染的会在最底层，后渲染的会在上一层进行渲染，如果有重叠的部分，那么后渲染的会覆盖前一张渲染的图片



3、刷新窗口

图片被渲染后并不会立即被显示出来。pygame需要刷新当前的窗口才能够将图片显示出来。这里可以参考上面的游戏刷新率的概念，也就是pygame是通过不停的刷新来更新窗口显示的内容的。

```
pygame.display.update()  # 刷新屏幕内容
```

