#### 常用模块

pygame.cdrom

pygame.cursors

pygame.Color

pygame.display

pygame.draw 绘制形状、线和点

pygame.font 使用字体

pygame.image 加载和存储图片

pygame.joystick

pygame.key

pygame.mixer

pygame.mouse

display常用模块

```python
pygame.display.init()
pygame.display.quit()
pygame.display.get_init()
```



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

### get_rect()

在`pygame`库中，`get_rect()`方法常用于获取图像或Surface对象的矩形区域（或边界框）。这个矩形区域包含了图像或Surface的所有像素，并且可以用来进行碰撞检测、位置定位等。

具体来说，`get_rect()`方法返回一个`pygame.Rect`对象，该对象有四个主要的属性：`x`（左上角x坐标）、`y`（左上角y坐标）、`width`（宽度）和`height`（高度）。

但是，需要注意的是，当你对一个图像或Surface对象调用`get_rect()`方法时，默认情况下，返回的矩形区域的`(x, y)`坐标是`(0, 0)`，即左上角位于图像或Surface的左上角。这通常不是你想要的，因为你可能希望这个矩形与图像或Surface一起在屏幕上移动。

因此，在实际使用中，你通常会先调用`get_rect()`方法获取一个矩形对象，然后设置这个对象的`(x, y)`属性为你想要的位置。例如：

```python
import pygame  
  
# 初始化pygame  
pygame.init()  
  
# 创建一个窗口  
screen = pygame.display.set_mode((800, 600))  
  
# 加载一个图像  
image = pygame.image.load('my_image.png')  
  
# 获取图像的矩形区域  
rect = image.get_rect()  
  
# 设置矩形区域的位置（例如，将其置于屏幕中央）  
rect.center = (screen.get_width() // 2, screen.get_height() // 2)  
  
# 在屏幕上绘制图像（使用其矩形区域的位置）  
screen.blit(image, rect.topleft)  
  
# 更新屏幕显示  
pygame.display.flip()  
  
# 后续的游戏循环...
```

在上面的例子中，我们首先加载了一个图像，并使用`get_rect()`方法获取了它的矩形区域。然后，我们设置了矩形区域的中心位置为屏幕的中央。最后，我们使用`blit()`方法将图像绘制到屏幕上，其中`rect.topleft`给出了图像的左上角位置（这是由矩形区域的`(x, y)`坐标给出的）。
