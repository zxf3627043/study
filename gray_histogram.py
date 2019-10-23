
#encoding:utf-8
import cv2
import numpy as np
import matplotlib.pyplot as plt

img = cv2.imread('ori1.jpg', 1)
imgInfo = img.shape
height = imgInfo[0]
width = imgInfo[1]

gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
count = np.zeros(256, np.float) # ��Ϊ�Ǹ���, �п����Ǹ�����

# ͳ�����ظ������������
for i in range(height):
    for j in range(width):
        pixel = gray[i, j]
        index = int(pixel)
        count[index] = count[index] + 1

total = height * width # �����ظ���
count =  count / total  # �������

# ��ͼ
x = np.linspace(0, 255, 256)
y = count
plt.bar(x, y, 0.9, alpha = 1, color = "b")
plt.show()
