int cal(int a,int b,int c)
{
	int x,y;
	int gcd=(a,b,x,y);
	if(c%gcd!=0)
		return -1;//�����޽� 
	//  ax0+by0=gcd(a,b)                                ����һ 
	//ͬʱ����c/gcd(a,b)��   
	// (a*c/gcd(a,b))*x0+(b*c/gcd(a,b))*y0=c;
	// �� x1=c/gcd(a,b)*x0  y1=c/gcd(a,b)*y0;
	// ��ɵ� ax1+by1=c                                 ���̶� 
	// ��ʱ�ó����̵�һ����   x1=x0*c/gcd(a,b)     y1=y0*c/gcd(a,b)  
	x*=c/gcd; //�� ����һ��һ���ؽ�ת���ɷ���2��һ���ؽ� 
	//�������ĵĹ�ʽ�ɵöԷ��̶�
	// b'=b/gcd(a,b);
	b/=gcd;   
	if(b<0)//����С��0��������� 
		b=-b;
	//���ؽ�x  +- kb'  �ҵ���С������
	//��x=kb'+r
	//��ô������Ҫ������������r
	//ֱ��ȡģ���㼴�� 
	int ans=x%b; 
	//�Ѹ�����rת���������� 
	if(ans<=0)
		ans+=b;
	return ans;
}
