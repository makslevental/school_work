from itertools import chain

vertexes = [[0,False],[1,False],[2,False],[3,False],[4,False],[5,False],[6,False],[7,False]]

adjacencyLst = [[[vertexes[0],vertexes[1],1],[vertexes[0],vertexes[2],1],[vertexes[0],vertexes[4],1]],
		 	    [[vertexes[1],vertexes[0],1],[vertexes[1],vertexes[2],1],[vertexes[1],vertexes[3],1],[vertexes[1],vertexes[5],1],[vertexes[1],vertexes[6],1]],
		 	    [[vertexes[2],vertexes[0],1],[vertexes[2],vertexes[1],1],[vertexes[2],vertexes[4],1],[vertexes[2],vertexes[6],1]],
		 	    [[vertexes[3],vertexes[1],1],[vertexes[3],vertexes[5],1],[vertexes[3],vertexes[7],1]],
		 	    [[vertexes[4],vertexes[0],1],[vertexes[4],vertexes[2],1],[vertexes[4],vertexes[6],1]],
		        [[vertexes[5],vertexes[1],1],[vertexes[5],vertexes[3],1],[vertexes[5],vertexes[6],1]],
		        [[vertexes[6],vertexes[1],1],[vertexes[6],vertexes[2],1],[vertexes[6],vertexes[4],1],[vertexes[6],vertexes[5],1]],
		        [[vertexes[7],vertexes[3],1]]]

edges = list(chain.from_iterable(adjacencyLst))

def reverse_edge(lst):
	new_edge = [lst[1],lst[0],lst[2]]
	return new_edge
j = 0
for i in edges:
	print j , i
	j+=1

for i in range(len(edges)):
	if edges[i] == None :
		continue
	for j in range(i+1,len(edges)):
		if edges[j] == None :
			continue
		rev = reverse_edge(edges[i])
		if rev == edges[j]:
			edges[j] = None

edges = [x for x in edges if x != None ]

