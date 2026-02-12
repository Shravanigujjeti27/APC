/*
NAME		  : G.Shravani
DATE		  : 12 FEB 2026
DESCRIPTION   : The Arbitrary Precision Calculator (APC) is a C-based console application that performs arithmetic operations on very large integers beyond standard data type limits.
				It uses doubly linked lists to store each digit and carry out operations digit-by-digit.
			   	The calculator supports addition, subtraction, multiplication, and division, handles negative numbers.
*/
#include "apc.h"

void division(node *head_L1, node *head_OPR2, node *tail_OPR2, node **headR, node **tailR)
{
    int sub_count;
    node *head_OPR1 = NULL, *tail_OPR1 = NULL, *L1_temp = head_L1;
    node *head_SR = NULL;
    node *tail_SR = NULL;

    /* 61) 1 2 2 3 0 7 (2005
        _-_1_2_2________
           0 0 0 3 0 7
                _3_0_5__
                _0_0_2__*/
    /* L1 is used to store 1 2 2 3 0 7
       OPR 1 will store 1 at start and after comparing digits of L1 will be added.
       OPR2 will store 61*/

    insert_last(&head_OPR1, &tail_OPR1, L1_temp->data);  // 1 from L1 will be stored.

    /* OPR1 -> 1, OPR2 -> 61. Since, len1<len2 compare_list will give OPERAND2.*/
    while(compare_list(head_OPR1,head_OPR2) == OPERAND2)    // len(1)<len(61) || 12<61 || len(122)>len(61) will go to next while loop.
    {
        L1_temp = L1_temp -> next;     // now temp pointer will go to 2 of L1,then to next 2 of L1,
        if(L1_temp == NULL)
        {
            insert_last(headR,tailR,0);
            break;
        }
        insert_last(&head_OPR1,&tail_OPR1,L1_temp->data);    // OPR1 will have 1 2. OPR1 will have 1 2 2.
    }


    /* Divisor = 61
       Quotient = 2005
       Remainder = 2
       So, 122-61 = 61, 61-61 = 0. So the 1st digit of quotient is 2.
           3 of L1 already stores in the OPR1, using last five lines of the below while loop.
           0 of quotient => 0 comes down.
           0 of quotient => 7 comes down.
           307-61 = 246, 246-61 = 185, 185-61 = 124, 124-61 = 63, 63-61 = 2. This last 2 is the remainder. And 5 of quotient is five times we have subtracted 307 with 61 to get 2.*/

    while(L1_temp != NULL)      // till we complete all the digits of L1.
    {
        remove_pre_zeros(&head_OPR1);

        sub_count = 0;      // sub_count is used to put the count of no.of time we have subtracted.
        while((compare_list(head_OPR1, head_OPR2) == OPERAND1) || (compare_list(head_OPR1, head_OPR2)) == SAME)   // OPR1 = 122, OPR2 = 61, 122>61 => OPERAND2. 2nd=> OPR1 = 61, OPR2 = 61, 61==61 => SAME. 3rd => OPR1=0, OPR2 = 61, 0>61 X and 0==61 X, will not go into this loop.
            // Now OPR1 will have 3(after reaching till the end of outer loop). len(3)>len(61) X || len(3) == len(61) X. Will go to last five lines. When OPR1=30, 30>61 X || 30==61 X. When OPR1=307, len(307)>len(61) will go into the while loop. len(246)>len(61).
            // len(185)>len(61). len(124)>len(61). 63>61. len(2)>len(61) X || 2>61 X, will not enter the while loop.
        {
            subtraction(tail_OPR1, tail_OPR2, &head_SR,&tail_SR);      // 122-61 = 61, and stores in Subtraction result list. 2nd => 61-61 = 0 || When OPR1=307, 307-61=246. OPR1=246, 246-61=185. OPR1=185, 185-61=124. OPR1=124, 124-61=63. OPR1=63, 63-61=2.
            delete_list(&head_OPR1, &tail_OPR1);      // The OPR1 list is getting deleted.
            head_OPR1 = head_SR;    // Now, 61 will go to OPR1 list. We're linking SR with OPR1. 2nd => 0 will go to OPR1 list. || 246 will go to OPR1 list. 185 will go to OPR1 list. 124 will go to OPR1. 63 will go to OPR1. 2 will go to OPR1.
            tail_OPR1 = tail_SR;
            head_SR = tail_SR = NULL;   // SR list will be reused.
            remove_pre_zeros(&head_OPR1);    // The pre zeros are removed in OPR1 if any present.
            sub_count++;    // sub_count = 1. 2nd => sub_count = 2. || sub_count = 1. sub_count = 2. sub_count=3. sub_count=4. sub_count=5.
        }
        insert_last(headR, tailR, sub_count);     // the R list will store the quotient. sub_count = 2 will be stored in the R list. When, len(3)>len(61) X => sub_count=0 will go into R list. When 30>61 X => sub_count=0 will go into R list. || sub_count = 5 will go to R list.
        L1_temp = L1_temp->next;     // now the pointer will go to 3 of the L1. pointer will go to 0 of L1. pointer will go to 7 of L1. || pointer will reach to NULL.
        if(L1_temp == NULL)    // after getting 2005 pointer reaches to NULL and will break.
            break;
        insert_last(&head_OPR1, &tail_OPR1, L1_temp->data);   // 3 will go to OPR1. 0 will go to OPR1. 7 will go to OPR1.
    }
}
