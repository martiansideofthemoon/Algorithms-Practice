def counting_sort(arr=[],lower=0,upper=0):
	counter=[]
	for i in range(0,upper-lower):
		counter.append(0)
	for element in arr:
		if element<lower or element>=upper:
			print "Invalid Bounds!"
			return arr
		counter[element-lower]=counter[element-lower]+1
	for i in range(1,upper-lower):
		counter[i]=counter[i]+counter[i-1]
	sorted_arr=[]
	for i in range(0,len(arr)):
		sorted_arr.append(0)
	for element in reversed(arr): #stable
		sorted_arr[counter[element-lower]-1]=element
		counter[element-lower]=counter[element-lower]-1
	return sorted_arr
print counting_sort([2,4,5,1,5,3,6,2,6,2,8,9],0,10)