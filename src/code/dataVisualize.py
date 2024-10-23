
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd  # 新增部分

# 数据规模 - O(N), O(N^1.5), O(N^2)
edges = np.array([10, 100, 1000])  # 你可以根据实际情况更改

# 不同堆在不同数据规模下的时间 (单位: 毫秒)
stl_times = [0.085, 1.388, 12.93]           
binary_heap_times = [0.2162, 2.183, 28.31]   
binomial_heap_times = [0.202, 1.655, 21.83] 
skew_heap_times = [0.1145, 1.802, 20.34]    
fibonacci_heap_times = [0.1452, 1.646, 21.86]

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

# 创建 pandas DataFrame 并展示表格
data = {
    'Edge Growth': ['O(N)', 'O(N^1.5)', 'O(N^2)'],
    'STL Heap (ms)': stl_times,
    'Binary Heap (ms)': binary_heap_times,
    'Binomial Heap (ms)': binomial_heap_times,
    'Skew Heap (ms)': skew_heap_times,
    'Fibonacci Heap (ms)': fibonacci_heap_times
}

# 创建 DataFrame
df = pd.DataFrame(data)

# 打印表格
print("Performance Table:")
print(df)
