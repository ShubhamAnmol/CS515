This is documentation of assignment 10 in CS515.
/////////////////////////////////////////
Problem statement : Finding total area of two triangles.

Assumption : All the point must be in first quadrant, meaning every coordinate has to be  positive. 

Input Format :  x1 y1 x2 y2 x2 y3
                x4 y4 x5 y5 x6 y6

Input Format Explanation : The input is contained in a file name input.txt .
  * There are two lines in input.
  * Each line contains coordinates for a triangle in a space seperated manner.


Approach to solution :
total_area=area(t1)+area(t2)-overlapped_area

overlapped_area : area of polygon formed by points of intersection of lines of traingle and the point inside each other. 

points inside each other : to find if point P is inside triangle ABC .
area(ABP)+area(ACP)+area(BCP) = area(ABC)

Intersection points : A line of triangle t1 intersects with a line triangle t2 if point of intersection lies in valid range. There will be nine such cases to check. 

Ordering points of polygon : To order points of polygon ,first the center of polygon is calculated and points are sorted according to 
slope of line joining the points to center. 

After ordering we can calculate the area of overlapped polygon and thus the total area.
 
