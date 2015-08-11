#!/usr/bin/env python3

class Solution:
# @param {integer[]} nums
# @param {boolean}
    def containsDuplicate(self, nums):
        return len(nums) != len(set(nums))
