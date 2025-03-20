# -*- coding:sjis -*-
import pygame
import codecs
import os


def main():
    # フォントコードが書かれたテキストを読み込みます
    file = codecs.open('fnt_idx.txt', 'r', 'utf_16')
    str = file.read()
    file.close()


    # サーフェイスの大きさを定義します
    # FontSize
    fs = 8
    # FontX, Y
    fx = 8
    fy = 8
    # SurfaceCX, CY
    cx = 32  * fx
    cy = 218 * fy

    pygame.init()
    scn = pygame.Surface((cx, cy))
    scn.fill((255, 255, 255))


    # ttfフォントを読み込みます
    font = pygame.font.Font("misaki_gothic_2nd.ttf", fs)


    # 1文字づつ、サーフェイスに書き込んでいきます
    x = 0
    y = 0
    for i in range(len(str)):
        sur = font.render(str[i], True, (0,0,0))
        scn.blit(sur, (x,y))
        x = x + fx
        if x >= cx:
            x = 0
            y = y + fy

    # サーフェイスを保存します
    pygame.image.save(scn, "fnt_m8x8.bmp")
    return


if __name__ == '__main__': main()
# end of file
