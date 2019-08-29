/*
Have you ever played quoit in a playground? Quoit is a game 
in which flat rings are pitched at some toys, 
with all the toys encircled awarded. 
In the field of Cyberground, the position of each toy is fixed,
 and the ring is carefully designed so it can only encircle one toy at a time. 
 On the other hand, to make the game look more attractive, 
 the ring is designed to have the largest radius. 
 Given a configuration of the field, you are supposed to find the radius of such a ring. 
 Assume that all the toys are points on a plane. 
 A point is encircled by the ring if the distance between the point and the center of the ring 
 is strictly less than the radius of the ring. If two toys are placed at the same point, 
 the radius of the ring is considered to be 0.

 就是找最近点对距离的一半
*/
// A divide and conquer program in C/C++ to find the smallest distance from a
// given set of points.

#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>

// A structure to represent a Point in 2D plane
struct Point
{
    float x, y;
};

// Needed to sort array of points according to X coordinate
int compareX(const void *a, const void *b)
{
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->x - p2->x);
}
// Needed to sort array of points according to Y coordinate
int compareY(const void *a, const void *b)
{
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->y - p2->y);
}

// A utility function to find the distance between two points
float dist(Point p1, Point p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                (p1.y - p2.y) * (p1.y - p2.y));
}

// A Brute Force method to return the smallest distance between two points
// in P[] of size n
float bruteForce(Point *P, int n)
{
    float min = FLT_MAX;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (dist(P[i], P[j]) < min)
                min = dist(P[i], P[j]);
    return min;
}

// A utility function to find minimum of two float values
float min(float x, float y)
{
    return (x < y) ? x : y;
}

// A utility function to find the distance beween the closest points of
// strip of given size. All points in strip[] are sorted accordint to
// y coordinate. They all have an upper bound on minimum distance as d.
// Note that this method seems to be a O(n^2) method, but it's a O(n)
// method as the inner loop runs at most 6 times
float stripClosest(Point strip[], int size, float d)
{
    float min = d; // Initialize the minimum distance as d

    qsort(strip, size, sizeof(Point), compareY);

    // Pick all points one by one and try the next points till the difference
    // between y coordinates is smaller than d.
    // This is a proven fact that this loop runs at most 6 times
    for (int i = 0; i < size; ++i)
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; ++j)
            if (dist(strip[i], strip[j]) < min)
                min = dist(strip[i], strip[j]);

    return min;
}

// A recursive function to find the smallest distance. The array P contains
// all points sorted according to x coordinate
float closestUtil(Point *P, int n)
{
    // If there are 2 or 3 points, then use brute force
    if (n <= 3)
        return bruteForce(P, n);

    // Find the middle point
    int mid = n / 2;
    Point midPoint = P[mid];

    // Consider the vertical line passing through the middle point
    // calculate the smallest distance dl on left of middle point and
    // dr on right side
    float dl = closestUtil(P, mid);
    float dr = closestUtil(P + mid, n - mid);

    // Find the smaller of two distances
    float d = min(dl, dr);

    // Build an array strip[] that contains points close (closer than d)
    // to the line passing through the middle point
    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++)
        if (abs(P[i].x - midPoint.x) < d)
            strip[j] = P[i], j++;

    // Find the closest points in strip. Return the minimum of d and closest
    // distance is strip[]
    return min(d, stripClosest(strip, j, d));
}

// The main functin that finds the smallest distance
// This method mainly uses closestUtil()
float closest(Point *P, int n)
{
    for (int i = 0; i < n; i++)
        printf("%lf %lf\n", P[i].x, P[i].y);
    qsort(P, n, n * sizeof(Point), compareX);
    for (int i = 0; i < n; i++)
        printf("%lf %lf\n", P[i].x, P[i].y);

    // Use recursive function closestUtil() to find the smallest distance
    return closestUtil(P, n);
}

// Driver program to test above functions
Point P[100005];
int main()
{
    int n;
    while (true)
    {
        scanf("%d", &n);
        if (n == 0)
            break;
        for (int i = 0; i < n; i++)
        {
            scanf("%lf%lf", &P[i].x, &P[i].y);
        }
        for (int i = 0; i < n; i++)
            printf("%lf %lf\n", P[i].x, P[i].y);
        printf("%0.2lf\n", closest(P, n));
    }
    return 0;
}
