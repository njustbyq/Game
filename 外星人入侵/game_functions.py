import sys

import pygame
from bullet import Bullet

def check_keydown_events(event, ai_settings, screen, ship, bullets):
    """响应按键"""
    if event.key == pygame.K_RIGHT:
        ship.moving_right = True
    elif event.key == pygame.K_SPACE:
        fire_bullets(ai_settings, screen, ship, bullets)

def fire_bullets(ai_settings, screen, ship, bullets):
    """如果还没达到限制, 就发射一颗子弹"""
    # 创建新子弹并将其加入到编组bullets中
    if len(bullets) < ai_settings.bullets_allowed:
        new_bullet = Bullet(ai_settings, screen, ship)
        bullets.add(new_bullet)
    elif event.key == pygame.K_LEFT:
        ship.moving_left = True

def check_keyup_events(event, ship):
    """响应松开"""
    if event.key == pygame.K_RIGHT:
        ship.moving_right = False
    elif event.key == pygame.K_LEFT:
        ship.moving_left = False

def check_events(ai_settings, screen, ship, bullets):
    """响应按键和鼠标事件"""
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
        elif event.type == pygame.KEYDOWN:
            check_keydown_events(event, ai_settings, screen, ship, bullets)
        elif event.type == pygame.KEYUP:
            check_keyup_events(event, ship)

def update_screen(ai_settings, screen, ship, bullets):
    # 每次循环都重绘屏幕
    screen.fill(ai_settings.bg_color)
    # 在飞船和外星人后面重绘所以子弹
    for bullet in bullets.sprites():
        bullet.draw_bullet()
    ship.blitme()

    # 让最近绘制的屏幕可见
    # 游戏运行时将不断刷新屏幕显示元素的新位置，并在原来的位置隐藏元素
    # 营造出平滑移动的效果
    pygame.display.flip()

def update_bullets(bullets):
    """更新子弹的位置, 并删除已消失的子弹"""
    # 更新子弹的位置
    bullets.update()

    #删除消失的子弹
    for bullet in bullets.copy():
        if bullet.rect.bottom <= 0:
            bullets.remove(bullet)
        