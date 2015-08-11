class Solution:
# @param {string} version1
# @param {string} version2
# @return {integer}
    def compareVersion(self, version1, version2):
        len1 = len(version1)
        len2 = len(version2)
        if len1 == 0 and len2 == 0:
            return 0
        dotPos1 = len1 if len1 == 0 or version1.find('.') == -1 else version1.find('.')
        dotPos2 = len2 if len2 == 0 or version2.find('.') == -1 else version2.find('.')
        mainVer1 = int(version1[0:dotPos1]) if dotPos1 > 0 else 0
        mainVer2 = int(version2[0:dotPos2]) if dotPos2 > 0 else 0
        if mainVer1 != mainVer2:
            return mainVer1 > mainVer2 and 1 or -1
        else: 
            return self.compareVersion(version1[dotPos1+1:len(version1)], version2[dotPos2+1:len(version2)])

sol = Solution()
print(sol.compareVersion('01', '1'))
