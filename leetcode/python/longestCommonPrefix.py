#!/usr/bin/env python3

class Solution:
    #@param {string[]} strs
    #@param {string}
    def longestCommonPrefix(self, strs):
        if not strs:
            return ''
        minLen = len(strs[0])
        for s in strs:
            sLen = len(s)
            if sLen < minLen:
                minLen = sLen
        result = ''
        i = 0;
        while i < minLen:
            c = strs[0][i];
            for s in strs:
                if c != s[i]:
                    return result;
            result += c
            i += 1
        return result
