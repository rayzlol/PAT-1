/**
 * 02-线性结构2 Reversing Linked List   (25分)
 * Given a constant K and a singly linked list L, you are supposed to reverse 
 * the links of every K elements on L. For example, given L being 1→2→3→4→5→6, 
 * if K = 3, then you must output 3→2→1→6→5→4; if K = 4, you must output 
 * 4→3→2→1→5→6.
 * 
 * Input Specification:
 * Each input file contains one test case. For each case, the first line 
 * contains the address of the first node, a positive N(≤10^5) which is the 
 * total number of nodes, and a positive K (≤N) which is the length of the 
 * sublist to be reversed. The address of a node is a 5-digit nonnegative 
 * integer, and NULL is represented by -1.
 * 
 * Then NN lines follow, each describes a node in the format:
 * Address Data Next
 * where Address is the position of the node, Data is an integer, and Next is 
 * the position of the next node.
 * 
 * Output Specification:
 * For each case, output the resulting ordered linked list. Each node occupies 
 * a line, and is printed in the same format as in the input.
 * 
 * Sample Input:
 * 00100 6 4
 * 00000 4 99999
 * 00100 1 12309
 * 68237 6 -1
 * 33218 3 00000
 * 99999 5 68237
 * 12309 2 33218
 * 
 * Sample Output:
 * 00000 4 33218
 * 33218 3 12309
 * 12309 2 00100
 * 00100 1 99999
 * 99999 5 68237
 * 68237 6 -1
 * 
 * 测试点
 * sample 有尾巴不反转, 地址取上下界
 * 正好全反转
 * K=N全反转
 * K=1不用反转
 * N=1 最小case
 * 最大N,最后剩K-1不反转
 * 有多余结点不在链表上
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINELEN 20
#define TOT 100000

int main()
{
    int data[TOT];
    int next[TOT];
    char line[LINELEN];
    
    fgets(line, LINELEN, stdin);
    int initadd = atoi(strtok(line, " "));
    int N = atoi(strtok(NULL, " "));
    int K = atoi(strtok(NULL, " "));
    
    int add;
    for(int i = 0; i < N; i++)
    {
        fgets(line, LINELEN, stdin);
        add = atoi(strtok(line, " "));
        data[add] = atoi(strtok(NULL, " "));
        next[add] = atoi(strtok(NULL, " "));
    }
    
    int localadd = initadd;
    int *kadd = (int*)malloc(K * sizeof(int));
    /* each K numbers */
    int flag = 0;
    while(flag == 0)
    {
        int j = 0;
        /* keep the k numbers */
        kadd[0] = localadd;
        for(j = 1; j < K; j++)
        {
            kadd[j] = next[kadd[j - 1]];
            if (kadd[1] == -1) /* N = 1 case */
            {
                flag = 1;
                j = 0;
                break;
            }
            
            if (next[kadd[j]] == -1) /* this is the last number */
            {
                flag = 1;
                break;
            }
        }
        if (K == 1 && next[kadd[0]] == -1) /* this is the last number */
        {
            flag = 1;
            j = 0;
        }
        /* print */
        if (j < K - 1) /* last round, print from 0 to j - 1 */
        {
            for(int l = 0; l <= j; l++)
            {
                if (localadd == initadd && l == 0)
                {
                    printf("%05d %d ", kadd[l], data[kadd[l]]);
                }
                else
                {
                    printf("%05d\n%05d %d ", kadd[l], kadd[l], data[kadd[l]]);
                }
            }
            break;
        }
        else /* not last round, print from K - 1 to 0 */
        {
            for(int l = K - 1; l >= 0; l--)
            {
                if (localadd == initadd && l == K - 1)
                {
                    printf("%05d %d ", kadd[l], data[kadd[l]]);
                }
                else
                {
                    printf("%05d\n%05d %d ", kadd[l], kadd[l], data[kadd[l]]);
                }
            }
            /* update */
            localadd = next[kadd[K - 1]];
        }
    }
    free(kadd);
    printf("-1");
    
    return 0;
}