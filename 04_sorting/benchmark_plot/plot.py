import pandas as pd
import matplotlib.pyplot as plt

insertion_sort = pd.read_csv("insert_sort.txt", sep="\t")

ax = plt.gca() #gca = get current axis

insertion_sort.plot(kind='line', x='Size', y='insert_sort_random', ax=ax)
insertion_sort.plot(kind='line', x='Size', y='insert_sort_best', ax=ax)
insertion_sort.plot(kind='line', x='Size', y='insert_sort_worst', ax=ax)

plt.xlabel('Input size')
plt.ylabel('Elapsed time (seconds)')

plt.savefig("benchmark_insert_sort.png")
plt.show("benchmark_insert_sort.png")

quick_sort = pd.read_csv("quicksort.txt", sep="\t")

ax = plt.gca() #gca = get current axis

quick_sort.plot(kind='line', x='Size', y='quick_random', ax=ax)
quick_sort.plot(kind='line', x='Size', y='quick_worst', ax=ax)
quick_sort.plot(kind='line', x='Size', y='quick+select_random', ax=ax)
quick_sort.plot(kind='line', x='Size', y='quick+select_worst', ax=ax)

plt.xlabel('Input size')
plt.ylabel('Elapsed time (seconds)')

plt.savefig("benchmark_quicksort.png")
plt.show("benchmark_quicksort.png")

all_times = pd.read_csv("all.txt", sep="\t")

ax = plt.gca() #gca = get current axis

all_times.plot(kind='line', x='Size', y='insert_sort_random', ax=ax)
all_times.plot(kind='line', x='Size', y='quick_random', ax=ax)
all_times.plot(kind='line', x='Size', y='bubble', ax=ax)
all_times.plot(kind='line', x='Size', y='selection_sort', ax=ax)
all_times.plot(kind='line', x='Size', y='heap_sort', ax=ax)

plt.xlabel('Input size')
plt.ylabel('Elapsed time (seconds)')

plt.savefig("benchmark_all.png")
plt.show("benchmark_all.png")

quick_vs_heap = pd.read_csv("quick_vs_heap.txt", sep="\t")

ax = plt.gca() #gca = get current axis

quick_vs_heap.plot(kind='line', x='Size', y='quick_random', ax=ax)
quick_vs_heap.plot(kind='line', x='Size', y='quick+select_random', ax=ax)
quick_vs_heap.plot(kind='line', x='Size', y='heap_sort', ax=ax)


plt.xlabel('Input size')
plt.ylabel('Elapsed time (seconds)')

plt.savefig("benchmark_quick_vs_heap.png")
plt.show("benchmark_quick_vs_heap.png")