
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd  # 引入 pandas 库

# 三个不同数据 BAY, FLA, NY
categories = ['BAY', 'FLA', 'NY']

# 五种堆对应的时间数据 (单位: 秒)
binary_heap_times = [0.2172, 0.7922, 0.1887]  # BAY, FLA, NY 的时间
stl_times = [0.1671, 0.7082, 0.1542]         # BAY, FLA, NY 的时间
binomial_heap_times = [0.2302, 0.9498, 0.2437] # BAY, FLA, NY 的时间
skew_heap_times = [0.1335, 0.4605, 0.1193]    # BAY, FLA, NY 的时间
fibonacci_heap_times = [0.253, 0.8718, 0.2232] # BAY, FLA, NY 的时间

# 柱的宽度
bar_width = 0.15

# 设置每种堆的位置偏移
index = np.arange(len(categories))

# 绘制柱状图
plt.figure(figsize=(10, 6))

# 画五种不同堆的柱状图
plt.bar(index, stl_times, bar_width, label='STL Heap')
plt.bar(index + bar_width, binary_heap_times, bar_width, label='Binary Heap')
plt.bar(index + 2 * bar_width, binomial_heap_times, bar_width, label='Binomial Heap')
plt.bar(index + 3 * bar_width, skew_heap_times, bar_width, label='Skew Heap')
plt.bar(index + 4 * bar_width, fibonacci_heap_times, bar_width, label='Fibonacci Heap')

# 设置横坐标刻度和标签
plt.xticks(index + 2 * bar_width, categories)

# 设置标题和坐标轴
plt.title('Heap Performance Comparison in Different Datasets (Time in Seconds)', fontsize=14)
plt.xlabel('Dataset', fontsize=12)
plt.ylabel('Time (s)', fontsize=12)

# 添加图例
plt.legend()

# 展示图表
plt.tight_layout()
plt.show()

# 创建时间记录表格
data = {
    'Dataset': categories,
    'STL Heap (s)': stl_times,
    'Binary Heap (s)': binary_heap_times,
    'Binomial Heap (s)': binomial_heap_times,
    'Skew Heap (s)': skew_heap_times,
    'Fibonacci Heap (s)': fibonacci_heap_times
}

# 使用 pandas 创建 DataFrame
df = pd.DataFrame(data)

# 打印时间记录表格
print("Performance Time Table (in seconds):")
print(df)
