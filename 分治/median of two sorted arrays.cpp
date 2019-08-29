/*
https://leetcode.com/problems/median-of-two-sorted-arrays/

There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

You may assume nums1 and nums2 cannot be both empty.
*/
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
  public:
    inline int Min(int a, int b) { return a > b ? b : a; }
    inline int Max(int a, int b) { return a < b ? b : a; }
    double Median(vector<int> &A, vector<int> &B) //make sure a.size <= b.size;
    {
        int m = A.size();
        int n = B.size();
        int iMin = 0, iMax = m, halfLen = (m + n + 1) / 2;
        while (iMin <= iMax)
        {
            int i = (iMin + iMax) / 2;
            int j = halfLen - i;
            if (i < iMax && B[j - 1] > A[i])
            {
                iMin = i + 1; // i is too small
            }
            else if (i > iMin && A[i - 1] > B[j])
            {
                iMax = i - 1; // i is too big
            }
            else
            { // i is perfect
                int maxLeft = 0;
                if (i == 0)
                {
                    maxLeft = B[j - 1];
                }
                else if (j == 0)
                {
                    maxLeft = A[i - 1];
                }
                else
                {
                    maxLeft = Max(A[i - 1], B[j - 1]);
                }
                if ((m + n) % 2 == 1)
                {
                    return maxLeft;
                }

                int minRight = 0;
                if (i == m)
                {
                    minRight = B[j];
                }
                else if (j == n)
                {
                    minRight = A[i];
                }
                else
                {
                    minRight = Min(B[j], A[i]);
                }

                return (maxLeft + minRight) / 2.0;
            }
        }
        return 0.0;
    }
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        if (nums1.size() < nums2.size())
        {
            return Median(nums1, nums2);
        }
        else
        {
            return Median(nums2, nums1);
        }
    }
};