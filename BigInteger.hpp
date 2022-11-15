#include<iostream>
#include<cstring>
#include<algorithm>
using ll=long long;
using ull=unsigned long long;
class BigInteger
{
private:
	const static int N=105,base=1e8;
	int a[N],len,neg;
	void write(int _a)const{if(_a>9)write(_a/10);putchar((_a%10)|48);}
	int getlen(int _a)const{int ans=0;while(_a)_a/=10,++ans;return ans;}
public:
	BigInteger(){len=1,neg=0,memset(a,0,sizeof(a));}
	BigInteger(char *s)
	{
		memset(a,0,sizeof(a));
		if(s[0]=='-')
		{
			int slen=strlen(s)-1;
			len=1,neg=1;
			int k=1;
			for(int i=1;i<=slen;++i)
			{
				if(k==base)++len,k=1;
				a[len]+=k*(s[slen-i+1]^48);
				k*=10;
			}
		}
		else
		{
			int slen=strlen(s);
			len=1,neg=0;
			int k=1;
			for(int i=1;i<=slen;++i)
			{
				if(k==base)++len,k=1;
				a[len]+=k*(s[slen-i]^48);
				k*=10;
			}
		}
	}
	BigInteger(std::string s)
	{
		memset(a,0,sizeof(a));
		if(s[0]=='-')
		{
			int slen=s.size()-1;
			len=1,neg=1;
			int k=1;
			for(int i=1;i<=slen;++i)
			{
				if(k==base)++len,k=1;
				a[len]+=k*(s[slen-i+1]^48);
				k*=10;
			}
		}
		else
		{
			int slen=s.size();
			len=1,neg=0;
			int k=1;
			for(int i=1;i<=slen;++i)
			{
				if(k==base)++len,k=1;
				a[len]+=k*(s[slen-i]^48);
				k*=10;
			}
		}
	}
	BigInteger(const char *s)
	{
		memset(a,0,sizeof(a));
		if(s[0]=='-')
		{
			int slen=strlen(s)-1;
			len=1,neg=1;
			int k=1;
			for(int i=1;i<=slen;++i)
			{
				if(k==base)++len,k=1;
				a[len]+=k*(s[slen-i+1]^48);
				k*=10;
			}
		}
		else
		{
			int slen=strlen(s);
			len=1,neg=0;
			int k=1;
			for(int i=1;i<=slen;++i)
			{
				if(k==base)++len,k=1;
				a[len]+=k*(s[slen-i]^48);
				k*=10;
			}
		}
	}
	template<typename _Tp>BigInteger(_Tp x)
	{
		len=0;neg=0;
		memset(a,0,sizeof(a));
		if(x<0)x=-x,neg=1;
		int tmp;
		while((tmp=x/base))
		{
			a[++len]=x%base;
			x=tmp;
		}
		a[++len]=x;
	}
	void get()
	{
		std::string s=std::string();
		char ch=getchar();
		while(ch<'0'||ch>'9')
		{
			if(ch=='-'&&!s.size())s+='-';
			ch=getchar();
		}
		while(ch>='0'&&ch<='9')s+=ch,ch=getchar();
		*this=BigInteger(s);
	}
	void print()const
	{
		int baselen=getlen(base)-1;
		if(neg)putchar('-');
		write(a[len]);
		for(int i=len-1,tmp;i;--i)
		{
			tmp=baselen-getlen(a[i]);
			while(tmp--)putchar('0');
			if(a[i])write(a[i]);
		}
	}
	std::string to_string()
	{
		std::string res="";
		int baselen=getlen(base)-1;
		if(neg)res+="-";
		std::string tmp1="";int tmp2=a[len];
		if(!a[len])return "0";
		while(tmp2)tmp1+=tmp2%10+'0',tmp2/=10;
		reverse(tmp1.begin(),tmp1.end());res+=tmp1;
		for(int i=len-1,tmp;i;--i)
		{
			tmp=baselen-getlen(a[i]);
			while(tmp--)res+="0";
			if(!a[i])continue;
			tmp1="";tmp2=a[i];
			while(tmp2)tmp1+=tmp2%10+'0',tmp2/=10;
			reverse(tmp1.begin(),tmp1.end());res+=tmp1;
		}
		return res;
	}
	friend std::istream& operator>>(std::istream& input,BigInteger& x)
	{
		x.get();
		return input;
	}
	friend std::ostream& operator<<(std::ostream& output,const BigInteger& x)
	{
		x.print();
		return output;
	}
	bool operator==(const BigInteger& x)const
	{
		if(len!=x.len||neg!=x.neg)return false;
		for(int i=1;i<=len;++i)if(a[i]!=x.a[i])return false;
		return true;
	}
	bool operator!=(const BigInteger& x)const{return !(*this==x);}
	bool operator>(const BigInteger& x)const
	{
		if(neg!=x.neg)return x.neg;
		if(len!=x.len)return len>x.len;
		for(int i=len;i;--i)if(a[i]!=x.a[i])return a[i]>x.a[i];
		return false;
	}
	bool operator<(const BigInteger& x)const
	{
		if(neg!=x.neg)return neg;
		if(len!=x.len)return len<x.len;
		for(int i=len;i;--i)if(a[i]!=x.a[i])return a[i]<x.a[i];
		return false;
	}
	bool operator>=(const BigInteger& x)const{return !(*this<x);}
	bool operator<=(const BigInteger& x)const{return !(*this>x);}
	
	
	BigInteger operator-()const{BigInteger x(*this);x.neg^=1;return x;}
	BigInteger operator+(const BigInteger& x)const
	{
		if((!neg)&&x.neg)return *this-(-x);
		if(neg&&(!x.neg))return x-(-*this);
		BigInteger ans=BigInteger();
		ans.len=std::max(len,x.len);
		for(int i=1;i<=ans.len;++i)
		{
			ans.a[i]+=a[i]+x.a[i];
			if(ans.a[i]>=base)ans.a[i]-=base,++ans.a[i+1];
		}
		if(ans.a[ans.len+1])++ans.len;
		if(neg&&x.neg)ans.neg=1;
		return ans;
	}
	BigInteger operator+=(const BigInteger& x){return *this=*this+x;}
	BigInteger operator-(const BigInteger& x)const 
	{
		if((!neg)&&x.neg)return *this+(-x);
		if(neg&&x.neg)return (-x)-(-*this);
		if(neg&&(!x.neg))return -((-*this)+x);
		BigInteger ans=BigInteger();
		if(*this==x)return ans;
		if(x>*this)
		{
			ans=(x-*this);
			ans.neg=1;
			return ans;
		}
		ans.len=std::max(len,x.len);
		for(int i=1;i<=ans.len;++i)
		{
			ans.a[i]+=a[i]-x.a[i];
			if(ans.a[i]<0)ans.a[i]+=base,--ans.a[i+1];
		}
		while(ans.len&&!ans.a[ans.len])--ans.len;
		return ans;
	}
	BigInteger operator-=(const BigInteger& x){return *this=*this-x;}
	BigInteger operator*(const BigInteger& x)const
	{
		
		BigInteger ans=BigInteger();
		if(*this==ans||x==ans)return ans;
		if(neg!=x.neg)ans.neg=1;
		ans.len=len+x.len;
		ull tmp;
		for(int i=1;i<=len;++i)
			for(int j=1;j<=x.len;++j)
			{
				tmp=1ull*a[i]*x.a[j]+ans.a[i+j-1];
				if(tmp>=base)
				{
					ans.a[i+j]+=tmp/base;
					ans.a[i+j-1]=tmp%base;
				}
				else ans.a[i+j-1]=tmp;
			}
		while(!ans.a[ans.len])--ans.len;
		return ans;
	}
	BigInteger operator*=(const BigInteger& x){return *this=*this*x;}
	BigInteger operator/(const BigInteger& X)const
	{
		if(X==0)std::cerr<<"Error:divide 0\n",exit(-1);
		BigInteger ans(*this),x(X),tmp(1),lt=BigInteger();
		if(neg!=x.neg)ans.neg=1;
		while(ans>=x) x*=2,tmp*=2;
		while(tmp.len>1||tmp.a[1])
		{
			if(ans>=x) ans-=x,lt+=tmp;
			x/=2,tmp/=2;
		}
		ans=lt;
		while(ans.len&&!ans.a[ans.len])--ans.len;
		if(!ans.len)return BigInteger();
		return ans;
	}
	BigInteger operator/=(const BigInteger& X)
	{
		if(X==0)std::cerr<<"Error:divide 0\n",exit(-1);
		BigInteger x(X),tmp(1),lt=BigInteger();
		if(neg!=x.neg)neg=1;
		else neg=0;
		while(*this>=x) x*=2,tmp*=2;
		while(tmp.len>1||tmp.a[1])
		{
			if(*this>=x) *this-=x,lt+=tmp;
			x/=2,tmp/=2;
		}
		*this=lt;
		while(len&&!a[len])--len;
		if(!len)return *this=BigInteger();
		return *this;
	}
	BigInteger operator%(const BigInteger& X)const
	{
		if(X==0)std::cerr<<"Error:mod 0\n",exit(-1);
		BigInteger ans(*this),x(X),tmp(1),lt=BigInteger();
		if(neg!=x.neg)ans.neg=1;
		while(ans>=x) x*=2,tmp*=2;
		while(tmp.len>1||tmp.a[1])
		{
			if(ans>=x) ans-=x,lt+=tmp;
			x/=2,tmp/=2;
		}
		return ans;
	}
	BigInteger operator%=(const BigInteger& X)
	{
		if(X==0)std::cerr<<"Error:mod 0\n",exit(-1);
		BigInteger x(X),tmp(1),lt=BigInteger();
		if(neg!=x.neg)neg=1;
		else neg=0;
		while(*this>=x) x*=2,tmp*=2;
		while(tmp.len>1||tmp.a[1])
		{
			if(*this>=x) *this-=x,lt+=tmp;
			x/=2,tmp/=2;
		}
		return *this;
	}
	
