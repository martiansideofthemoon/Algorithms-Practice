#!/usr/bin/python
import math,sys
def merge(arr1=[],arr2=[]):
	i=0
	j=0
	arr3=[]
	while i<len(arr1) and j<len(arr2):
		if arr1[i]<=arr2[j]:
			arr3.append(arr1[i])
			i=i+1
		else:
			arr3.append(arr2[j])
			j=j+1
	if i==len(arr1):
		 arr3.extend(arr2[j:])
	else:
		arr3.extend(arr1[i:])
	return arr3

def merge_sort(arr=[]):
	length = len(arr)
	if length==1:
		return arr
	else:
		arr1 = arr[:int(math.ceil(length/2))]
		arr2 = arr[int(math.ceil(length/2)):]
		return merge(merge_sort(arr1),merge_sort(arr2))
input_arr = []
for i in range(10,0,-1):
	input_arr.append(i)
merge_sort(input_arr)
