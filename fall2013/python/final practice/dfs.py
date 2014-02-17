
vertexes = [[0,False],[1,False],[2,False],[3,False],[4,False],[5,False],[6,False],[7,False]]

adjacencyLst = [[[vertexes[0],vertexes[1],1],[vertexes[0],vertexes[2],1],[vertexes[0],vertexes[4],1]],
		 	    [[vertexes[1],vertexes[0],1],[vertexes[1],vertexes[2],1],[vertexes[1],vertexes[3],1],[vertexes[1],vertexes[5],1],[vertexes[1],vertexes[6],1]],
		 	    [[vertexes[2],vertexes[0],1],[vertexes[2],vertexes[1],1],[vertexes[2],vertexes[4],1],[vertexes[2],vertexes[6],1]],
		 	    [[vertexes[3],vertexes[1],1],[vertexes[3],vertexes[5],1],[vertexes[3],vertexes[7],1]],
		 	    [[vertexes[4],vertexes[0],1],[vertexes[4],vertexes[2],1],[vertexes[4],vertexes[6],1]],
		        [[vertexes[5],vertexes[1],1],[vertexes[5],vertexes[3],1],[vertexes[5],vertexes[6],1]],
		        [[vertexes[6],vertexes[1],1],[vertexes[6],vertexes[2],1],[vertexes[6],vertexes[4],1],[vertexes[6],vertexes[5],1]],
		        [[vertexes[7],vertexes[3],1]]]

que = []

que.append(vertexes[0])
vertexes[0][1] = True

while que:
	VertexPtr = que.pop()

	VertexPtr[1] = True
	print "vertexptr", VertexPtr
	tempList = adjacencyLst[VertexPtr[0]]

	for i in range(len(tempList)):
		# print tempList[i]
		tempVertex2 = tempList[i]
		print "tempvertex2",tempVertex2
		if tempVertex2[1][1] != True :
			que.append(tempVertex2[1])
			
			