#include <stdio.h>

int main() {
    int level, exp, money;//定义变量
    scanf("%d %d %d", &level, &exp, &money);//输入等级、作战记录、钱 数
    int level_need = 80 - level;//距离满级所差的等级数
    int exp_need = level_need * 10; //计算升到满级需要的作战记录数
    int money_need = level_need * 1000; //计算升到满级需要的钱数
    if (exp_need <= exp && money_need <= money) { //如果两者都够，输出YES
        printf("YES %d %d", exp_need, money_need);
    } else if (exp_need <= exp && money_need > money) { //如果作战记录足够，但钱不够
        printf("NO 0 %d", money_need - money);
    } else if (exp_need > exp && money_need <= money) { //如果钱足够，但作战记录不够
        printf("NO %d 0", exp_need - exp);
    } else { //如果两者都不够
            printf("NO %d %d", exp_need - exp, money_need - money);
    }
}
