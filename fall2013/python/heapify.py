a = [0,1,2,3,4,5,6,7,8,9,10,11]

# a = [0,6,1,2,3,4,5,7,8,9,10,11,30,25,34,99,43,-1,-2,35,23]

def MaxHeapify(list):
	for x in range(len(list)/2+1,0,-1):
		j = x
		while j <= len(list)-1:
			# print j
			# print x
			c1 = j*2
			c2 = c1+1	
			if c1 >= len(list):
				break
			if c2 >= len(list):
				if list[c1] >list[j]:
					list[c1], list[j] = list[j], list[c1]
					# j = c1
					break
			# if c1 >= len(list):
			# 	if list[c2] >list[j]:
			# 		list[c2], list[j] = list[j], list[c2]
			# 		j = c2
			# 		break
			# print list[c1]
			# print list[c2]
			c = c1 if list[c1]>list[c2] else c2
			# print c
			if list[c] > list[j]:
				list[c], list[j] = list[j], list[c]
			j = c
			# print list

# def MaxHeapify(list):
# 	for x in range(len(list)/2+1,0,-1):
# 		j = x
# 		while j <= len(list)-1:
# 			c1 = j*2
# 			c2 = c1+1	
# 			if c1 >= len(list) and c2 >= len(list):
# 				j = c1
# 				continue
# 			if c2 >= len(list):
# 				list[c1], list[j] = list[j], list[c1]
# 				j = c1
# 				continue
# 			if c1 >= len(list):
# 				list[c2], list[j] = list[j], list[c2]
# 				j = c2
# 				continue
# 			c = c1 if list[c1]>list[c2] else c2
# 			list[c], list[j] = list[j], list[c]
# 			j = c
# 		print list

print a

MaxHeapify(a)

print a
