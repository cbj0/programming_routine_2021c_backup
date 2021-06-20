# Special-2020级航类庆五一赛

## 比赛简介

预祝大家五一快乐！

百年创业，筚路蓝缕；一心圆梦，砥砺奋进。

心怀炽热信仰铭记历史，手写严谨代码开创未来。

庆五一赛不计入总成绩。欢迎大家练习，循序渐进，提升水平。

## A 4378
鉴于本题的特殊性，答案略。

## B 4353


## C 4377


## D 4387


## E 4404


## F 4350


## G 4406


## H 4407


## I 4331

### 解题思路

![题目分析](https://image.accoding.cn/FqfJHQk1RLBh96pVRRrHApFEtKRY)

### AC代码

```C

#include<stdio.h>
#include<math.h>

int n,l,L;

int main()
{
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d%d",&L,&l);
		if(3*l*l>=4*L*L)
		{
			puts("1.000000");
			continue;
		}
		double rad,pi=acos(-1),ans=0;
		if(l>L)
		{
			rad=asin(1.*L/l);
		}
		else
		{
			rad=pi/2;
		}
		ans+=pi/2-rad;
		ans+=(-cos(rad)+cos(pi/3))*l/L;
		ans/=(pi/6);
		printf("%.6f\n",ans);
	}
	return 0;
}

```

## J 4408


## K 4312


## L 4405


## M 4402


## N 4403

本题为一个异或博弈找规律的题目

首先所有数进行异或和，那么异或和的最高位1必然是可以攻占的“制高点”

如果对应位为1的数只有一个，那么先手只要拿下这个，就必然胜利了。

如果制高点唯一，则非制高点为奇数的时候同样能赢，偶数时反而会输（因为先手第一发拿制高点,后手就去抢次制高点 反之亦然）

唯一的平局局面，即为异或和为0的时候。

```c
#include<stdio.h>
#define maxn 200010
#define getchar getchar_unlocked
#define putchar putchar_unlocked
int rd() {
    int k = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        k = (k << 1) + (k << 3) + (c ^ 48);
        c = getchar();
    }
    return f > 0 ? k : -k;
}
int a[maxn];
int t, n, i;
int all;
int tmp;
int k;//可以攻占的制高点 (注意不一定是最高的 万一最高的有偶数个就得看次高的)
int main() {
    t = rd();
    while (t--) {
        n = rd(), all = k = 0;
        for (i = 1; i <= n; ++i) a[i] = rd(), all ^= a[i];
        tmp = 1 << 30;
        while (all < tmp) tmp >>= 1;
        for (i = 1; i <= n; ++i) if (tmp & a[i]) ++k;//制高点应该必然是奇数个才对(除非答案是0)
        if (tmp == 0) putchar('0');//异或和是0的时候一定平局
        else if (k == 1) putchar('1');//可以攻占的制高点只有1个,那么先手必赢
        else if (!((n - k) & 1)) putchar('1');//攻占制高点不一定唯一,但是奇数非制高点的时候,下位的抗衡无关紧要,关键就看这个奇数位即可
        else putchar('-'), putchar('1');//偶数非制高点,一定会输 先手第一发拿制高点,后手就去抢次制高点 反之亦然
        putchar('\n');
    }
}
//case 1 : 2 1 1
//case 2 : 5 8 8 8 8 1
//case 3 : 5 8 8 8 1 1 
//case 4 : 4 8 8 8 1
```

## O 4382
根据最后的提示，可以很方便地求解过三点的圆。一个问题是，如何在已知两圆的一个交点的情形下，求解另一个交点。

我的想法是用韦达定理：联立两圆的方程，得到一个二次方程，那么已知一个交点就是已知一个解。根据韦达定理，容易知道两解之和。求解另一个解，就是用两解之和减去一个解，就能得到另一个解。

```C

#include<stdio.h>
#include<math.h>

struct Point
{
	double x,y;
};

struct Line//cos theta x + sin theta y = d
{
	double theta,d;//法向量倾角
};

struct Circle// x^2 + y^2 + Dx + Ey + F = 0
{
	double D,E,F;
};

double det2(double a11,double a12,double a21,double a22)
{
	return a11*a22-a12*a21;
}

double det3(double a11,double a12,double a13,double a21,double a22,double a23,double a31,double a32,double a33)
{
	return a11*a22*a33+a12*a23*a31+a13*a21*a32-a13*a22*a31-a11*a23*a32-a12*a21*a33;
}

struct Line Point2(struct Point a,struct Point b)
{
	struct Line ans;
	if(fabs(a.y-b.y)<1e-12)//垂直于y轴
	{
		ans.theta=acos(-1)/2;
	}
	else//限定在-pi/2到pi/2之间
	{
		ans.theta=-atan((a.x-b.x)/(a.y-b.y));//法向量
	}
	ans.d=cos(ans.theta)*a.x+sin(ans.theta)*a.y;
	return ans;
}

struct Circle Point3(struct Point a,struct Point b,struct Point c)
{
	double temp=det3(a.x,a.y,1.0,b.x,b.y,1.0,c.x,c.y,1.0);
	struct Circle ans;
	if(temp==0)//三点共线
	{
		ans.D=ans.E=ans.F=NAN;//无法表示
		return ans;
	}
	double ra=a.x*a.x+a.y*a.y;
	double rb=b.x*b.x+b.y*b.y;
	double rc=c.x*c.x+c.y*c.y;
	ans.D=det3(-ra,a.y,1.0,-rb,b.y,1.0,-rc,c.y,1.0)/temp;
	ans.E=det3(a.x,-ra,1.0,b.x,-rb,1.0,c.x,-rc,1.0)/temp;
	ans.F=det3(a.x,a.y,-ra,b.x,b.y,-rb,c.x,c.y,-rc)/temp;
	return ans;
}

struct Point Line2(struct Line a,struct Line b)
{
	struct Point ans;
	double temp=sin(b.theta-a.theta);
	if(fabs(temp)<1e-12)//平行或重合
	{
		ans.x=ans.y=NAN;//无法表示
		return ans;
	}
	ans.x=det2(a.d,sin(a.theta),b.d,sin(b.theta))/temp;
	ans.y=det2(cos(a.theta),a.d,cos(b.theta),b.d)/temp;
	return ans;
}

struct Point Circle2(struct Circle a,struct Circle b,struct Point c)//已知一个交点求另一个
{
	struct Circle temp;//两圆相减，事实上是直线 D x + E y + F = 0
	temp.D=a.D-b.D;
	temp.E=a.E-b.E;
	temp.F=a.F-b.F;
	struct Point ans;
	if(fabs(temp.E)<1e-12)
	{
		if(fabs(temp.D)<1e-12)//同心圆
		{
			ans.x=NAN;//无法表示
			ans.y=NAN;
			return ans;
		}
		else
		{
			double cons=-temp.F/temp.D;//这时候的x值
			ans.x=cons;
			ans.y=-a.E-c.y;//韦达定理
			return ans;
		}
	}
	else
	{
		double cons1=-temp.D/temp.E;
		double cons2=-temp.F/temp.E;
		double test=1.0+cons1*cons1;
		ans.x=-(a.D+2*cons1*cons2+a.E*cons1)/test-c.x;//韦达定理
		ans.y=cons1*ans.x+cons2;
		return ans;
	}
}

int main()
{
	struct Point a,b,c,d,e;
	scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf",&a.x,&a.y,&b.x,&b.y,&c.x,&c.y,&d.x,&d.y,&e.x,&e.y);
	struct Line Line13=Point2(a,c);
	struct Line Line24=Point2(b,d);
	struct Line Line35=Point2(c,e);
	struct Line Line41=Point2(d,a);
	struct Line Line52=Point2(e,b);
	struct Point Point12=Line2(Line13,Line52);
	struct Point Point23=Line2(Line24,Line13);
	struct Point Point34=Line2(Line35,Line24);
	struct Point Point45=Line2(Line41,Line35);
	struct Point Point51=Line2(Line52,Line41);
	struct Circle Circle11=Point3(a,Point51,Point12);
	struct Circle Circle22=Point3(b,Point12,Point23);
	struct Circle Circle33=Point3(c,Point23,Point34);
	struct Circle Circle44=Point3(d,Point34,Point45);
	struct Point ans1=Circle2(Circle11,Circle22,Point12);
	struct Point ans2=Circle2(Circle22,Circle33,Point23);
	struct Point ans3=Circle2(Circle33,Circle44,Point34);
	struct Circle ans=Point3(ans1,ans2,ans3);
	if(fabs(ans.D)<1e-12)
	{
		ans.D=0.0;
	}
	if(fabs(ans.E)<1e-12)
	{
		ans.E=0.0;
	}
	if(fabs(ans.F)<1e-12)
	{
		ans.F=0.0;
	}
	printf("%.5lf %.5lf %.5lf\n",ans.D,ans.E,ans.F);
	return 0;
}

```

如果了解一些 Miquel Point 的知识，可以让求解的过程变短。当然这就用到复杂几何学的知识了，完全没有必要了解。只要知道上一个方法，能够计算就足够了。

```C

int main()
{
	struct Point a,b,c,d,e;
	scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf",&a.x,&a.y,&b.x,&b.y,&c.x,&c.y,&d.x,&d.y,&e.x,&e.y);
	struct Line Line13=Point2(a,c);
	struct Line Line24=Point2(b,d);
	struct Line Line35=Point2(c,e);
	struct Line Line41=Point2(d,a);
	struct Line Line52=Point2(e,b);
	struct Point Point12=Line2(Line13,Line52);
	struct Point Point23=Line2(Line24,Line13);
	struct Point Point34=Line2(Line35,Line24);
	struct Point Point51=Line2(Line52,Line41);
	struct Circle Circle23=Point3(a,d,Point23);
	struct Circle Circle51=Point3(d,b,Point51);
	struct Circle Circle34=Point3(b,e,Point34);
	struct Circle Circle12=Point3(e,c,Point12);
	struct Point ans1=Circle2(Circle23,Circle51,d);
	struct Point ans2=Circle2(Circle51,Circle34,b);
	struct Point ans3=Circle2(Circle34,Circle12,e);
	struct Circle ans=Point3(ans1,ans2,ans3);
	if(fabs(ans.D)<1e-12)
	{
		ans.D=0.0;
	}
	if(fabs(ans.E)<1e-12)
	{
		ans.E=0.0;
	}
	if(fabs(ans.F)<1e-12)
	{
		ans.F=0.0;
	}
	printf("%.5lf %.5lf %.5lf\n",ans.D,ans.E,ans.F);
	return 0;
}

```

## P 4339

据出题人透露，本题的灵感来源于一位《数理逻辑》老师随口提到的比赛项目计划。即读入一个数理逻辑表达式，输出它的真值表。

事实上，它实现的是一个小型编译器的功能。“源代码”就是数理逻辑表达式，“目标程序”就是真值表。

本题最好的做法，是参考Q题里的提示，把P题作为Q题的预演。这种做法用到了《数据结构》课程里面有关“栈”的知识。本门课虽然也讲了栈结构，但是浅尝辄止，对于做这道题而言是不够用的。这种Q题预演的做法相对小巧灵便。

这种做法，将真值表的每一行代入计算一遍。真值表有多少行，就现场计算多少遍。

```C

#include<stdio.h>
#include<string.h>
#include<ctype.h>

int k[130];
int len;
char s[1005];

int cal(int u)
{
	int ret=1,x=1,v=0;
	for(; u!=len; u++)
	{
		if(islower(s[u]))
		{
			if(x==1)
			{
				ret=(ret&(k[s[u]]^v));
			}
			else if(x==0)
			{
				ret=(ret|(k[s[u]]^v));
			}
			v=0;
		}
		else
		{
			int num;
			switch(s[u])
			{
				case'&':
					x=1;
					break;
				case'|':
					x=0;
					break;
				case'~':
					v^=1;
					break;
				case')':
					return ret;
				case'(':
					if(x==1)
					{
						ret=(ret&(cal(u+1)^v));
					}
					else if(x==0)
					{
						ret=(ret|(cal(u+1)^v));
					}
					v=0;
					num=1;
					while(num!=0)
					{
						u++;
						if(s[u]=='(')
						{
							num++;
						}
						else if(s[u]==')')
						{
							num--;
						}
					}
			}
		}
	}
	return ret;
}

char q[15];
int output[15];

int main()
{
	gets(s);
	len=strlen(s);
	int n=-1;
	int i;
	for(i=0; i<len; i++)
	{
		if(islower(s[i])&&k[s[i]]==0)
		{
			k[s[i]]=1;
			q[++n]=s[i];
		}
	}
	scanf("%s",s);
	len=strlen(s);
	for(i=0; i<=n; i++)
	{
		printf("| %c ",q[i]);
	}
	printf("| R |\n");
	int f;
	for(f=(1<<(n+1))-1; f>=0; f--)
	{
		for(i=0; i<=n; i++)
		{
			if((f>>(n-i))&1)
			{
				k[q[i]]=0;
				output[i]=0;
			}
			else
			{
				k[q[i]]=1;
				output[i]=1;
			}
		}
		output[n+1]=cal(0);
		for(i=0; i<=n+1; i++)
		{
			if(output[i]==0)
			{
				printf("| F ");
			}
			else
			{
				printf("| T ");
			}
		}
		printf("|\n");
	}
}

```

其他思路，就要用到《编译》课里的老套路了。无论是哪个专业，这门课都在大三。“表达式”是编译里面的一个重点研究对象，作为这门课介绍的表达式处理套路，学长学姐们自然是印象十分深刻。这种做法仅做了解即可。

这种做法，直接用一个数组模拟真值表的所有行，程序运行时，对所有行同时进行操作。

```C

#include<stdio.h>
#include<string.h>

char SYM[25];
int TOP;

struct expr
{
	char status[1030];
};

struct expr express();

struct expr parse_primary()
{
	struct expr temp;
	char next=getchar();
	int loc;
	int i;
	switch(next)
	{
		case'(':
			temp=express();
			next=getchar();
			break;
		case'~':
			temp=parse_primary();
			for(i=0; i<1026; i++)
			{
				temp.status[i]^=1;
			}
			break;
		default:
			for(i=0; i<TOP; i++)
			{
				if(SYM[i]==next)
				{
					loc=i;
					break;
				}
			}
			loc=1<<(TOP-loc-1);
			for(i=0; i<1026; i++)
			{
				temp.status[i]=((i&loc)!=0)?1:0;
			}
	}
	return temp;
}

struct expr express()
{
	struct expr lhs=parse_primary();
	char peek;
	for(peek=getchar(); peek=='&'||peek=='|'; peek=getchar())
	{
		struct expr rhs=parse_primary();
		if(peek=='&')
		{
			int i;
			for(i=0; i<1026; i++)
			{
				lhs.status[i]=lhs.status[i]&rhs.status[i];
			}
		}
		else if(peek=='|')
		{
			int i;
			for(i=0; i<1026; i++)
			{
				lhs.status[i]=lhs.status[i]|rhs.status[i];
			}
		}
	}
	ungetc(peek,stdin);
	return lhs;
}

int main()
{
	TOP=0;
	char c;
	while((c=getchar())!='\n')
	{
		if(c!=' '&&c!='\r')
		{
			SYM[TOP]=c;
			TOP++;
		}
	}
	struct expr ans=express();
	printf("|");
	int i;
	for(i=0; i<TOP; i++)
	{
		printf(" %c |",SYM[i]);
	}
	printf(" R |\n");
	int line=1<<TOP;
	for(i=0; i<line; i++)
	{
		printf("|");
		int j;
		for(j=TOP-1; j>=0; j--)
		{
			((i>>j)&1)?printf(" T |"):printf(" F |");
		}
		(ans.status[i]!=0)?printf(" T |\n"):printf(" F |\n");
	}
	return 0;
}

```

## Q 4395

这道题，来源于一位天才助教对于大作业的一些伟大设想——当然，最终相关提案无下文了，这个选题也有些偏向计算机科学，而且稍微有些抽象了。

原本天才助教想设计一下关于表达式求值、递归分析、自顶向下等背景介绍和小任务，希望设计成一个额外计分的、分模块化的lab。但是由于只能出1道题，最后选择了其中一个方向，设计一个小的表达式解析parser，并将其中一个小任务的内容的完整代码作为思路上的提示，用于降低设计难度，并使用前面已经存在的P题作为铺垫。

最后一道题目除了码量稍微大了一些之外，不见得有多难。按照题目指导思路，即“表达式栈”的思路，设计的代码如下：

```C

#include<stdio.h>
#include<string.h>
#include<ctype.h>

char str[114514];

int issub(int l,int r)
{
	int i,in=0;
	if(str[l]!='('||str[r]!=')')
	{
		return 0;
	}
	for(i=l; i<r; i++)
	{
		in+=str[i]=='(';
		in-=str[i]==')';
		if(in==0)
		{
			return 0;
		}
	}
	return 1;
}

int isfun(int l,int r)
{
	int ret=0,in=0;
	if(islower(str[l])&&str[l+1]=='('&&str[r]==')')
	{
		ret=1;
	}
	int i;
	for(i=l+1; i<r; i++)
	{
		in+=str[i]=='(';
		in-=str[i]==')';
		if(in==0)
		{
			return 0;
		}
	}
	return ret;
}

int getlst(int L,int R)
{
	int i,ret=-1;
	int in=0;
	for (i=R; i>=L; i--)
	{
		in+=str[i]=='(';
		in-=str[i]==')';
		if(in!=0)
		{
			continue;
		}
		if(str[i]=='+'||str[i]=='-')
		{
			return i;
		}
		if((str[i]=='*'||str[i]=='/')&&ret==-1)
		{
			ret=i;
		}
	}
	if(ret!=-1)
	{
		return ret;
	}
	for (i=R; i>=L; i--)
	{
		in+=str[i]=='(';
		in-=str[i]==')';
		if(in!=0)
		{
			continue;
		}
		if(str[i]=='.')
		{
			return i;
		}
	}
	return ret;
}

int q[100005];
int t;
int cnt;

int c(int L,int R)
{
	int x,y;
	if(L>R)
	{
		return 0;
	}
	if(L==R&&islower(str[L]))
	{
		return -str[L];
	}
	if(issub(L,R))
	{
		return c(L+1,R-1);
	}
	if(isfun(L,R))
	{
		int num=0,las=L+2,in=0;
		int i;
		for(i=las; i<=R-1; i++)
		{
			if(str[i]=='(')
			{
				in++;
			}
			if(str[i]==')')
			{
				in--;
			}
			if(in!=0)
			{
				continue;
			}
			if(str[i]==',')
			{
				q[++t]=c(las,i-1);
				las=i+1;
				num++;
			}
		}
		q[++t]=c(las,R-1);
		num++;
		printf("%c ",str[L]);
		for(i=t-num+1; i<=t; i++)
		{
			if(q[i]<0)
			{
				printf("%c ",-q[i]);
			}
			else
			{
				printf("%d ",q[i]);
			}
		}
		printf("\n");
		while(num--)
		{
			q[t]=0;
			t--;
		}
		return ++cnt;
	}
	int mid=getlst(L,R);
	if(str[mid]=='.')
	{
		q[++t]=c(L,mid-1);
		int num=1,las=mid+3,in=0;
		int i;
		for(i=las; i<=R-1; i++)
		{
			if(str[i]=='(')
			{
				in++;
			}
			if(str[i]==')')
			{
				in--;
			}
			if(in!=0)
			{
				continue;
			}
			if(str[i]==',')
			{
				q[++t]=c(las,i-1);
				las=i+1;
				num++;
			}
		}
		q[++t]=c(las,R-1);
		num++;
		printf("%c ",str[mid+1]);
		for(i=t-num+1; i<=t; i++)
		{
			if(q[i]<0)
			{
				printf("%c ",-q[i]);
			}
			else
			{
				printf("%d ",q[i]);
			}
		}
		printf("\n");
		while(num--)
		{
			q[t]=0;
			t--;
		}
		return ++cnt;
	}
	q[++t]=c(L,mid-1);
	q[++t]=(y=c(mid+1,R));
	printf("%c ",str[mid]);
	if(q[t-1]<0)
	{
		printf("%c ",-q[t-1]);
	}
	else
	{
		printf("%d ",q[t-1]);
	}
	if(q[t]<0)
	{
		printf("%c ",-q[t]);
	}
	else
	{
		printf("%d ",q[t]);
	}
	q[t]=0;
	t--;
	q[t]=0;
	t--;
	printf("\n");
	return ++cnt;
}

int main()
{
	scanf("%s",str+1);
	int len;
	len=strlen(str+1);
	c(1,len);
}

```

出题助教给出的自顶向下标程如下：

```C

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

char input[130];
int len;

struct parse_tree_node
{
	int dfs_time;
	char key_link;
	int child_index[130];
	int child_cnt;
};

struct parse_tree_node memory_pool[130];
int node_cnt;//在内存池中开设的节点个数
int root;//语法树根节点的下标
int dfs_cnt;//dfs序的时间戳
int time_table[130];//dfs_time memory_pool_index

void clear(struct parse_tree_node * x)
{
	int i = 0;
	for (i = 0; i < x->child_cnt; ++i)
		x->child_index[i] = 0;
	x->dfs_time = 0;
	x->key_link = '\0';
	x->child_cnt = 0;
}

void add_child(struct parse_tree_node * x, int a)
{
	x->child_index[x->child_cnt] = a;
	x->child_cnt++;
}

int is_leaf(struct parse_tree_node * x)
{
	int i = 0;
	for (i = 0; i < x->child_cnt; ++i)
		if (x->child_index[i])
			return 0;
	return 1;
}

void print(struct parse_tree_node * x)
{
	putchar(x->key_link), putchar(' ');
	for (int i = 0; i < x->child_cnt; ++i)
	{
		int ch = x->child_index[i];
		if (memory_pool[ch].dfs_time) printf("%d ", memory_pool[ch].dfs_time);
		else putchar(memory_pool[ch].key_link), putchar(' ');
	}
	putchar('\n');
}

void back_trace(int _index)//后序遍历dfs序部分
{
	for (int i = 0; i < memory_pool[_index].child_cnt; ++i)
		back_trace(memory_pool[_index].child_index[i]);
	if (!is_leaf(&memory_pool[_index]))
		memory_pool[_index].dfs_time = ++dfs_cnt, time_table[dfs_cnt] = _index;
}

void init()
{
	for (int i = 1; i <= node_cnt; ++i)
		clear(&memory_pool[i]);
	node_cnt = root = 0;
	dfs_cnt = 0;
}

int is_duplicate_bracket(int l, int r)
{
	int s[130], cnt = 0;
	memset(s, 0, sizeof(s));
	int ret = 0;
	for (int i = l; i < r; ++i)
	{
		if (input[i] == '(') s[cnt] = i, cnt++;
		if (input[i] == ')') cnt--, s[cnt] = 0;
	}
	if (cnt == 1 && s[0] == l) ret = 1;
	return ret;
}

int get_plus_or_minus(int l, int r)
{
	int in = 0;//在多少层括号内，无论正负，只有0才是真的需要的
	for (int i = r; i >= l; --i)
	{
		in += input[i] == '(';
		in -= input[i] == ')';
		if (in) continue;
		if (input[i] == '+' || input[i] == '-') return i;
	}
	return -1;
}

int get_multi_or_div(int l, int r)
{
	int in = 0;//在多少层括号内，无论正负，只有0才是真的需要的
	for (int i = r; i >= l; --i)
	{
		in += input[i] == '(';
		in -= input[i] == ')';
		if (in) continue;
		if (input[i] == '*' || input[i] == '/') return i;
	}
	return -1;
}

int get_member_func(int l, int r)
{
	int in = 0;//在多少层括号内，无论正负，只有0才是真的需要的
	for (int i = r; i >= l; --i)
	{
		in += input[i] == '(';
		in -= input[i] == ')';
		if (in) continue;
		if (input[i] == '.') return i;
	}
	return -1;
}

int is_stadard_func(int l, int r)
{
	if (r - l + 1 <= 3) return 0;
	return islower(input[l]) && input[l + 1] == '(' && input[r] == ')';
}

int* get_all_comma(int l, int r)
{
	int* ret;
	ret = (int*)malloc(sizeof(int) * 130);
	memset(ret, -1, sizeof(int) * 130);
	int cnt = 0;
	int in = 0;
	for (int i = l; i <= r; ++i)
	{
		in += input[i] == '(';
		in -= input[i] == ')';
		if (in) continue;
		if (input[i] == ',') ret[cnt] = i, cnt++;
	}
	return ret;
}

int build(int l, int r)
{
	if (l > r) return 0;
	//pre-treat : 去掉所有括号
	while (is_duplicate_bracket(l, r)) l++, r--;
	int ptn = ++node_cnt, pos = -1;
	//特判 priority 5 : 常量
	if (l == r)
	{
		memory_pool[ptn].key_link = input[l];
		return ptn;
	}
	//priority 1 : 加减符
	pos = get_plus_or_minus(l, r);
	if (pos != -1)
	{
		memory_pool[ptn].key_link = input[pos];
		add_child(&memory_pool[ptn], build(l, pos - 1));
		add_child(&memory_pool[ptn], build(pos + 1, r));
		return ptn;
	}
	//priority 2 : 乘除符
	pos = get_multi_or_div(l, r);
	if (pos != -1)
	{
		memory_pool[ptn].key_link = input[pos];
		add_child(&memory_pool[ptn], build(l, pos - 1));
		add_child(&memory_pool[ptn], build(pos + 1, r));
		return ptn;
	}
	//priority 3 : 成员函数
	pos = get_member_func(l, r);
	if (pos != -1)
	{
		memory_pool[ptn].key_link = input[pos + 1];//注意字母在'.'后面
		add_child(&memory_pool[ptn], build(l, pos - 1));
		int* commas = get_all_comma(pos + 3, r - 1);
		int commas_size = 0;
		while (commas[commas_size] >= 0)++commas_size;
		commas[commas_size] = r;
		commas_size++;

		int start = pos + 3, i = 0;
		for (i = 0; i < commas_size; ++i)
		{
			add_child(&memory_pool[ptn], build(start, commas[i] - 1));
			start = commas[i] + 1;
		}
		free(commas);
		return ptn;
	}
	//priority 4 : 普通函数
	pos = is_stadard_func(l, r);
	if (pos)
	{
		memory_pool[ptn].key_link = input[l];
		int* commas = get_all_comma(l + 2, r - 1);
		int commas_size = 0;
		while (commas[commas_size] >= 0)++commas_size;
		commas[commas_size] = r;
		commas_size++;

		int start = l + 2, i = 0;
		for (i = 0; i < commas_size; ++i)
		{
			add_child(&memory_pool[ptn], build(start, commas[i] - 1));
			start = commas[i] + 1;
		}
		free(commas);
		return ptn;
	}
	return 0;
}

int main()
{
	while (scanf("%s", input) != EOF)
	{
		init();
		len = strlen(input);
		root = build(0, len - 1);
		back_trace(root);
		int i = 0;
		for (i = 1; i <= dfs_cnt; ++i)
			print(&memory_pool[time_table[i]]);
	}
}

```

另一种自底向上的写法如下：

```C

#include<stdio.h>

int LINE;//当前行号

struct expr
{
	int valid;
	int isline;//是行号
	int value;//名字或行号
};

struct expr express();

struct expr func(char name,struct expr lhs)//传入函数名，已知的左值，默认左括号也被读了。左值仅当valid的时候才会输出
{
	struct expr mem[100];
	int top=0;
	char next=0;
	while(next!=')')//回退时并不改变next。执行函数的参数列表项 
	{
		mem[top]=express();
		top++;
		next=getchar();//右小括号或逗号
	}//结束的时候右小括号已经读过了 
	printf("%c",name);
	if(lhs.valid==1)
	{
		if(lhs.isline==1)//是行号
		{
			printf(" %d",lhs.value);
		}
		else
		{
			printf(" %c",(char)lhs.value);
		}
	}
	int i;
	for(i=0;i<top;i++)
	{
		if(mem[i].isline==1)//是行号
		{
			printf(" %d",mem[i].value);
		}
		else
		{
			printf(" %c",(char)mem[i].value);
		}
	}
	printf("\n");
	LINE++;
	struct expr temp;
	temp.valid=1;
	temp.isline=1;
	temp.value=LINE;
	return temp;
}

struct expr parse_primary()//处理常量、括号、普通函数。返回行号
{
	char next=getchar();
	if(next=='(')//左括号 
	{
		struct expr temp=express();
		next=getchar();//右括号
		return temp;//直接无脑弹出temp 
	}
	else//标识符。函数也在这部分
	{
		char temp=next;
		next=getchar();
		if(next=='(')//左括号 
		{
			struct expr nul;
			nul.valid=0;
			return func(temp,nul);
		}
		else//一个普通的标识符
		{
			ungetc(next,stdin);//退回左括号
			struct expr ans;
			ans.isline=0;
			ans.valid=1;
			ans.value=temp;
			return ans;
		}
	}
}

struct expr combine(struct expr lhs,char op,struct expr rhs)//处理加减乘除。输出语句，返回行号expr
{
	printf("%c ",op);
	if(lhs.isline==1)//是行号
	{
		printf("%d ",lhs.value);
	}
	else
	{
		printf("%c ",(char)lhs.value);
	}
	if(rhs.isline==1)//是行号
	{
		printf("%d\n",rhs.value);
	}
	else
	{
		printf("%c\n",(char)rhs.value);
	}
	LINE++;
	struct expr temp;
	temp.valid=1;
	temp.isline=1;
	temp.value=LINE;
	return temp;
}

int prec(char op)//返回指定算符的优先级
{
	if(op=='+'||op=='-')
	{
		return 1;
	}
	else if(op=='*'||op=='/')
	{
		return 2;
	}
}

int isop(char op)
{
	if(op=='+'||op=='-'||op=='*'||op=='/')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

struct expr parse_opg(struct expr lhs,int cerp)//cerp是左部优先级。每次调用这个的时候，下一个总应该是运算符。点运算应该在这里特判。所有的lhs rhs代表行号
{
	char peek=getchar();//运算符1，prec是优先级
	while(peek=='.')//是个点运算
	{
		char temp=getchar();
		getchar();//左括号
		lhs=func(temp,lhs);
		peek=getchar();//再来
	}
	while(isop(peek)&&prec(peek)>=cerp)//peek是二元运算符，peek优先级大于等于左部旧优先级就要规约
	{
		char op=peek;
		struct expr rhs=parse_primary();//右部读一个并解析某个东西3
		peek=getchar();//再预读下一个运算符2。比较1和2两个运算符的优先级
		while(peek=='.')//是个点运算
		{
			char temp=getchar();
			getchar();//左括号
			rhs=func(temp,rhs);
			peek=getchar();//再来
		}
		while(isop(peek)&&prec(peek)>prec(op))//peek是二元运算符且peek优先级大于op优先级。因为赋值只能出现一次，且优先级最低，故无需考虑右结合
		{
			ungetc(peek,stdin);//这里必须退回运算符2
			rhs=parse_opg(rhs,prec(peek));//做右边
			peek=getchar();
			while(peek=='.')//是个点运算
			{
				char temp=getchar();
				getchar();//左括号
				rhs=func(temp,rhs);
				peek=getchar();//再来
			}
		}
		lhs=combine(lhs,op,rhs);//表示规约
	}
	ungetc(peek,stdin);//这里必须退一个后面的字符
	return lhs;
}

struct expr express()
{
	struct expr lhs=parse_primary();
	struct expr ans=parse_opg(lhs,0);
	return ans;
}

int main()
{
	express();
	return 0;
}

```

