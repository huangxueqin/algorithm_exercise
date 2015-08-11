class Solution:
# @param {integer} n
# @return {string}
    def convertToTitle(self, n):
        s = ''
        while n > 0:
            t = n % 26
            if t == 0:
                t = 26
            s += self.int2chr(t)
            n = (n-t) / 26
        return s[::-1]

    def int2chr(self, n):
        return chr(ord('A')+n-1)
