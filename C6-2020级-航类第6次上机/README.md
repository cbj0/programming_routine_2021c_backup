# C6-2020级-航类第六次上机

## 比赛简介
这是 C语言程序设计 的第6次上机，你可能需要以下知识才能较为轻松地完成本次的所有题目：
- 快速排序
- 结构体
- 链表
- 字符串
- 指针
本次上机 8 题，做出 3 题你就非常优秀了。以后要习惯挫折，每次上机不太可能在短时间内做出所有题！

再次重申，题目难度与题目的排布顺序并不完全相关！请根据题目通过率等信息进行难度判断，掌控好自己的做题节奏！

## 题目列表

- A 4391 统计成绩（套娃版）
- B 4392 出人意料的送分
- C 4381 五月加急名单
- D 4388 合成单向链表
- E 4282 吃糖
- F 4386 另类合成
- G 4383 String.ReplaceAll()
- H 4385 合成宝石


### A 4391 统计成绩（套娃版）



### B 4392 出人意料的送分
一道很基础的快排模板题，没有坑点。

```c
#include<stdio.h>
#include<stdlib.h>

int n;
int a[200005];

int cmp(const void *a, const void *b){
    int *c=(int*)a, *d=(int*)b;
    return *c - *d;
}

int main(){
    int i;
    
    scanf("%d", &n);
    for(i=1; i<=n; ++i)
        scanf("%d", &a[i]);
    
    qsort(a+1, n, sizeof(a[1]), cmp);
    
    for(i=1; i<=n; ++i)
        printf("%d ", a[i]);
    return 0;
}
```

### C 4381 五月加急名单


### D 4388 合成单向链表


### E 4282 吃糖

我们规定从左往右是第$1、2、3……n$堆，用数组$a_i$记录第$i$堆糖的数量，用变量$Ans$记录所需要吃的糖果数。

对于第$1、2$堆糖：如果它们之和小于等于$m$，那我们就不用管，继续看第$2、3$堆糖；如果大于$m$，设$a_1+a_2$比$m$多$x$，那么我们将$Ans$加$x$，如果$x$比$a_2$小，我们把第二堆的糖果吃掉$x$个，如果$x$比$a_2$大，那就把第二堆吃完，把第一堆的糖果吃到$m$个，之后处理第$2、3$堆糖。

对于第$2、3$堆糖，如果它们之和小于等于$m$，我们同样不用处理，继续看第$3、4$堆糖；如果大于$m$，设$a_2+a_3$比$m$多$x$，那么我们将$Ans$加$x$，把第二堆糖吃掉$x$个，然后处理第$3、4$堆糖。（不可能会有$x>a_2$的情况发生，想一想为什么）

对于之后的相邻两堆都重复对第$2、3$堆的操作即可，最后的$Ans$就是最少的糖果数。

正确性可以用数学归纳法证明，这里不赘述辽。

#### 示例代码
```c
#include<stdio.h>

int n, m, Ans;
int a[100005];

int main(){
    int i;
    scanf("%d%d", &n, &m);
    for(i=1; i<=n; ++i)
        scanf("%d", &a[i]);
    
    if(a[1]+a[2] > m){
        Ans += a[1]+a[2]-m;
        if(a[1]+a[2]-m > a[2]){ 
            a[2] = 0;
            a[1] = m;
        }
        else    a[2] = m-a[1];
    }
    for(i=2; i<n; ++i){
        if(a[i]+a[i+1] <= m)    continue;
        Ans += a[i]+a[i+1]-m;
        a[i+1] = m-a[i];
    }
    printf("%d", Ans);
    return 0;
}
```

### F 4386 另类合成



### G 4383 String.ReplaceAll()

#### 题目分析

本题考查指针和`strstr`库函数的使用。推荐新建一个数组，存放新的字符串。遇到子串就放进新的字符串就OK了。

实际上，本题根本无需替换原字符串，遇到要替换的字符串直接输出就OK了。

#### 示例代码

```c
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 此函数用来去除字符串结尾的\r
int TrimEndR(char *base);

char str[3015], old[30], new[30], newstr[3015];
char laji[5];
int main()
{
    int n;
    scanf("%d", &n), gets(laji); // scanf之后记得gets
    for (int i = 0; i < n; i++)
    {
        gets(str), gets(old), gets(new);
        TrimEndR(str), TrimEndR(old), TrimEndR(new);
        int strL = strlen(str), oldL = strlen(old), newL = strlen(new), cnt = 0;
        for (char *p = str; p < str + strL; p += oldL) // 每次找到旧串后将p跳过旧串的长度。
        {
            char *n = strstr(p, old);
            if (n == NULL)
            {
                for (; p < str + strL; p++, cnt++)
                    newstr[cnt] = *p;
                break;
            }
            for (; p < n; p++, cnt++)
                newstr[cnt] = *p;
            for (int i = 0; i < newL; i++, cnt++)
                newstr[cnt] = new[i];
        }
        newstr[cnt] = '\0';
        puts(newstr);
    }
}

int TrimEndR(char *base)
{
    while (base[strlen(base) - 1] == '\r')
        base[strlen(base) - 1] = '\0';
    return strlen(base);
}
```

### H 4385 合成宝石

#### 题目分析
这道题可以看成是一道简单的“高精度算法”，可以将1级到9级宝石分别看成这个三进制九位数的个位、十位、百位...
进位过程就是:高位+=低位/3
判断依据就是：将数字从个位进到第$q$位，第$q$位是0就说明合成不了，非0就说明可以合成。

#### 示例代码
```c
#include<stdio.h>

int bag[2][10]={0};

int main()
{
    int n,m;
    int a,b;
    int p,q;
    int c=0,i;
    scanf("%d %d",&n,&m);
    
    while(n--)
    {
        scanf("%d %d",&a,&b);
        bag[a][b]++;
    }
    while(m--)
    {
        scanf("%d %d",&p,&q);
        c=0;
        for(i=1;i<=q;++i)
        {
            c/=3;
            c+=bag[p][i];
        }
        
        if(c){
            printf("%%\n");
        }else{
            printf("\"\'\n");
        }
        
    }
}
```

