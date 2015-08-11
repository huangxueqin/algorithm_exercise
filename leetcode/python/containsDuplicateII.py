#!/usr/bin/env python3

class Solution:
    # @param {integer[]} nums
    # @param {integer} k
    # @return {boolean}
    def containsNearbyDuplicate(self, nums, k):
        if k < 1:
            return False
        mymap = dict()
        i = 0
        for i in range(0, len(nums)):
            num = nums[i]
            if num in mymap:
                index = mymap[num]
                if i - index <= k:
                    return True
            mymap[num] = i
        return False
