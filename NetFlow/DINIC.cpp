bool BFS()
{
	static int line[maxo];
	int f = 0, r = 0;
	
	for(int i = 1; i <= T; i++) dep[i] = -1;
	
	dep[T] = 0;
	line[r++] = T;
	
	while(f != r)
	{
		int u = line[f++];
		
		for(int i = head[u]; i != -1 ; i = edge[i].next)
		{
			int v = edge[i].v;
			if(edge[i ^ 1].cap && dep[v] == -1)
			{
				dep[v] = dep[u] + 1;
				line[r++] = v;
			}
		}
	}
	return dep[S] != -1;
}
int DFS(int x,int tf)
{
	if(x == T || !tf) return tf;
	
	int res = 0;
	for(int i = cur[x]; i != -1; i = edge[i].next)
	{
		int v = edge[i].v;
		if(dep[v] + 1 == dep[x])
		{
			int ff = DFS(v, std::min(tf, edge[i].cap));
			
			res += ff;
			tf -= ff;
			edge[i].cap -= ff;
			edge[i ^ 1].cap += ff;
			
			if(!tf)
			{
				cur[x] = i;
				return res;
			}
		}
	}
	
	cur[x] = -1;
	return res;
}
int dinic()
{
	int res = 0
	while(BFS())
	{
		for(int i = 1; i <= T; i++) cur[i] = head[i];
		res += DFS(S, inf);
	}
	
	return res;
}
