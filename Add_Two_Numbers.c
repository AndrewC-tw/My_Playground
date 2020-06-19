#include<stdlib.h>
#include<stdio.h>
//Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
}; 

struct ListNode* addNode(struct ListNode* ptrParent)
{
    struct ListNode* iterator = ptrParent;
    if(iterator)
    {
        while(iterator->next)
            iterator = iterator->next;
        iterator = iterator->next = calloc(sizeof(struct ListNode), 1);
    }
    else
        iterator = calloc(sizeof(struct ListNode), 1);
    return iterator;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    unsigned int carry = 0;
    int sum = 0;
    struct ListNode *ptrCurrentL1 = l1;
    struct ListNode *ptrCurrentL2 = l2;
    struct ListNode *ptrOutput = NULL;
    struct ListNode *ptrCurrentOutput = NULL;
    do{
        if(!ptrOutput)
        {
            ptrOutput = addNode(NULL);
            ptrCurrentOutput = ptrOutput;
        }
        else
            ptrCurrentOutput = addNode(ptrCurrentOutput);
        
        sum = (ptrCurrentL1? ptrCurrentL1->val: 0) + (ptrCurrentL2? ptrCurrentL2->val: 0) + carry;
        printf("sum = %d\n", sum);
        carry = ((sum > 9)? 1: 0);
        sum %= 10;
        printf("sum = %d, carry = %d\n", sum, carry);
        ptrCurrentOutput->val = sum;
        printf("ptrCurrentOutput->val = %d\n", ptrCurrentOutput->val);
        ptrCurrentL1 = (ptrCurrentL1? ptrCurrentL1->next: NULL);
        ptrCurrentL2 = (ptrCurrentL2? ptrCurrentL2->next: NULL);
    }while(ptrCurrentL1 || ptrCurrentL2 || carry);
    return ptrOutput;
}

int main()
{
    int i;
    struct ListNode *l1 = NULL;
    struct ListNode *l2 = NULL;
    struct ListNode *itrL1 = l1;
    struct ListNode *itrL2 = l2;
    for(i = 0; i < 1; i++)
    {
        if(!l1)
            itrL1 = l1 = addNode(l1);
        else
            itrL1 = addNode(l1);
        if(!l2)
            itrL2 = l2 = addNode(l2);
        else
            itrL2 = addNode(l2);
        switch(i)
        {
            case 0:
                itrL1->val = 5;
                itrL2->val = 5;
                break;
            case 1:
                itrL1->val = 4;
                itrL2->val = 6;
                break;
            case 2:
                itrL1->val = 3;
                itrL2->val = 4;
                break;
        }
    }
    addTwoNumbers(l1, l2);

}
