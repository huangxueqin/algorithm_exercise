class Solution:
    # @param {integer} A
    # @param {integer} B
    # @param {integer} C
    # @param {integer} D
    # @param {integer} E
    # @param {integer} F
    # @param {integer} G
    # @param {integer} H
    # @return {integer}
    def computeArea(self, A, B, C, D, E, F, G, H):
        area = (C-A)*(D-B) + (G-E)*(H-F) 
        print(area)
        oh = 0
        ow = 0
        if A < G and C > E and F < D and H > B:
            ot = D if H >= D else H
            ob = F if F >= B else B
            oh = ot - ob
            ol = A if A >= E else E
            oR = G if C >= G else C
            ow = oR - ol
        print(oh)
        print(ow)
        return area - oh*ow

sol = Solution()
print(sol.computeArea(-2, -2, 2, 2, 1, -3, 3, -1))
