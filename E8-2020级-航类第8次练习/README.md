# E8-2020级-航类第8次练习

## 题目列表

+ A 4364 字符串库函数测试
+ B 4236 格雷编码
+ C 4276 小迷弟搞偷袭
+ D 4423 李白打酒
+ E 4417 djj的奇怪数列
+ F 4251 补码相反数
+ G 4424 李白打酒2.0
+ H 4390 动态链表操作
+ I 4297 大美丽和大凶残
+ J 4425 蒙达鲁克硫斯伯古比奇巴勒城的名册
+ K 4401 小迷弟的灵光三现
+ L 4422 简单的函数求和

### `A` 4364 字符串库函数测试
本题主要考察字符串库函数的应用。

```C

#include<stdio.h>
#include<string.h>

char input[55];
char instr[55];

char op[55];

void handler()
{
	if(strcmp(instr,"strlen")==0)
	{
		printf("%d\n",strlen(input));
	}
	else if(strcmp(instr,"strstr")==0)
	{
		scanf("%s",op);
		char *loc=strstr(input,op);
		if(loc==NULL)
		{
			printf("NULL\n");
		}
		else
		{
			printf("%d\n",loc-input);
		}
	}
	else if(strcmp(instr,"strcpy")==0)
	{
		scanf("%s",op);
		strcpy(input,op);
	}
	else if(strcmp(instr,"strcat")==0)
	{
		scanf("%s",op);
		strcat(input,op);
	}
}

int InstrCnt;

int main()
{
	scanf("%s",input);
	scanf("%d",&InstrCnt);
	while(InstrCnt--)
	{
		scanf("%s",instr);
		handler();
	}
	printf("%s\n",input);
}

```

### `B` 4236 格雷编码


### `C` 4276 小迷弟搞偷袭


### `D` 4423 李白打酒


### `E` 4417 djj的奇怪数列


### `F` 4251 补码相反数


### `G` 4424 李白打酒2.0


### `H` 4390 动态链表操作


### `I` 4297 大美丽和大凶残
虽然这道题的题目非常长，但是事实上只需要按照题目给出的指示去做就可以了。

这里有一个巧妙的想法：用0表示无意义，1表示美丽，-1表示凶残。那么代码就长这样：

```C

#include<stdio.h>
#include<math.h>

int mod(int m,int n)
{
	if(n<0)
	{
		n=-n;
	}
	int ans=m%n;
	while(ans<0)
	{
		ans+=n;
	}
	return ans;
}

int fish(int m,int n)
{
	if(m==1||n==1)
	{
		return 1;
	}
	if(m>0&&n==-1)
	{
		return 1;
	}
	if(m<0&&n==-1)
	{
		return -1;
	}
	if(m==-1&&mod(n,4)==1)
	{
		return 1;
	}
	if(m==-1&&mod(n,4)==3)
	{
		return -1;
	}
	if(abs(m)==abs(n))
	{
		return 0;
	}
	if(abs(n)>abs(m))
	{
		if((m>0||n>0)&&(mod(n,4)==1||mod(m,4)==1))
		{
			return fish(n,m);
		}
		else if(m<0&&n<0&&mod(n,4)==3&&mod(m,4)==3)
		{
			return fish(n,m);
		}
		else
		{
			return -fish(n,m);
		}
	}
	else
	{
		int temp=mod(m,n);
		if(mod(temp,2)==0)
		{
			if(temp>0)
			{
				temp-=abs(n);
			}
			else
			{
				temp+=abs(n);
			}
		}
		if(n<0&&((temp>0&&m<0)||(temp<0&&m>0)))
		{
			return -fish(temp,n);
		}
		else
		{
			return fish(temp,n);
		}
	}
}

int main()
{
	int m,n;
	while(scanf("%d%d",&m,&n)!=EOF)
	{
		int ans=fish(m,n);
		if(ans==1)
		{
			printf("Great beauty!\n");
		}
		else if(ans==-1)
		{
			printf("Great ferocity!\n");
		}
		else
		{
			printf("Nonsense.\n");
		}
	}
}

```

### `J` 4425 蒙达鲁克硫斯伯古比奇巴勒城的名册


### `K` 4401 小迷弟的灵光三现


### `L` 4422 简单的函数求和





