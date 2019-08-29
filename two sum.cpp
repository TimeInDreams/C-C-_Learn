/*
https://leetcode.com/problems/two-sum/
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

[-3,4,3,9]
0
[0,2]

[3,3]
6
[0,1]

*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
  public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        int INF = 0x3fffffff;
        vector<int> result;
        vector<int> tmp = nums;
        //O(nlogn)
        sort(nums.begin(), nums.end());
        int r = nums.size() - 1;
        int l = 0;
        //O(n)
        while (r > l)
        {
            if (nums[r] + nums[l] == target)
                break;
            if (nums[r] + nums[l] < target)
                l++;
            else
                r--;
        }
        //O(n)
        for(int i = 0; i < tmp.size() && result.size() < 2; i++)
        {
            if(nums[r] == tmp[i])
            {
                result.push_back(i);
                nums[r] = INF;//防止重复
                continue;
            }
            if(nums[l] == tmp[i])
            {
                result.push_back(i);
                nums[l] = INF;
                continue;
            }
        }
        
        return result;
    }
};

int main()
{
    Solution s;
    vector<int> v;
    v.push_back(-3);
    v.push_back(3);
    v.push_back(4);
    v.push_back(90);
    vector<int> result = s.twoSum(v, 0);
    cout << result[0] << " " << result[1] << endl;
    return 0;
}
