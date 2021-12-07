import sys

import pygame

from settings import Settings

def run_game():
    # 初始化游戏设置并创建一个屏幕对象
    pygame.init()
    ai_settings = Settings()
    screen = pygame.display.set_mode(
        (ai_settings.screen_width, ai_settings.screen_height))
    pygame.display.set_caption("Alien Invasion")


    # 开始游戏的主循环
    while True:

        # 监视键盘和鼠标事件
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()

        # 每次循环都重绘屏幕
        screen.fill(ai_settings.bg_color)

        # 让最近绘制的屏幕可见
        # 游戏运行时将不断刷新屏幕显示元素的新位置，并在原来的位置隐藏元素
        # 营造出平滑移动的效果
        pygame.display.flip()

run_game()