int pf[size], c[size][2], fa[size], rev[size];

void update(int x)
{
    int maxL = max[c[x][0]], maxR = max[c[x][1]];
    max[x] = x;

    if(val[maxL] > val[max[x]]) max[x] = maxL;
    if(val[maxR] > val[max[x]]) max[x] = maxR;
}
void pushdown(int x)
{
    if(rev[x])
    {
        std::swap(c[x][0], c[x][1]);
        rev[c[x][0]] ^= 1;
        rev[c[x][1]] ^= 1;
        rev[x] = 0;
    }
}
void rotate(int x)
{
    int y = fa[x], z = fa[y], i, j;

    pushdown(y), pushdown(x);
    j = (c[z][1] == y), i = (c[y][1] == x);

    if(check(z)) c[z][j] = x;
    else pf[x] = pf[y], pf[y] = 0;

    if(c[x][i ^ 1]) fa[c[x][i ^ 1]] = y;

    fa[x] = z, fa[y] = x;
    c[y][i] = c[x][i ^ 1], c[x][i ^ 1] = y;

    update(y), update(x); 
}
void Splay(int v)
{
    int g = fa[v], h = fa[g];

    pushdown(v);

    while(check(g))
    {
        if(check(h)) 
        {
            if((c[h][1] == g)^(c[g][1] == v))
                rotate(v);
            else
                rotate(g);          
        }
        rotate(v), g = fa[v], h = fa[g];    
    }

    update(v);
}
void access(int v)
{
    int u = v, e = v;
    v = 0;

    while(u)
    {
        Splay(u);

        int &t = c[u][1];

        if(check(t)) pf[t] = u, fa[t] = 0;

        if(check(v)) pf[v] = 0, fa[v] = u;

        t = v, update(u);
        v = u, u = pf[u];
    }
    Splay(e);
}
void makeroot(int v)
{
    access(v);
    rev[v] ^= 1;

}
void join(int v,int u)
{
    makeroot(v);
    pf[v] = u;
    access(v);
}
void cut(int v,int u)
{
    makeroot(v);
    access(u);
    c[u][0] = fa[v] = 0;
}
int query(int u,int v)
{
    makeroot(u);
    access(v);
    return max[v];
}
