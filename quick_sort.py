#!/usr/bin/python
def swap(arr,i,j):
	temp=arr[i]
	arr[i]=arr[j]
	arr[j]=temp

def partition(arr=[]):
	pivot=arr[0]
	i=0
	for j in range(1,len(arr)):
		if arr[j]<pivot:
			swap(arr,i+1,j)
			i=i+1
	swap(arr,0,i)
	return i

def quicksort(arr=[]):
	if arr==[]:
		return arr
	p = partition(arr)
	print str(p) + " for " + str(arr)
	output_arr = []
	output_arr.extend(quicksort(arr[0:p]))
	output_arr.append(arr[p])
	output_arr.extend(quicksort(arr[p+1:]))
	return output_arr

print quicksort([4,7,2,1,8,9,66,22,82,41,14,33])