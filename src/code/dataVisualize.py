import numpy as np
import matplotlib.pyplot as plt

# 数据规模 - O(N), O(N^1.5), O(N^2)
edges = np.array([10, 100, 1000])  # 你可以根据实际情况更改

# 不同堆在不同数据规模下的时间 (单位: 毫秒)
# 请用你自己的数据替换这里的时间值
stl_times = [1, 10, 100]           # 这是你需要填入的时间数据
binary_heap_times = [2, 12, 110]    # 你自己的数据
binomial_heap_times = [1.5, 11, 105]# 你自己的数据
skew_heap_times = [1.8, 13, 120]    # 你自己的数据
fibonacci_heap_times = [1.2, 9, 95] # 你自己的数据

# 绘制折线图
plt.figure(figsize=(10, 6))

plt.plot(edges, stl_times, label="STL Heap", marker='o')
plt.plot(edges, binary_heap_times, label="Binary Heap", marker='x')
plt.plot(edges, binomial_heap_times, label="Binomial Heap", marker='s')
plt.plot(edges, skew_heap_times, label="Skew Heap", marker='^')
plt.plot(edges, fibonacci_heap_times, label="Fibonacci Heap", marker='d')

# 设置横轴为对数坐标以更好展示不同规模的数据
plt.xscale('log')
plt.xticks(edges, ['O(N)', 'O(N^1.5)', 'O(N^2)'])  # 自定义刻度标签

# 添加图例、标题和坐标轴标签
plt.title('Performance of Different Heaps at Various Data Scales', fontsize=14)
plt.xlabel('Edge Growth (O(N), O(N^1.5), O(N^2))', fontsize=12)
plt.ylabel('Time (ms)', fontsize=12)
plt.legend()

# 展示图表
plt.grid(True)
plt.show()
