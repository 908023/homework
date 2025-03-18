#include "clist.h"
#include <stdlib.h>
#include <stdio.h>

// 创建循环链表头节点（不含数据域）
pHead ClistCreate()
{
    pHead ph = (pHead)malloc(sizeof(struct Head));
    if (ph == NULL)
        printf("分配头结点失败！");
    ph->length = 0; // 初始化长度
    ph->next = NULL; // 初始无数据节点
    return ph;
}

// 在pos位置插入元素val（0表示头节点后）
int ClistInsert(pHead ph, int pos, int val)
{
    if (ph == NULL || pos < 0 || pos > ph->length)
        printf("插入元素时，参数传入有误！\n");
    
    pNode pval = (pNode)malloc(sizeof(struct Node));
    pval->data = val;
    
    if(IsEmpty(ph)) // 空链表处理
    {
        ph->next = pval;
        pval->next = pval; // 自环
        pval->pre = pval;
    }
    else
    {
        pNode pRead = ph->next;
        if(pos==0) // 头插法
        {
            pval->pre = ph->next->pre;  // 新节点的前驱是原头节点的前驱
            pval->next = ph->next;      // 新节点的后继是原头节点
            ph->next->pre->next = pval; // 原头节点前驱的后继指向新节点
            ph->next->pre = pval;       // 原头节点的前驱更新为新节点
            ph->next = pval;            // 更新链表头指针
        }
        else // 中间或尾部插入
        {
            pNode pCur = ph->next;
            if(pos<(int)(ph->length/2)) // 前半部分正向遍历
            {
                for(int i = 1; i < pos; i++)
                    pCur = pCur->next;
                pval->next = pCur->next;
                pval->pre = pCur;
                pCur->next->pre = pval; // 修改后继节点的前驱
            }
            else // 后半部分逆向遍历优化
            {
                for(int i = ph->length; i == pos; i--) // 从尾部向前定位
                    pCur = pCur->pre;
                pval->next = pCur;
                pval->pre = pCur->pre;
                pCur->pre->next = pval; // 修改前驱节点的后继
                pCur->pre = pval;
            }
        }
    }
    ph->length++;
    return 1;
}

// 打印链表所有元素（从头节点开始）
void print(pHead ph)
{
    if(ph == NULL || ph->length == 0)
        printf("参数传入有误！");
    
    pNode pTmp = ph->next; // 从头节点开始遍历

    for(int i = 0; i < ph->length; i++)
    {
        printf("%d ", pTmp->data);
        pTmp = pTmp->next; // 循环移动
    }
    printf("\n");
}

// 判断链表是否为空（仅通过长度判断）
int IsEmpty(pHead ph)
{
    if (ph == NULL)
        printf("传入的双链表有误！");

    if(ph->length == 0)
        return 1;
    else
        return 0;
}