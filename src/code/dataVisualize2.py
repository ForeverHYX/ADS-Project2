
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd  

categories = ['BAY', 'FLA', 'NY']

binary_heap_times = [0.2172, 0.7922, 0.1887]  
stl_times = [0.1671, 0.7082, 0.1542]         
binomial_heap_times = [0.2302, 0.9498, 0.2437] 
skew_heap_times = [0.1335, 0.4605, 0.1193]    
fibonacci_heap_times = [0.253, 0.8718, 0.2232] 

bar_width = 0.15

index = np.arange(len(categories))

plt.figure(figsize=(10, 6))

plt.bar(index, stl_times, bar_width, label='STL Heap')
plt.bar(index + bar_width, binary_heap_times, bar_width, label='Binary Heap')
plt.bar(index + 2 * bar_width, binomial_heap_times, bar_width, label='Binomial Heap')
plt.bar(index + 3 * bar_width, skew_heap_times, bar_width, label='Skew Heap')
plt.bar(index + 4 * bar_width, fibonacci_heap_times, bar_width, label='Fibonacci Heap')

plt.xticks(index + 2 * bar_width, categories)

plt.title('Heap Performance Comparison in Different Datasets (Time in Seconds)', fontsize=14)
plt.xlabel('Dataset', fontsize=12)
plt.ylabel('Time (s)', fontsize=12)

plt.legend()

plt.tight_layout()
plt.show()

data = {
    'Dataset': categories,
    'STL Heap (s)': stl_times,
    'Binary Heap (s)': binary_heap_times,
    'Binomial Heap (s)': binomial_heap_times,
    'Skew Heap (s)': skew_heap_times,
    'Fibonacci Heap (s)': fibonacci_heap_times
}

df = pd.DataFrame(data)

print("Performance Time Table (in seconds):")
print(df)
