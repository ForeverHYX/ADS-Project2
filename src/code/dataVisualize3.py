'''
Author: ForeverHYX 2937532336@qq.com
Date: 2024-10-23 03:22:24
LastEditors: ForeverHYX 2937532336@qq.com
LastEditTime: 2024-10-23 03:22:30
FilePath: /code/dataVisualize3.py
Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
'''
import matplotlib.pyplot as plt
import numpy as np

# 数据
heap_types = ['Fibonacci Heap', 'Binary Heap', 'Binomial Heap']
insert_times = [0.000064, 0.000102, 0.000130]
delete_min_times = [0.000615, 0.000294, 0.000493]

# 位置
bar_width = 0.35
index = np.arange(len(heap_types))

# 绘制柱状图
fig, ax = plt.subplots()

bars1 = ax.bar(index, insert_times, bar_width, label='Insert Time (ms)')
bars2 = ax.bar(index + bar_width, delete_min_times, bar_width, label='Delete Min Time (ms)')

# 添加标签
ax.set_xlabel('Heap Type')
ax.set_ylabel('Time (ms)')
ax.set_title('Average Time of Insert and Delete Min Operations for Different Heaps')
ax.set_xticks(index + bar_width / 2)
ax.set_xticklabels(heap_types)

# 显示图例
ax.legend()

# 添加数值标签
def add_labels(bars):
    for bar in bars:
        yval = bar.get_height()
        ax.text(bar.get_x() + bar.get_width()/2, yval, f'{yval:.6f}', va='bottom', ha='center')

add_labels(bars1)
add_labels(bars2)

# 展示图表
plt.tight_layout()
plt.show()
