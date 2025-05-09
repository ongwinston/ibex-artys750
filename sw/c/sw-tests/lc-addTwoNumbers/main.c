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



///////////////////////////////////////////////////////////////////////////////
// LC Solution
///////////////////////////////////////////////////////////////////////////////

struct ListNode* addTwoNumbers_LC(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode* dummyHead = malloc(sizeof(struct ListNode));
    dummyHead->val = 0;
    dummyHead->next = NULL;
    struct ListNode* curr = dummyHead;
    int carry = 0;
    while (l1 != NULL || l2 != NULL || carry != 0) {
        int x = (l1 != NULL) ? l1->val : 0;
        int y = (l2 != NULL) ? l2->val : 0;
        int sum = carry + x + y;
        carry = sum / 10;
        curr->next = malloc(sizeof(struct ListNode));
        curr->next->val = sum % 10;
        curr->next->next = NULL;
        curr = curr->next;
        if (l1 != NULL) l1 = l1->next;
        if (l2 != NULL) l2 = l2->next;
    }
    struct ListNode* result = dummyHead->next;
    free(dummyHead);  // Free the memory allocated for dummyHead
    return result;
}

///////////////////////////////////////////////////////////////////////////////
// My Solution
///////////////////////////////////////////////////////////////////////////////

struct ListNode global_list[100];
static int global_node_index = 0;

struct ListNode *iterateThroughNodes(struct ListNode* l1, struct ListNode* l2, int carry) {

    struct ListNode *newNode = &global_list[global_node_index++];
    int32_t add_rslt = 0;
    int32_t next_carry = 0;

    // Check for NULL vals
    if(l1 == NULL && l2 == NULL && carry == 1) {
        // BOTH are NULL and we have a carry, We also dont have any nodes left so return
        newNode->val = carry;
        newNode->next = NULL;
        return newNode;
    }

    if(l1 == NULL && l2 == NULL && carry == 0) {
        return NULL;
    }

    if(l1 != NULL) {
        add_rslt += l1->val;
    }

    if(l2 != NULL){
        add_rslt += l2->val;
    }

    add_rslt += carry;

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

    // // Causing fail test case 2
    // if(next_l1 == NULL && next_l2 == NULL && next_carry == 0) {
    //     return newNode;
    // }
    // Recursive call
    newNode->next = iterateThroughNodes(next_l1, next_l2, next_carry);

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

void test_case_1(void) {
    myprintf("\nTest Case 1\n");

    // Call addTwoNumbers
    struct ListNode l1_1, l1_2, l1_3;
    struct ListNode l2_1, l2_2, l2_3;

    // Add test items to l1
    l1_1.val = 2;
    l1_2.val = 4;
    l1_3.val = 3;

    l2_1.val = 5;
    l2_2.val = 6;
    l2_3.val = 4;

    l1_1.next = &l1_2;
    l1_2.next = &l1_3;
    l1_3.next = NULL;

    l2_1.next = &l2_2;
    l2_2.next = &l2_3;
    l2_3.next = NULL;

    struct ListNode *list_sum_head;
    list_sum_head  = addTwoNumbers(&l1_1, &l2_1);

    printList(list_sum_head);
    myprintf("\n");
    myprintf("Expected : 708\n");
    myprintf("End test_case_1\n");

}
void test_case_2(void) {
    myprintf("\nTest Case 2\n");

    // Call addTwoNumbers
    struct ListNode l1_1;
    struct ListNode l2_1;

    // Add test items to l1
    l1_1.val = 0;

    l2_1.val = 0;

    l1_1.next = NULL;
    l2_1.next = NULL;

    struct ListNode *list_sum_head;
    list_sum_head  = addTwoNumbers(&l1_1, &l2_1);

    printList(list_sum_head);
    myprintf("\n");
    myprintf("Expected : 0\n");
    myprintf("End test_case_2\n");

}
void test_case_3(void) {
    myprintf("\nTest Case 3\n");

    // Call addTwoNumbers
    struct ListNode l1_1, l1_2, l1_3, l1_4, l1_5, l1_6, l1_7;
    struct ListNode l2_1, l2_2, l2_3, l2_4;

    // Add test items to l1
    l1_1.val = 9;
    l1_2.val = 9;
    l1_3.val = 9;
    l1_4.val = 9;
    l1_5.val = 9;
    l1_6.val = 9;
    l1_7.val = 9;

    l2_1.val = 9;
    l2_2.val = 9;
    l2_3.val = 9;
    l2_4.val = 9;

    l1_1.next = &l1_2;
    l1_2.next = &l1_3;
    l1_3.next = &l1_4;
    l1_4.next = &l1_5;
    l1_5.next = &l1_6;
    l1_6.next = &l1_7;
    l1_7.next = NULL;
    l2_1.next = &l2_2;
    l2_2.next = &l2_3;
    l2_3.next = &l2_4;
    l2_4.next = NULL;


    struct ListNode *list_sum_head;
    list_sum_head  = addTwoNumbers(&l1_1, &l2_1);

    printList(list_sum_head);
    myprintf("\n");
    myprintf("Expected : 89990001\n");
    myprintf("End test_case_3\n");

}
void test_case_4(void) {
    myprintf("\nTest Case 4\n");

    // Call addTwoNumbers
    struct ListNode l1_1;
    struct ListNode l2_1, l2_2, l2_3, l2_4, l2_5, l2_6, l2_7, l2_8, l2_9, l2_10;

    // Add test items to l1
    l1_1.val = 9;

    l2_1.val = 1;
    l2_2.val = 9;
    l2_3.val = 9;
    l2_4.val = 9;
    l2_5.val = 9;
    l2_6.val = 9;
    l2_7.val = 9;
    l2_8.val = 9;
    l2_9.val = 9;
    l2_10.val = 9;

    l1_1.next = NULL;
    l2_1.next = &l2_2;
    l2_2.next = &l2_3;
    l2_3.next = &l2_4;
    l2_4.next = &l2_5;
    l2_5.next = &l2_6;
    l2_6.next = &l2_7;
    l2_7.next = &l2_8;
    l2_8.next = &l2_9;
    l2_9.next = &l2_10;
    l2_10.next = NULL;


    struct ListNode *list_sum_head;
    list_sum_head  = addTwoNumbers(&l1_1, &l2_1);

    printList(list_sum_head);
    myprintf("\n");
    myprintf("Expected : 00000000001\n");
    myprintf("End test_case_4\n");

}

int main(void) {
    myprintf("----\n");

    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();

    while(1) {
        asm volatile("nop");
    }

    return 0;
}