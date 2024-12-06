# -*- coding:sjis -*-
import pygame
import codecs
import os


def main():
    # �t�H���g�R�[�h�������ꂽ�e�L�X�g��ǂݍ��݂܂�
    file = codecs.open('fnt_idx.txt', 'r', 'utf_16')
    str = file.read()
    file.close()


    # �T�[�t�F�C�X�̑傫�����`���܂�
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


    # ttf�t�H���g��ǂݍ��݂܂�
    font = pygame.font.Font("misaki_gothic_2nd.ttf", fs)


    # 1�����ÂA�T�[�t�F�C�X�ɏ�������ł����܂�
    x = 0
    y = 0
    for i in range(len(str)):
        sur = font.render(str[i], True, (0,0,0))
        scn.blit(sur, (x,y))
        x = x + fx
        if x >= cx:
            x = 0
            y = y + fy

    # �T�[�t�F�C�X��ۑ����܂�
    pygame.image.save(scn, "fnt_m8x8.bmp")
    return


if __name__ == '__main__': main()
# end of file
