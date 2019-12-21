import random

def insertionSort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while (j >= 0 and key < arr[j]):
            arr[j+1] = arr[j]
            j -= 1
        arr[j+1] = key
    return arr

if __name__ == "__main__":
    a = random.sample(range(100), 70)
    print(f"Input: {a}")
    print(f"Sorted: {insertionSort(a)}")
