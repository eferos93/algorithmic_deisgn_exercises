import pandas as pd
import matplotlib.pyplot as plt

dijkstra_times = pd.read_csv("benchmark_data.txt", sep="\t")

ax = plt.gca() #gca = get current axis

dijkstra_times.plot(kind='line', x='Size', y='Dijkstra Heap', ax=ax)
dijkstra_times.plot(kind='line', x='Size', y='Dijkstra Array', ax=ax)
plt.xlabel('Input size')
plt.ylabel('Elapsed time (seconds)')

plt.savefig("benchmark_dijkstra.png")
plt.show("benchmark_dijkstra.png")
