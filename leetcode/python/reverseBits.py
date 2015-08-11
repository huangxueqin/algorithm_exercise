class Solution:
    # @param n, an integer
    # @return an integer
    def reverseBits(self, n):
        n = ((n >> 1) & 0x55555555) | (((n & 0x55555555) << 1) & 0xFFFFFFFF)
        n = ((n >> 2) & 0x33333333) | (((n & 0x33333333) << 2) & 0xFFFFFFFF)
        n = ((n >> 4) & 0x0F0F0F0F) | (((n & 0x0F0F0F0F) << 4) & 0xFFFFFFFF)
        n = ((n >> 8) & 0x00FF00FF) | (((n & 0x00FF00FF) << 8) & 0xFFFFFFFF)
        n = ( n >> 16             ) | (( n               << 16)& 0xFFFFFFFF)
        return n