	template<typename _Tp>operator _Tp()const{return _Tp(a[1]);}
	template<typename _Tp>BigInteger operator+(const _Tp& x)const{return *this+BigInteger(x);}
	template<typename _Tp>BigInteger operator+=(const _Tp& x){return *this=*this+x;}
	template<typename _Tp>BigInteger operator-(const _Tp& x)const{return *this-BigInteger(x);}
	template<typename _Tp>BigInteger operator-=(const _Tp& x){return *this=*this-x;}
	template<typename _Tp>BigInteger operator*(const _Tp& x)const{return *this*BigInteger(x);}
	template<typename _Tp>BigInteger operator*=(const _Tp& x){return *this=*this*x;}
	template<typename _Tp>BigInteger operator/(const _Tp& x)const
	{
		if(x==0)std::cerr<<"Error:divide 0\n",exit(-1);
		BigInteger ans=BigInteger();
		if(len==1&&x>a[1])return ans;
		ull res=0;ans.len=len;
		if(neg!=(x<0))ans.neg=1;
		for(int i=len;i;--i)
		{
			res=res*base+a[i];
			ans.a[i]=res/x;
			res%=x;
		}
		while(ans.len>1&&!ans.a[ans.len])--ans.len;
		return ans;
	}
	template<typename _Tp>BigInteger operator/=(const _Tp& x){return *this=*this/x;}
	template<typename _Tp>BigInteger operator%(const _Tp& x)const
	{
		if(x==0)std::cerr<<"Error:mod 0\n",exit(-1);
		if(len==1&&x>a[1])return *this;
		ull res=0;
		for(int i=len;i;--i)
		{
			res=res*base+a[i];
			res%=x;
		}
		return res;
	}
	template<typename _Tp>BigInteger operator%=(const _Tp& x){return *this=*this%x;}
};
template<typename _Tp>const BigInteger operator+(const _Tp& x,const BigInteger& y){return BigInteger(x)+y;}
template<typename _Tp>const BigInteger operator-(const _Tp& x,const BigInteger& y){return BigInteger(x)-y;}
template<typename _Tp>const BigInteger operator*(const _Tp& x,const BigInteger& y){return BigInteger(x)*y;}
template<typename _Tp>const BigInteger operator/(const _Tp& x,const BigInteger& y){return BigInteger(x)/y;}
template<typename _Tp>const BigInteger operator%(const _Tp& x,const BigInteger& y){return BigInteger(x)%y;}
