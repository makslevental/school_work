void shortestPath::relax(DirectedEdge *e){
	int v = e->from();, w = e->to();
	if(distTo[w] > distTo[v] + e->weight()){
		distTo[w] = distTo[v] + e->weight();
		edgeTo[w] = e;
	}
}