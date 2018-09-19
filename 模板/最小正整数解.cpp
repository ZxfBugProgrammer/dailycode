int cal(int a,int b,int c)
{
	int x,y;
	int gcd=(a,b,x,y);
	if(c%gcd!=0)
		return -1;//代表无解 
	//  ax0+by0=gcd(a,b)                                方程一 
	//同时乘以c/gcd(a,b)得   
	// (a*c/gcd(a,b))*x0+(b*c/gcd(a,b))*y0=c;
	// 令 x1=c/gcd(a,b)*x0  y1=c/gcd(a,b)*y0;
	// 则可得 ax1+by1=c                                 方程二 
	// 这时得出方程的一个解   x1=x0*c/gcd(a,b)     y1=y0*c/gcd(a,b)  
	x*=c/gcd; //将 方程一的一个特解转化成方程2的一个特解 
	//套用上文的公式可得对方程二
	// b'=b/gcd(a,b);
	b/=gcd;   
	if(b<0)//处理小于0的特殊情况 
		b=-b;
	//对特解x  +- kb'  找到最小整数解
	//设x=kb'+r
	//那么我们想要求的整数解就是r
	//直接取模运算即可 
	int ans=x%b; 
	//把负数的r转化成正数的 
	if(ans<=0)
		ans+=b;
	return ans;
}
