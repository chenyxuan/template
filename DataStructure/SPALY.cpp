// poj 3580

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cassert>

typedef long long LL;
const int maxs = 2e5 + 20;

template<class T>void checkmin(T &x,T y)
{
	if(y < x) x = y;
}
struct Node
{
	int size; //*
	Node *c[2], *fa;
	int rev; 
	
	LL val;
	LL add;
	LL min; //*
	
	void init(LL v)
	{
		val = v;
		min = v;		
		add = 0;
		
		rev = 0;
		c[0] = c[1] = NULL;
		fa = NULL;
		size = 1;
	}
	void reverse()
	{
		std::swap(c[0], c[1]);
		rev ^= 1;
	}
	void inc(LL x)
	{
		val += x;
		add += x;
		min += x;
	}
	void pushdown()
	{
		if(rev)
		{
			if(c[0]) c[0]->reverse();
			if(c[1]) c[1]->reverse();
			rev = 0;
		}
		if(add)
		{
			if(c[0]) c[0]->inc(add);
			if(c[1]) c[1]->inc(add);
			add = 0;
		}
	}
	void update()
	{
		min = val;
		if(c[0]) checkmin(min, c[0]->min);
		if(c[1]) checkmin(min, c[1]->min);
		
		size = 1;
		if(c[0]) size += c[0]->size;
		if(c[1]) size += c[1]->size;
	}

} *root;

Node* newnode(int x)
{
	static Node pool[maxs], *p = pool;
	
	(++p)->init(x);
	
	return p;
}
void setc(Node *x,int t,Node *y)
{
	x->c[t] = y;
	if(y) y->fa = x;
}
Node *find(int k)
{
	Node *now = root;
	
	while(true)
	{
		now->pushdown();
		
		int t = (now->c[0] ? now->c[0]->size : 0) + 1;
		
		if(t == k) break;
		
		if(t > k) now = now->c[0];
		else now = now->c[1], k -= t;
	}
	
	return now;
}
void rotate(Node *x,Node* &k)
{
	Node *y = x->fa, *z = y->fa;
	
	if(y != k) z->c[z->c[1] == y] = x; 
	else k = x; //z may be null
	x->fa = z;
	
	int i = (y->c[1] == x);
	
	setc(y, i, x->c[i ^ 1]);
	setc(x, i ^ 1, y);
	
	y->update();
	x->update();
}
void spaly(Node *x,Node* &k)
{
	Node *y, *z;
	
	static Node *st[maxs];
	int top = 0;
	
	y = x;
	while(y != k)
	{
		st[++top] = y;
		y = y->fa;
	}
	st[++top] = y;
	
	while(top)
	{
		st[top]->pushdown();
		top--;
	}
	
	while(x != k)
	{
		y = x->fa, z = y->fa;
		
		if(y != k)
		{
			if((y == z->c[1]) ^ (x == y->c[1])) rotate(x, k);
			else rotate(y, k);
		}
		
		rotate(x, k);
	}
}
Node *subtree(int l,int r)
{
	l++, r++;
	
	assert(l <= r);
	
	spaly(find(l - 1), root);
	spaly(find(r + 1), root->c[1]);
	
	return root->c[1]->c[0];
}
void ins(int pos,int v)
{
	pos++;
	spaly(find(pos), root);
	spaly(find(pos + 1), root->c[1]);
	setc(root->c[1], 0, newnode(v));
	root->c[1]->update();
	root->update();
}
void del(int pos)
{
	pos++;
	spaly(find(pos - 1), root);
	spaly(find(pos + 1), root->c[1]);
	root->c[1]->c[0] = NULL;
	root->c[1]->update();
	root->update();
}
void init()
{
	root = newnode(0);
	setc(root, 1, newnode(0));
	root->update();
}
int main()
{
	int n, m;
	
	init();
	
	scanf("%d", &n);
	for(int i = 1, x; i <= n; i++)
	{
		scanf("%d", &x);
		ins(i - 1, x);
	}
	
	scanf("%d", &m);
	while(m--)
	{
		char ch[10];
		scanf("%s", ch);
		int x, y, z;
		
		scanf("%d", &x);
			
		if(ch[0] == 'D') del(x);
		else
		{
			scanf("%d", &y);
			
			if(ch[0] == 'R')
			{
				if(ch[3] == 'E') subtree(x, y)->reverse();
				else if(ch[3] == 'O')
				{
					scanf("%d", &z);
					
					int len = y - x + 1;
					
					z = (z % len + len) % len;
					
					if(z)
					{
						subtree(x, y - z)->reverse();
						subtree(y - z + 1, y)->reverse();
						subtree(x, y)->reverse();
					}
				}
				else assert(false);
			}
			else if(ch[0] == 'I') ins(x, y);
			else if(ch[0] == 'M') printf("%d\n", (int)(subtree(x, y)->min));
			else
			{
				scanf("%d", &z);
			
				if(ch[0] == 'A') subtree(x, y)->inc(z);
				else assert(false);
			}
		}
	}
	return 0;
}
