import matplotlib.pyplot as plt
import numpy as np

heap_types = ['Fibonacci Heap', 'Binary Heap', 'Binomial Heap']
insert_times = [0.000064, 0.000102, 0.000130]
delete_min_times = [0.000615, 0.000294, 0.000493] # Time consuming

bar_width = 0.35
index = np.arange(len(heap_types)) # x-axis

fig, ax = plt.subplots()

bars1 = ax.bar(index, insert_times, bar_width, label='Insert Time (ms)')
bars2 = ax.bar(index + bar_width, delete_min_times, bar_width, label='Delete Min Time (ms)')

ax.set_xlabel('Heap Type')
ax.set_ylabel('Time (ms)')
ax.set_title('Average Time of Insert and Delete Min Operations for Different Heaps')
ax.set_xticks(index + bar_width / 2)
ax.set_xticklabels(heap_types)

ax.legend()

def add_labels(bars):
    for bar in bars:
        yval = bar.get_height()
        ax.text(bar.get_x() + bar.get_width()/2, yval, f'{yval:.6f}', va='bottom', ha='center')# generate bar graph

add_labels(bars1)
add_labels(bars2)

plt.tight_layout()
plt.show()
