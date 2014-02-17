import Queue

# class Vertex:
# 	def __init__(self, name, visited = False):
# 		self.name = name
# 		self.visited = visited

# 	def printState(self):
# 		print self.name, self.visited

# class Edge:
# 	def __init__(self, start, end, weight = 1):
# 		self.start = start
# 		self.end = end
# 		self.weight = weight
# 	def printState(self):
# 		print self.start, self.end, self.weight

# numbers = "zero one two three four five six seven eight nine".split()

# vertices = [Vertex(numbers[i]) for i in range(8)]
# edges = [[Edge(0,1,1),Edge(0,2,1),Edge(0,4,1)],
# 		 [Edge(1,0,1),Edge(1,2,1),Edge(1,3,1),Edge(1,5,1),Edge(1,6,1)],
# 		 [Edge(2,0,1),Edge(2,1,1),Edge(2,4,1),Edge(2,6,1)],
# 		 [Edge(3,1,1),Edge(3,5,1),Edge(3,7,1)],
# 		 [Edge(4,0,1),Edge(4,6,1)],
# 		 [Edge(5,1,1),Edge(5,3,1),Edge(5,6,1)],
# 		 [Edge(6,1,1),Edge(6,2,1),Edge(6,4,1),Edge(6,5,1)],
# 		 [Edge(7,3,1)]]

# adjacencyList = {}

# for i in range(8):
# 	adjacencyList[vertices[i]] = edges[i]

# q = Queue.Queue()

# q.put(vertices[0])
# vertices[0].visited = True

# while(not q.empty()):
# 	tempVertex = q.get()
# 	tempList = adjacencyList[tempVertex]
# 	tempVertex.printState()
# 	for i in range(len(tempList)):
# 		if(vertices[tempList[i].end].visited != True):
# 			q.put(vertices[tempList[i].end])
# 			vertices[tempList[i].end].visited = True

vertexes = [[0,False],[1,False],[2,False],[3,False],[4,False],[5,False],[6,False],[7,False]]

adjacencyLst = [[[0,1,1],[0,2,1],[0,4,1]],
		 	    [[1,0,1],[1,2,1],[1,3,1],[1,5,1],[1,6,1]],
		 	    [[2,0,1],[2,1,1],[2,4,1],[2,6,1]],
		 	    [[3,1,1],[3,5,1],[3,7,1]],
		 	    [[4,0,1],[4,6,1]],
		        [[5,1,1],[5,3,1],[5,6,1]],
		        [[6,1,1],[6,2,1],[6,4,1],[6,5,1]],
		        [[7,3,1]]]

que = Queue.Queue()

que.put(vertexes[0])
vertexes[0][1] = True

while not que.empty():
	tempVertex = que.get()
	print "tempVertex",tempVertex
	tempList = adjacencyLst[tempVertex[0]]
	for i in range(len(tempList)):
		if vertexes[tempList[i][1]][1] != True :
			que.put(vertexes[tempList[i][1]])
			vertexes[tempList[i][1]][1] = True