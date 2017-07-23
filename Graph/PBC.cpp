#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cassert>

const int maxn = 2e4 + 10, maxm = 2e5 + 20;

struct Edge
{
	int v, next;
	
} edge[maxm];

int head[maxn], sz;

int n, m;
int dfn[maxn], low[maxn], df;
int pbc[maxm];
int stack[maxm], top;
int ind[maxn], tot;

void newedge(int u,int v)
{
	edge[++sz] = (Edge){v, head[u]};
	head[u] = sz;
}
void tarjan(int u,int f)
{
	low[u] = dfn[u] = ++df;
	
	for(int i = head[u]; i ; i = edge[i].next)
	{
		int v = edge[i].v;
		
		if(v == f) continue;
		
		if(!dfn[v])
		{
			stack[++top] = i;
			tarjan(v, u);
			low[u] = std::min(low[u], low[v]);
			
			if(low[v] >= dfn[u])
			{
				++tot;
				ind[tot] = i;
				
				while(stack[top] != i)
				{
					ind[tot] = std::min(ind[tot], stack[top]);
					pbc[stack[top--]] = tot;
				}
				
				pbc[stack[top--]] = tot;
			}
		}
		else if(dfn[v] < dfn[u])
		{
			stack[++top] = i;
			low[u] = std::min(low[u], dfn[v]);
		}
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1, x, y; i <= m; i++)
	{
		scanf("%d%d", &x, &y);
		newedge(x, y);
		newedge(y, x);
	}
	
	tarjan(1, 0);
	
	printf("%d\n", tot);
	for(int i = 1; i <= m; i++)
	{
		int now = std::max(pbc[i * 2 - 1], pbc[i * 2]);
		
		assert(now);
		printf("%d ", now ? (ind[now] + 1) / 2 : i);
	}
	
	return 0;
}
