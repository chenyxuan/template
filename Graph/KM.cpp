bool find(int a)
{
    visx[a] = true;

    for(int i = 1; i <= ind; i++)
    {
        if(visy[i]) continue;

        int calc = lx[a] + ly[i] - w[a][i];

        if(!calc)
        {
            visy[i] = true;

            if(!lnk[i] || find(lnk[i]))
            {
                if(!lnk[i]) add(type[i]); 

                lnk[i] = a;     
                return true;
            }
        }
        else
            slack = std::min(slack, calc);
    }   
    return false;
}
void clear()
{
    for(int i = 1; i <= tot; i++) visx[i] = false;
    for(int i = 1; i <= ind; i++) visy[i] = false;
}
void adjust()
{
    for(int i = 1; i <= tot; i++)
        if(visx[i]) lx[i] -= slack;
    for(int i = 1; i <= ind; i++) 
        if(visy[i]) ly[i] += slack;
}
int KM()
{
    int ret = 0;

    for(int i = 1; i <= tot; i++)
    {
        lx[i] = -INF;
        for(int j = 1; j <= ind; j++)
            lx[i] = std::max(lx[i], w[i][j]);
    }
// lx[i] + ly[j] >= w[i][j]  

    for(int i = 1; i <= tot; i++)
    {   
        while(true)
        {
            slack = INF;

            clear();

            if(find(i)) break;

            adjust();
        }
    }

    for(int i = 1; i <= ind; i++)
        if(lnk[i]) ret += w[lnk[i]][i];
    return -ret;    
}
