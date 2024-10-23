import matplotlib.pyplot as plt

files = ['resultBH.txt', 'resultBino.txt', 'resultFibo.txt', 'resultSkew.txt', 'resultSTL.txt']
labels = ['Binary', 'Binomial', 'Fibonacci', 'Skew', 'STL']
data = {}

for file in files:
    with open(file, 'r') as f:
        data[file] = [list(map(float, line.split())) for line in f]

for file, label in zip(files, labels):
    x = [line[0] for line in data[file]] 
    y = [line[1] for line in data[file]] 
    plt.plot(x, y, marker='o', label=label)

plt.title('Comparison of Dijkstra Times')
plt.xlabel('Node Count')
plt.ylabel('Time (milliseconds)')
plt.legend()
plt.grid()
plt.show()
