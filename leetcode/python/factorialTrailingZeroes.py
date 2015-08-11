class Solution:
    # @param {integer} n
    # @return {integer}
    def trailingZeroes(self, n):
        if n < 5:
            return 0
        count = []
        t = 1
        while t * 5 <= n:
            t *= 5
            count.append(n / t)
        length = len(count)
        result = count[0]
        for i in range(1, length):
                result += count[i]
        return result
