import pandas as pd
import matplotlib.pyplot as plt
import os

min_heap_times = pd.read_csv("benchmark.txt", sep="\t")
min_heap_times.columns = ["n", "On Heaps (two arrays)", "On Arrays"]
ax = plt.gca() #gca = get current axis

min_heap_times.plot(kind='line', x='n', y='On Heaps (two arrays)', ax=ax)
min_heap_times.plot(kind='line', x='n', y='On Arrays', ax=ax)
plt.xlabel('Input size')
plt.ylabel('Elapsed time (seconds)')

plt.savefig("benchmark_heaps.png")
plt.show("benchmark_heaps.png")

min_heap_normal_times = pd.read_csv(os.path.join("..", "..", "02_heaps", "benchmark_plot", "benchmark.txt"), sep="\t")
min_heap_normal_times.columns = ["n", "On Heaps (normal)", "On Arrays"]
_ = plt.figure()
ax = plt.gca()
min_heap_times.plot(kind='line', x='n', y="On Heaps (two arrays)", ax=ax)
min_heap_normal_times.plot(kind='line', x='n', y='On Heaps (normal)', ax=ax)

plt.xlabel('Input size')
plt.ylabel('Elapsed time (seconds)')

plt.savefig("benchmark_heap_implemetations.png")
plt.show("benchmark_heap_implementations.png")
