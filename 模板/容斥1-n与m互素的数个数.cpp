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
    if(n>1) p.push_back(n);///��n��������
    LL S=0;
    for(LL i=1;i<(1<<p.size());i++)///��1һֱö�ٵ�1<<�����Ӹ���
    {
        LL cnt=0;
        LL mul=1;
        for(LL j=0;j<p.size();j++)///ö��ÿ��������
        {
            if(i&(1<<j))///����Ӧλ��Ϊ1��ô����
            {
                cnt++;
                mul*=p[j];
            }
        }
        if(cnt&1)///�ݳ�ԭ��ѡȡ�ĸ���Ϊ����������
            S+=m/mul;
        else S-=m/mul;///ѡȡ�ĸ���Ϊż��������
    }
    return m-S;///S��õ���1-m����n�����ص����ĸ��������ص���1-m����n���ص����ĸ���
}

