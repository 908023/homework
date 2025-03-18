#include <stdlib.h>
#include <stdio.h>
#include "clist.c"

int main(void)
{
    int m,n;
    printf("请输入约瑟夫环的总人数：\n");
    scanf("%d",&m);
    if(m <= 0) // 检查输入合法性
    {
        printf("请输入正确的数字！\n");
        return 0;
    }
    printf("请输入出局者的报数：\n");
    scanf("%d",&n);
    if(n <= 0 || n >= m) // 约瑟夫环报数需满足 0 < n < m
    {
        printf("请输入正确的数字！\n");
        return 0;
    }

    pHead ph = NULL;
    ph = ClistCreate(); // 创建循环链表头节点
    if(ph == NULL)
    {
        printf("创建循环链表失败！\n");
        return 0;
    }
    
    // 逆向插入节点（优化时间复杂度为O(n)）
    for(int i = m; i > 0; i--)
        ClistInsert(ph,0,i); // 始终在头部插入，形成m到1的序列
    
    print(ph); // 打印初始链表
    printf("出局顺序：\n");
    pNode node = ph->next; // 初始指向第一个节点
    
    // 约瑟夫环处理逻辑（双向循环）
    while (node->next != node) // 当链表只剩一个节点时终止
    {
        pNode pTmp = NULL;
        // 正向移动n-1步（注意：这里实际移动次数为n-1次）
        for(int i = 1; i < n-1; i++)
            node = node->next;
        pTmp = node->next; // 定位待删除节点
    
        // 处理链表连接（若删除的是头节点则更新ph->next）
        if(pTmp == ph->next)
            ph->next = pTmp->next;
        node->next = pTmp->next;
        pTmp->next->pre = node;
        printf("%d  ", pTmp->data); // 输出出局者编号
        free(pTmp);
        ph->length--;
        node = node->next; // 移动到下一个起始点
    
        // 检查是否只剩一个节点（可能提前终止）
        if(node->next == node)
            break;
    
        // 逆向移动n-1步（双向约瑟夫环的特殊处理）
        for(int i = 1; i < n-1; i++)
            node = node->pre;
        pTmp = node->pre; // 定位反向待删除节点
    
        // 处理链表连接
        if(pTmp == ph->next)
            ph->next = pTmp->next;
        node->pre = pTmp->pre;
        pTmp->pre->next = node;
        printf("%d  ", pTmp->data); // 输出反向出局者编号
        free(pTmp);
        ph->length--;
        node = node->pre; // 移动到下一个起始点（反向）
    }
    // 确保最后一个节点自环
    node->next = node;
    node->pre = node;
    printf("\n");
    
    printf("链表中最后留下的是 ");
    print(ph); // 输出最终结果
    
    getchar(); // 防止控制台闪退（仅Windows有效）
    return 0;
}