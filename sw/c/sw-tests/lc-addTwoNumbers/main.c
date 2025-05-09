// You are given two non-empty linked lists representing two non-negative integers.
// The digits are stored in reverse order, and each of their nodes contains a single digit.
// Add the two numbers and return the sum as a linked list.
// You may assume the two numbers do not contain any leading zero, except the number 0 itself.

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "myprintf.h"

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

struct ListNode global_list[100];
static int global_node_index = 0;

struct ListNode *iterateThroughNodes(struct ListNode* l1, struct ListNode* l2, int carry) {

    struct ListNode *newNode = &global_list[global_node_index++];
    int32_t add_rslt;
    int32_t next_carry = 0;

    // Check for NULL vals
    if(l1 == NULL && l2 == NULL) {
        // BOTH are NULL and we have a carry, We also dont have any nodes left so return
        newNode->val = carry;
        newNode->next = NULL;
        myprintf("%d\n",newNode->val);
        return newNode;
    } else if(l2 == NULL) {
        // l2 is null so result is l1 + carry
        add_rslt = l1->val + carry;
        // if(l1->next == NULL) no_further_nodes = true;
    } else if(l1 == NULL){
        // l1 is NULL then rslt is l2 + carry
        add_rslt = l2->val + carry;
        // if(l2->next == NULL) no_further_nodes = true;
    } else {
        // Neither are NULL
        add_rslt = l1->val + l2->val + carry;
    }

    // Check if the addition overflows
    if(add_rslt > 9) {
        // Then take the modulus of 10
        newNode->val = add_rslt % 10;
        next_carry = 1;
    } else {
        newNode->val = add_rslt;
    }

    // Check that there are items left to add
    // Determine next nodes for recursive call
    struct ListNode *next_l1 = (l1 != NULL) ? l1->next : NULL;
    struct ListNode *next_l2 = (l2 != NULL) ? l2->next : NULL;

    if(next_l1 == NULL && next_l2 == NULL && next_carry == 0) {
        return newNode;
    }
    // Recursive call
    newNode->next = iterateThroughNodes(next_l1, next_l2, next_carry);


    // if(l1->next == NULL && l2->next == NULL) {
    //     // Both lists are now empty
    //     newNode->next = NULL;
    // } else if(((l1->next == NULL) || (l1 == NULL)) && (l2 != NULL)) {
    //     // Iterate l2
    //     newNode->next = iterateThroughNodes(NULL, l2->next, next_carry);
    // }
    // else if(((l2->next == NULL) || (l2 == NULL)) && (l1 != NULL)) {
    //     // Iterate l1
    //     newNode->next = iterateThroughNodes(l1->next, NULL, next_carry);
    // } else {
    //     // Then call IterateThroughNodes with the next items
    //     newNode->next = iterateThroughNodes(l1->next, l2->next, next_carry);
    // }

    // myprintf("%d",newNode->val);
    return newNode;
}

struct ListNode *addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode *finalNode;
    finalNode = iterateThroughNodes(l1, l2, 0);
    return finalNode;
}

// Print out the final list
void printList(struct ListNode *list) {

    if(list == NULL) {
        return;
    } else {
        myprintf("%d",list->val);
        printList(list->next);
    }
}

int main(void) {
    myprintf("----\n");

    // Call addTwoNumbers
    struct ListNode l1_1,l1_2,l1_3; //,l1_4,l1_5,l1_6;
    struct ListNode l2_1,l2_2,l2_3;

    // Add test items to l1
    l1_1.val = 2;
    l1_2.val = 4;
    l1_3.val = 3;
    // l1_4.val = 9;
    // l1_5.val = 9;
    // l1_6.val = 9;

    l2_1.val = 5;
    l2_2.val = 6;
    l2_3.val = 4;

    l1_1.next = &l1_2;
    l1_2.next = &l1_3;
    l1_3.next = NULL;//&l1_4;
    // l1_4.next = &l1_5;
    // l1_5.next = &l1_6;
    // l1_6.next = NULL;

    l2_1.next = &l2_2;
    l2_2.next = &l2_3;
    l2_3.next = NULL;

    struct ListNode *list_sum_head;
    list_sum_head  = addTwoNumbers(&l1_1, &l2_1);

    myprintf("==");
    printList(list_sum_head);

    while(1) {
        asm volatile("nop");
    }

    return 0;
}


