// You are given two non-empty linked lists representing two non-negative integers.
// The digits are stored in reverse order, and each of their nodes contains a single digit.
// Add the two numbers and return the sum as a linked list.
// You may assume the two numbers do not contain any leading zero, except the number 0 itself.

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "myprintf.h"
#include "dev_access.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *iterateThroughNodes(struct ListNode* l1, struct ListNode* l2, int carry) {
    
    // Track number of times we have entered iteratethroughNodes
    // DEV_WRITE(0x80003000,0x0bad);
    // myprintf("*");

    struct ListNode newNode;
    int32_t add_rslt;
    int32_t next_carry = 0;
    bool no_further_nodes = false;

    // Check for NULL vals
    if(l1 == NULL && l2 == NULL) {
        // BOTH are NULL and we have a carry
        // We also dont have any nodes left so return
        newNode.val = carry;
        newNode.next = NULL;
        // myprintf("%d\n", newNode.val);
        return &newNode;
    } else if(l2 == NULL) {
        // l2 is null so result is l1 + carry
        // myprintf("@ l1.val = %d\n", l1->val);
        add_rslt = l1->val + carry;
        // if(l1->next == NULL) no_further_nodes = true;
    } else if(l1 == NULL){
        // l1 is NULL then rslt is l2 + carry
        // myprintf("# l2.val = %d\n", l2->val);
        add_rslt = l2->val + carry;
        // if(l2->next == NULL) no_further_nodes = true;
    } else {
        // Neither are NULL
        // myprintf("List1.val = %d, List2.val = %d\n", l1->val, l2->val);
        add_rslt = l1->val + l2->val + carry;
    }

    // myprintf("add_rslt = %d\n", add_rslt);

    // Check if the addition overflows
    if(add_rslt > 9) {
        // Then take the modulus of 10
        newNode.val = add_rslt % 10;
        next_carry = 1;
    } else {
        newNode.val = add_rslt;
    }

    // myprintf("newNode val = %d\n", newNode.val);
    // myprintf("next_carry = %d\n", next_carry);

    if(!no_further_nodes) {
        // Check that there are items left to add
        if(l1->next == NULL && l2->next == NULL) {
            // Both lists are now empty
            newNode.next = NULL;
        } else if(((l1->next == NULL) || (l1 == NULL)) && (l2 != NULL)) {
            // Iterate l2
            // myprintf("%%\n");
            newNode.next = iterateThroughNodes(NULL, l2->next, next_carry);
        }
        else if(((l2->next == NULL) || (l2 == NULL)) && (l1 != NULL)) {
            // Iterate l1
            // myprintf("$\n");
            newNode.next = iterateThroughNodes(l1->next, NULL, next_carry);
        } else {
            // myprintf("^\n");
            // Then call IterateThroughNodes with the next items
            newNode.next = iterateThroughNodes(l1->next, l2->next, next_carry);
        }
    }

    // myprintf("%d\n", newNode.val);
    return &newNode;
}


// Print out the final list
void printList(struct ListNode *list) {

    if(list == NULL) {
        myprintf("()\n");
        return;
    } else {
        myprintf("%d",list->val);
        printList(list->next);
    }
}

struct ListNode *addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode *finalNode;
    finalNode = iterateThroughNodes(l1, l2, 0);
    return finalNode;
}

int main(void) {
    myprintf("----\n");

    // Call addTwoNumbers
    struct ListNode l1_1,l1_2,l1_3,l1_4,l1_5,l1_6;
    struct ListNode l2_1,l2_2,l2_3;

    // Add test items to l1
    l1_1.val = 9;
    l1_2.val = 9;
    l1_3.val = 9;
    l1_4.val = 9;
    l1_5.val = 9;
    l1_6.val = 9;

    l2_1.val = 9;
    l2_2.val = 9;
    l2_3.val = 9;

    l1_1.next = &l1_2;
    l1_2.next = &l1_3;
    l1_3.next = &l1_4;
    l1_4.next = &l1_5;
    l1_5.next = &l1_6;
    l1_6.next = NULL;

    l2_1.next = &l2_2;
    l2_2.next = &l2_3;
    l2_3.next = NULL;

    // myprintf("print l1\n");
    // printList(&l11);

    // myprintf("print l2\n");
    // printList(&l21);


    struct ListNode *ret_num = addTwoNumbers(&l1_1, &l2_1);
    // printList(ret_num);
    // myprintf("main scope %d\n", ret_num->val);
    // myprintf("EXIT\n");
    // myprintf("%d\n",ret_num->val);
    while(1) {
        asm volatile("nop");
    }

    return 0;
}


