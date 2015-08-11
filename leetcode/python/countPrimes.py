#!/usr/bin/env python3

class Solution:
    # @param {integer} n
    # @return {integer}
    def countPrimes(self, n):
        array = [0] * n
        i = 2
        while i < n:
            if array[i] = 0:
                j = 2
                while i*j < n:
                    array[i*j] = 1
                    j += 1
        count = 0
        for i in range(2, n):
            if array[i] == 0:
                count += 1
        return count
