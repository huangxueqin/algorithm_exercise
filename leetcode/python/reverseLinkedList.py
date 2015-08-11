#!/usr/bin/env python3

#definition of single linked list
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    # @param {ListNode} head
    # @return {ListNode}
    def reverseList(self, head):
        if head == None:
            return head
        currNode = head
        nextNode = currNode.next
        head.next = None
        while nextNode != None:
            t = nextNode.next
            nextNode.next = currNode
            currNode = nextNode
            nextNode = t
        return currNode
