class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
# @param two ListNodes
# @return the intersected ListNode
    def getIntersectionNode(self, headA, headB):
        pA = headA
        pB = headB
        while pA and pB:
            pA = pA.next
            pB = pB.next
        if pA and not pB:
            t = headA
            while pA:
                t = t.next
                pA = pA.next
            pA = t
            pB = headB
        elif not pA and pB:
            t = headB
            while pB:
                t = t.next
                pB = pB.next
            pB = t
            pA = headA
        else:
            pA = headA
            pB = headB
        while pA and pB and pA != pB:
            pA = pA.next
            pB = pB.next
        return pA
