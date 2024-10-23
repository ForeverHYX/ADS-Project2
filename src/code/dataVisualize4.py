import matplotlib.pyplot as plt
import numpy as np

# List of file paths containing the results of different heap implementations
files = [b'ADS/ads-project/ADS-P2-carry/ADS-Project2/src/testcase/quadratic_root/resultsBH.txt', 
         b'ADS/ads-project/ADS-P2-carry/ADS-Project2/src/testcase/quadratic_root/resultsBino.txt', 
         b'ADS/ads-project/ADS-P2-carry/ADS-Project2/src/testcase/quadratic_root/resultsFibo.txt', 
         b'ADS/ads-project/ADS-P2-carry/ADS-Project2/src/testcase/quadratic_root/resultsSkew.txt', 
         b'ADS/ads-project/ADS-P2-carry/ADS-Project2/src/testcase/quadratic_root/resultsSTL.txt']

# Corresponding labels for each heap type
labels = ['Binary', 'Binomial', 'Fibonacci', 'Skew', 'STL']

# Dictionary to store the data read from the files
data = {}

# Reading each file and storing the contents as lists of floating-point values
for file in files:
    with open(file, 'r') as f:
        # Each file contains multiple lines with two numbers per line (node count and time)
        data[file] = [list(map(float, line.split())) for line in f]

# For each file, extract the data, fit a quadratic curve, and plot the results
for file, label in zip(files, labels):
    # Extract the first column (node count) as x and the second column (time) as y
    x = np.array([line[0] for line in data[file]])  # Node count
    y = np.array([line[1] for line in data[file]])  # Execution time in milliseconds
    
    # Fit a quadratic curve (degree 2 polynomial) to the data
    coeffs = np.polyfit(x, y, deg=2)  # Returns the coefficients of the quadratic equation
    poly = np.poly1d(coeffs)  # Create a polynomial object from the coefficients
    
    # Generate a smooth x-axis range for plotting the fitted curve
    x_fit = np.linspace(min(x), max(x), 100)  # 100 evenly spaced points between min(x) and max(x)
    y_fit = poly(x_fit)  # Calculate the y values using the fitted polynomial
    
    # Plot the fitted curve and the original data points
    plt.plot(x_fit, y_fit, label=label)  # Plot the quadratic fit
    plt.scatter(x, y)  # Plot the actual data points

# Add the plot title and axis labels
plt.title('Fitted Comparison of Dijkstra m = O(N^1.5)')
plt.xlabel('Node Count')  # X-axis label
plt.ylabel('Time (milliseconds)')  # Y-axis label

# Add a legend to differentiate between heap implementations
plt.legend()

# Enable grid for better readability of the plot
plt.grid()

# Show the final plot
plt.show()
