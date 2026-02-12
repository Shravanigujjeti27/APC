/*
NAME		  : G.Shravani
DATE		  : 12 FEB 2026
DESCRIPTION   : The Arbitrary Precision Calculator (APC) is a C-based console application that performs arithmetic operations on very large integers beyond standard data type limits.
				It uses doubly linked lists to store each digit and carry out operations digit-by-digit.
			   	The calculator supports addition, subtraction, multiplication, and division, handles negative numbers.
*/
#include "apc.h"

void multiplication(node *tail1, node *tail2, node **headR1, node **tailR1)
{
    node *temp1=tail1,*temp2=tail2,*headR2=NULL,*tailR2=NULL,*headAR=NULL,*tailAR=NULL;
    int count=0,carry,num1,num2,mul,res;
    // loop through each digit of second number
    while(temp2)
    {
        carry=0;                                                // reset carry
        for (int i = 0; i < count; i++)                         // add zeros based on position
            insert_first(&headR2, &tailR2, 0);
        // multiply with each digit of first number
        while(temp1)
        {
            num1=temp1->data;                                   // get digit from first number
            num2=temp2->data;                                   // get digit from second number
            mul=num1*num2+carry;                                // multiply and add carry
            res=mul%10;                                         // store last digit
            carry=mul/10;                                       // update carry
            if(count == 0)                                      // store result
                insert_first(headR1,tailR1,res);
            else
                insert_first(&headR2,&tailR2,res);
            temp1=temp1->prev;                                   // move to next digit
        }
        if(carry)                                                // insert remaining carry
        {
            if(count == 0)
                insert_first(headR1,tailR1,carry);
            else
                insert_first(&headR2,&tailR2,carry);
        }
        // add temporary result to final result
        if(count)
        {
            addition(*tailR1,tailR2,&headAR,&tailAR);             // add lists
            delete_list(headR1,tailR1);                           // clear old result
            delete_list(&headR2,&tailR2);                         // clear temporary list
            *headR1=headAR;                                       // update result
            *tailR1=tailAR;
            headAR=tailAR=NULL;                                    // reset
        }
        temp2=temp2->prev;                                         // move to next digit
        temp1=tail1;                                               // reset first number pointer
        count++;                                                   // move to next position
    }
}
