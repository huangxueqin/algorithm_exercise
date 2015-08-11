class Solution:
    # @param {integer[]} nums
    # @param {integer} k
    # @return {void} Do not return anything, modify nums in-place instead.
    def rotate(self, nums, k):
        n = len(nums)
        nums2 = nums[0:n-k]
        nums[0:k] = nums[n-k:n]
        nums[k:n] = nums2
