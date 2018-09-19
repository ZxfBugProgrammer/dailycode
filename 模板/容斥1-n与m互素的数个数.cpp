vector<LL> p;
LL fun(LL n,LL m)
{
    p.clear();
    for(LL i=2;i*i<=n;i++)
    {
        if(n%i==0)
        {
            p.push_back(i);
            while(n%i==0)
                n/=i;
        }
    }
    if(n>1) p.push_back(n);///求n的素因子
    LL S=0;
    for(LL i=1;i<(1<<p.size());i++)///从1一直枚举到1<<素因子个数
    {
        LL cnt=0;
        LL mul=1;
        for(LL j=0;j<p.size();j++)///枚举每个素因子
        {
            if(i&(1<<j))///若对应位置为1那么计入
            {
                cnt++;
                mul*=p[j];
            }
        }
        if(cnt&1)///容斥原理，选取的个数为奇数个，加
            S+=m/mul;
        else S-=m/mul;///选取的个数为偶数个，减
    }
    return m-S;///S求得的是1-m中与n不互素的数的个数，返回的是1-m中与n互素的数的个数
}

