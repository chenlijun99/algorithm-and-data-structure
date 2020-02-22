import random

def merge(arr, left, right, mid):
    tmp = []
    i = left
    j = mid + 1

    while (i <= mid and j <= right):
        if (arr[i] <= arr[j]):
            tmp.append(arr[i])
            i += 1
        else:
            tmp.append(arr[j])
            j += 1

    if (i <= mid):
        tmp += arr[i:mid+1]
    elif (j <= right):
        tmp += arr[j:right+1]

    assert (right - left) + 1 == len(tmp)
    arr[left:right+1] = tmp

    return arr

def mergeSortRec(arr, left, right):
    if (right <= left):
        return arr
    mid = (left + right) // 2
    mergeSortRec(arr, left, mid)
    mergeSortRec(arr, mid + 1, right)
    merge(arr, left, right, mid)
    return arr

def mergeSort(arr):
    return mergeSortRec(arr, 0, len(arr) - 1)

if __name__ == "__main__":
    a = random.sample(range(100), 70)
    print(f"Input: {a}")
    print(f"Sorted: {mergeSort(a)}")
