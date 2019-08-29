/*
https://leetcode.com/problems/longest-substring-without-repeating-characters/

Input: "abcabcbb"
Output: 3 
Explanation: The answer is "abc", with the length of 3. 
*/
#include <iostream>
#include <string>
using namespace std;
class Solution
{
  public:
    int lengthOfLongestSubstring(string s)
    {
        int maxLen = 0;
        for (int i = 0, j = 0; i < s.size() - maxLen; i++) //假若剩余长度小于maxlen，则不需要再寻找
        {
            string tmp("");
            tmp += s[i];
            for (j = i + 1; j < s.size(); j++)
            {
                if (tmp.find(s[j]) == tmp.npos) //不重复
                {
                    tmp += s[j];
                }
                else
                {
                    break;
                }
            }
            maxLen = maxLen > (j - i) ? maxLen : (j - i);
            i += tmp.find(s[j]); //因为后续还有一个i++
        }
        return maxLen;
    }
};
int main(int argc, char const *argv[])
{
    Solution s;
    cout << s.lengthOfLongestSubstring("HelloWorld!") << endl;
    return 0;
}
