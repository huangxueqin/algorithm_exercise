class Solution:
# @param {string} s
# @param {string} s
    def titleToNumber(self, s):
        result = 0
        for c in s:
            result *= 26
            result += 1 + ord(c) - ord('A')
        return result
