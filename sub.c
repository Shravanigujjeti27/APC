/*
NAME		  : G.Shravani
DATE		  : 12 FEB 2026
DESCRIPTION   : The Arbitrary Precision Calculator (APC) is a C-based console application that performs arithmetic operations on very large integers beyond standard data type limits.
				It uses doubly linked lists to store each digit and carry out operations digit-by-digit.
			   	The calculator supports addition, subtraction, multiplication, and division, handles negative numbers.
*/
#include "apc.h"
//SAMPLE INPUT AND OUTPUT
/* 1 8 5 0
_____9_3_4_
_____9_1_6_
*/
void subtraction(node *tail1, node *tail2, node **headR, node **tailR)
{
    // taking one pointer each for two numbers, which will help to traverse.
    node *temp1=tail1;
    node *temp2=tail2;
    int borrow=0,result,num1,num2;
    while(temp1) //temp1 will be the bigger number, so while loop will iterate till the it reaches NULL.
    {
        // storing the value of number 1 one by one.The number is present in the list.
        num1=temp1->data; // 1st number is stored and it goes on till temp1 reaches NULL (which indicates end of the number).   0 5 8 1
        temp1=temp1->prev; // traversing to prev node. Since it's a DDL, and we subtract number starting from the last i.e., right to left so we go to prev node.
        // storing the value of number 2 one by one.The number is present in the list.
        if(temp2 !=NULL)
        {
            num2=temp2->data;   // 2nd number is stored and it goes on till temp2 reaches NULL (which indicates end of the number).    4 3 9
            temp2=temp2->prev;   // traversing to prev node. Since it's a DDL, and we subtract number starting from the last i.e., right to left so we go to prev node.
        }
        /* 1 8 5 0
          |0| 9 3 4*/
        else    // since the num2 is small so, there will be case where we need to put a zero(above |0|).
        {       // This will not occur for num1 because num1 is the bigger. And when both the numbers are same length this will occur.
            num2=0;  // 0 will add after 9 of num2(above ex).
        }
        if(borrow == 1)      // 1st time borrow=0.2nd => borrow=1. 3rd borrow=1. 4th borrow=1
        {
            num1 = num1 - 1;    // num1 = 5-1 = 4. num1 = 1-1 = 0.
            borrow = 0;    // lowering the borrow. lowering borrow
        }
        if(num1 < num2)     // 0<4 true. 4<3 X(wrong). 8<9 true. 0<0 X.
        {
            num1 = num1 + 10;   // num1=10. num1 = 8+10 = 18
            borrow = 1;     // borrow becomes 1. borrow becomes 1.
        }
        result=num1-num2;       // 10-4=6. 4-3=1. 18-9=9. 0-0 = 0
        insert_first(headR,tailR,result);   // 6 will go to result list. 1 will go. 9 will go. 0 will go, but will be removed by pre zeros fn.
    }
}