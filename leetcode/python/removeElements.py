#!/usr/bin/env python3
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    # @param {ListNode} head
    # @param {integer} val
    # @return {ListNode}
    def removeElements(self, head, val):
        if head == None:
            return None
        currNode = head
        while currNode != None and currNode.val == val:
            currNode = currNode.next
        if currNode == None:
            return None
        head = currNode
        prevNode = currNode
        currNode = currNode.next
        while currNode != None:
            if currNode.val == val:
                prevNode.next = currNode.next
                currNode = prevNode.next
            else :
                prevNode = currNode
                currNode = currNode.next
        return head
