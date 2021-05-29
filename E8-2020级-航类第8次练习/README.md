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

#### 题目分析

本题考点是数组和简单模拟，酒壶最多有 $5\times 10^4+1$ 个，因此用数组 $wine[50005]$ 记录每个酒壶的**剩余酒量**，根据每一天的不同情况修改数组对应元素的值即可。本题核心在于找**数组中的最大最小值**，由于题目数据保证 $O(n^2)$ 可以通过，因此直接循环查找即可。

若每次都对酒壶调用 $qsort$ 排序，那么程序总的时间复杂度是 $O(n^2logn)$ ，是会超时的；并且采用循环查找方法时，若每次都循环查找 $5\times 10^4$ 个元素也同样会超时，因此程序中用变量 $havePot$ 来记录**当前一共有多少个酒壶**，初始为 $1$ ，这样**每次查找只需要查找 $havePot$ 次**；需要注意的是，在遇友人时并不需要查找最大最小值，还有其他一些不必要的运算尽量减少，才能保证不 $TLE$ 。

其次还要考虑数据范围，对最后酒的总量作估计，**可能会超过** `int` ，但不超过 `long long` ，因此定义 $haveWine$ 为 `long long` 类型；另外由于数组 $wine$ 是 `int` 类型，则 $2\times wine[index]$ **有可能溢出** `int` ，因此 `if` 语句中写作 $v-wine[index]>wine[index]$ ，保证了数据不会溢出。

本题出错率很高，大多数同学出错在查找最大最小值这一环节上。建议同学们编写代码时条理清晰，清楚每一步的作用，考试时亦是如此，才不容易出错。

#### 示例代码

```c
#include <stdio.h>
#define INT_MAX 0x7FFFFFFF

int wine[50005];
int maxIndex(int n);    // 返回所有酒壶中最大值的下标
int minIndex(int n);    // 返回所有酒壶中最小值的下标


int main() {
    int v, n, i, op, havePot = 1, index;
    scanf("%d%d", &v, &n);
    long long haveWine = v;
    wine[0] = v;    // 初始第一壶酒有 v 斗

    for (i = 1; i <= n; i++) {      // 每一天
        scanf("%d", &op);
        if (op == 3) {      // 遇友人
            haveWine += v;
            wine[havePot++] = v;			// 将数组对应元素置为v，同时酒壶数+1
        } else if (op == 1) {       // 遇店
            index = minIndex(havePot);
            if (index != -1) {      // 表示并非所有酒壶都是空的
                if (v - wine[index] > wine[index]) {    // 最大可加量>剩余量，表示还能加一倍量
                    haveWine += wine[index];
                    wine[index] <<= 1;
                } else {
                    haveWine += v - wine[index];
                    wine[index] = v;
                }
            }
        } else if (op == 2) {       // 遇花
            index = maxIndex(havePot);
            if (index == -1) {      // 表示所有酒壶都是空的
                printf("Day %d: Such beautiful flowers, what a pity!\n", i);
                continue;
            }
            haveWine--;
            wine[index]--;
        }
        printf("Day %d: %lld\n", i, haveWine);
    }
    
    return 0;
}
int maxIndex(int n) {
    int ret = -1, i, max = 0;   // 最大值初始设为0
    for (i = 0; i < n; i++) {
        if (wine[i] > max) {
            max = wine[i];      // 更新最大值
            ret = i;            // 更新返回的下标值
        }
    }
    return ret;
}
int minIndex(int n) {
    int ret = -1, i, min = INT_MAX;   // 最小值初始设为int的最大值
    for (i = 0; i < n; i++) {
        if (wine[i] < min && wine[i] != 0) {     // 找最小值时空壶不纳入
            min = wine[i];
            ret = i;
        }
    }
    return ret;
}
```

### `E` 4417 djj的奇怪数列


### `F` 4251 补码相反数


### `G` 4424 李白打酒2.0

#### 题目分析

题目数据范围不大，我们可以尝试递归求解。递归函数需要三个参数，分别表示**剩下多少店**，**剩下多少花**，和当前**手中剩余的酒量**，对于每一次奇遇都有两种选择，即**遇店和遇花**，只须递归地调用 $travel$ 函数即可。

当剩余店铺数为 $0$ ，且恰好剩余 $1$ 次花和 $1$ 斗酒时，即为一个符合条件的次序，此时令 $cnt+1$ 后返回；如果在选择过程出了错，即 $dian<0\ ||\ hua\leq 0\ ||\ jiu\leq 0$ 时，直接 $return$ 回到上一层。  

#### 示例代码

```c
#include <stdio.h>

long long cnt;
int n, m, v;
int min(int a, int b) {
    return a < b ? a : b;
}
void travel(int dian, int hua, int jiu) {
    if (dian < 0 || hua <= 0 || jiu <= 0)
        return;
    if (dian == 0 && hua == 1 && jiu == 1) {
        cnt++;
        return;
    }
    
    // 遇到店
    travel(dian - 1, hua, min(2 * jiu, v));
    
    // 遇到花
    travel(dian, hua - 1, jiu - 1);
}

int main() {
    scanf("%d%d%d", &n, &m, &v);
    travel(n, m, v);
    printf("%lld\n", cnt);
    return 0;
}
```

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





