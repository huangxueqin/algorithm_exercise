#include "leetc.h"

class Solution {
public:
    string numberToWords(int num) {
        if(num == 0) return "Zero";
        vector<int> digits;
        while(num > 0) {
            digits.push_back(num % 10);
            num /= 10;
        }
        string result;
        int numDigits = digits.size();
        switch(numDigits) {
            case 10:
                result = digitToString(digits[9]) + " Billion " + 
                    ((smallNumberToWords(digits, 8, 6).size() > 0) ? (smallNumberToWords(digits, 8, 6) + " Million ") : ("")) + 
                    (smallNumberToWords(digits, 5, 3).size() > 0 ? (smallNumberToWords(digits, 5, 3) + " Thousand ") : "") +
                    (smallNumberToWords(digits, 2, 0).size() > 0 ? smallNumberToWords(digits, 2, 0) : "");
                break;
            case 9:
            case 8:
            case 7:
                result = smallNumberToWords(digits, numDigits-1, 6) + " Million " + 
                    (smallNumberToWords(digits, 5, 3).size() > 0 ? (smallNumberToWords(digits, 5, 3) + " Thousand ") : "") +
                    (smallNumberToWords(digits, 2, 0).size() > 0 ? smallNumberToWords(digits, 2, 0) : "");
                break;
            case 6:
            case 5:
            case 4:
                result = smallNumberToWords(digits, numDigits-1, 3) + " Thousand " +
                    (smallNumberToWords(digits, 2, 0).size() > 0 ? smallNumberToWords(digits, 2, 0) : "");
                break;
            case 3:
            case 2:
            case 1:
                result = smallNumberToWords(digits, numDigits-1, 0);
                break;
        }
        
        while(result.size() > 0 && result[result.size()-1] == ' ') {
            result.pop_back();
        }
        return result;
    }
private:
    string smallNumberToWords(vector<int> &digits, int start, int end) {
        string result;
        while(start >= end) {
            int t = start - end;
            if(t == 0) {
                if(digits[start] != 0) {
                    result += digitToString(digits[start]);
                }
                start -= 1;
            }
            else if(t == 1) {
                if(digits[start] > 1) {
                    result += digitToString(digits[start] * 10) + " ";
                    start -= 1;
                }
                else if(digits[start] == 1) {
                    result += digitToString(digits[start] * 10 + digits[start-1]);
                    start -= 2;
                }
                else {
                    start -= 1;
                }
            }
            else if(t == 2) {
                if(digits[start] != 0) {
                    result += digitToString(digits[start]) + " Hundred ";
                }
                start -= 1;
            }
        }
        while(result.size() > 0 && result[result.size()-1] == ' ') {
            result.pop_back();
        }
        return result;
    }
    string digitToString(int i) {
        string result;
        switch(i) {
            case 0: result = "Zero"; break;
            case 1: result = "One"; break;
            case 2: result = "Two"; break;
            case 3: result = "Three"; break;
            case 4: result = "Four"; break;
            case 5: result = "Five"; break;
            case 6: result = "Six"; break;
            case 7: result = "Seven"; break;
            case 8: result = "Eight"; break;
            case 9: result = "Nine"; break;
            case 10: result = "Ten"; break;
            case 11: result = "Eleven"; break;
            case 12: result = "Twelve"; break;
            case 13: result = "Thirteen"; break;
            case 14: result = "Fourteen"; break;
            case 15: result = "Fifteen"; break;
            case 16: result = "Sixteen"; break;
            case 17: result = "Seventeen"; break;
            case 18: result = "Eighteen"; break;
            case 19: result = "Nineteen"; break;
            case 20: result = "Twenty"; break;
            case 30: result = "Thirty"; break;
            case 40: result = "Forty"; break;
            case 50: result = "Fifty"; break;
            case 60: result = "Sixty"; break;
            case 70: result = "Seventy"; break;
            case 80: result = "Eighty"; break;
            case 90: result = "Ninety"; break;
        }
        return result;
    }
};
