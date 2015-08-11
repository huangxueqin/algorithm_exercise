#!/usr/bin/env python3

class Solution:
    
# @param {string} s
# @return {integer}
    def lengthOfLastWord(self, s):
        if not s:
            return 0
        strs = s.split()
        if not str:
            return 0
        return len(strs[len(strs)-1])

    def lengthOfLastWord2(self, s):
        length = len(s) - 1
        result = 0
        while length >= 0 and s[length].isspace():
            length -= 1
        while length >= 0 and not s[length].isspace():
            length -= 1
            result += 1
        return result
