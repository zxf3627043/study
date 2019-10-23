
#encoding:utf-8
import cv2
import numpy as np
import matplotlib.pyplot as plt

img = cv2.imread('ori1.jpg', 1)
imgInfo = img.shape
height = imgInfo[0]
width = imgInfo[1]

gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
count = np.zeros(256, np.float) # 因为是概率, 有可能是浮点数

# 统计像素个数并计算概率
for i in range(height):
    for j in range(width):
        pixel = gray[i, j]
        index = int(pixel)
        count[index] = count[index] + 1

total = height * width # 总像素个数
count =  count / total  # 计算概率

# 画图
x = np.linspace(0, 255, 256)
y = count
plt.bar(x, y, 0.9, alpha = 1, color = "b")
plt.show()
