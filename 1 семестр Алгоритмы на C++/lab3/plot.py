# /// script
# requires-python = ">=3.13"
# dependencies = [
#   "matplotlib",
#   "numpy",
# ]
# ///
import matplotlib.pyplot as plt
import numpy as np

DRAW_LIMIT = 51


def main() -> None:
    quick_sort_times = []
    with open("quick_results.txt") as f:
        quick_sort_times = [float(x) for x in f.read().split()]

    insertion_sort_times = []
    with open("insertion_results.txt") as f:
        insertion_sort_times = [float(x) for x in f.read().split()]

    x = np.arange(0, DRAW_LIMIT, 1, dtype=int)

    plt.figure(figsize=(10, 6))

    plt.plot(x, quick_sort_times[:DRAW_LIMIT], "b-", linewidth=2, label="quick_sort")
    plt.plot(
        x, insertion_sort_times[:DRAW_LIMIT], "r--", linewidth=2, label="insert_sort"
    )

    plt.xticks(x[::2])

    plt.title("Сравнение скорости сортировок на массивах разных размеров")
    plt.xlabel("Размер массива")
    plt.ylabel("Время выполнения")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.margins(x=0.01)

    plt.show()


if __name__ == "__main__":
    main()
