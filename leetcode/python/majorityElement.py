class Solution:
# @param {integer[]} nums
# @return {integer}
    def majorityElement(self, nums):
        nums.sort()
        i = 0
        j = len(nums)-1
        while j > i and nums[i] != nums[j]:
            i += 1
            j -= 1
        return nums[i]
