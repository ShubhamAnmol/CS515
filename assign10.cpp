#include<iostream>
#include<cstdlib>
#include<fstream>
#include<cmath>
using namespace std;
class point{
    float x,y;
    
    public:
    point(float i=0,float j=0):x(i),y(j){}
    point(const point &p1):x(p1.x),y(p1.y){}
    float getx() const{return x;}
    float gety() const{return y;}
    bool operator ==(const point &p1)
    {
       if(abs(p1.x-x)<0.000001 && abs(p1.y-y)<0.000001)
        return true; 
        return false;
     }
    friend ostream & operator << (ostream &out, const point &p);
};
class line{
    point p1,p2;
    
    public:
    line(){p1= point(-1,-1); p2= point(-1,-1);}
    line(point e1,point e2):p1(e1),p2(e2){}
    line(const line &l1):p1(l1.p1),p2(l1.p2){}
    double length() const
    {
     return sqrt(pow((p1.getx()-p2.getx()),2)+ pow((p1.gety()-p2.gety()),2));
        
    }
    point showp1() {return p1;}
    point showp2() {return p2;}
    point minx()
    {
        if(p1.getx()<p2.getx())
        return p1;
        else
        return p2;
    }
    point maxx()
    {
        if(p1.getx()>p2.getx())
        return p1;
        else
        return p2;
    }
    
};
class triangle{
    point p[3];
    line l[3];
    
    public:
     triangle(point e1,point e2,point e3)
     {
           p[0]=e1; p[1]=e2;p[2]=e3;
           l[0] = line(e1,e2);
           l[1] = line(e2,e3);
           l[2] = line(e1,e3);
     } 
         
    double area() const
    {
        double ar = (abs(p[0].getx()*(p[1].gety()-p[2].gety())+  p[1].getx()*(p[2].gety()-p[0].gety())+ p[2].getx()*(p[0].gety()-p[1].gety()) ))/2;
        return ar;  
    }  
    friend bool isinside(const triangle t1, const point p);
    friend int ptinside(triangle t1,triangle t2, point* ptintersect);
    friend int Intersections(triangle t1,triangle t2, point* ptarr);
    friend bool intersect(const line &l1 ,const line &l2, point* pt);
};

bool isinside(const triangle t1,const point p)
{
    triangle tri1(t1.p[0],t1.p[1],p);
    triangle tri2(t1.p[1],t1.p[2],p);  
    triangle tri3(t1.p[0],t1.p[2],p);  
      // cout<<tri1.area()<<endl;
      // cout<<tri2.area()<<endl;
      // cout<<tri3.area()<<endl;
      // cout<<t1.area()<<endl;
    
    if((tri1.area()+tri2.area()+tri3.area())- t1.area()>0.000001){return false;}
    else
    return true;
}

int ptinside(triangle t1,triangle t2,point* ptintersect)
{
    int count = 0;
    
    //cout<<"triangle t1 "<<t1.p[0]<<t1.p[1]<<t1.p[2]<<endl;
    
   // cout<<"triangle t2"<<t2.p[0]<<t2.p[1]<<t2.p[2]<<endl;
    
    for(int i=0;i<3;i++)
    {
        if(isinside(t1,t2.p[i]))
        {
          ptintersect[count]= t2.p[i];
          count++;
          
        //  cout<<t2.p[i]<<" Yes"<<endl;
        }
        else
        {
           // cout<<t2.p[i]<<" No"<<endl;
        }
    } 
    
    for(int i=0;i<3;i++)
    {
        if(isinside(t2,t1.p[i]))
        {
          ptintersect[count]= t1.p[i];
          count++;
            
        //  cout<<t1.p[i]<<" Yes"<<endl;
        }
        else
        {
          //cout<<t2.p[i]<<" No"<<endl;
        }
    } 
  //  cout<<"triangle t1 "<<t1.p[0]<<t1.p[1]<<t1.p[2]<<endl;
    
   // cout<<"triangle t2"<<t2.p[0]<<t2.p[1]<<t2.p[2]<<endl;
    
  return count;
}
point pt_minx(point p1,point p2)
{
    if(p1.getx()<p2.getx())
    return p1;
    else
    return p2;
}
point pt_maxx(point p1,point p2)
{
    if(p1.getx()>p2.getx())
    return p1;
    else
    return p2;
}
bool intersect(line &l1 ,line &l2, point *pt)
{
   
 point behind = pt_maxx(l1.minx(),l2.minx()) ;
 point ahead = pt_minx(l1.maxx(),l2.maxx());
    
    float A1 = (l1.showp1().gety()-l1.showp2().gety())/(l1.showp1().getx()-l1.showp2().getx()) ;
    
    float A2 = (l2.showp1().gety()-l2.showp2().gety())/(l2.showp1().getx()-l2.showp2().getx()) ;
    
    if(abs(A1-A2)<0.000001)
    {
       return false;
    }
    float b1 = l1.showp1().gety() - A1*l1.showp1().getx();
    
    float b2 = l2.showp1().gety() - A2*l2.showp1().getx();
    
    float Xa = (b2-b1)/(A1-A2);
    
    float Ya =  A1*Xa + b1 ;
    
    if((Xa-behind.getx()>=0) && (Xa-ahead.getx()<=0))
    {
        *pt = point(Xa,Ya) ;
        return true;
    }
    else
    {
       return false;
    }
}
int Intersections(triangle t1,triangle t2,point* ptarr)
{
    point *pt = new point;
    int count =0;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {
          if(intersect(t1.l[i],t2.l[j],pt))         
          {
            ptarr[count] = *pt;
            count++ ;
          } 
        }
   return count;
}
double area(point *pt, int n)
{
    if(n<3)
    return 0.0;
    double ar = 0.0;
    int j = n-1;
    for(int i =0;i<n;i++)
    {
        ar += (pt[j].getx()+pt[i].getx())*(pt[j].gety()- pt[i].gety());
        j=i;
    }
   return abs(ar/2.0);
}
point* order(point * pt ,int n)
{
    float centrex=0,centrey=0;
    for(int i =0;i<n;i++)
    {
        centrex += pt[i].getx();
        centrey += pt[i].gety();
    }
    
    centrex = centrex/n;
    centrey = centrey/n;
    
    //cout<<centrex<<" "<<centrey<<endl; 
    
    double *angles = new double[n] ;
    int *arr = new int[n] ;
    for(int i = 0; i<n;i++)
    {
         angles[i] = atan((centrey-pt[i].gety())/(centrex-pt[i].getx()));  
         arr[i] = i;
    }
   /* for(int i =0;i<n;i++)
    {
        cout<<angles[i]<<endl; 
    }
    for(int i =0;i<n;i++)
    {
      cout<<arr[i]<<endl; 
    }*/
    double temp ;
    int tem ;
    for(int i = 0;i<n-1;i++)
      for(int j =0;j<n-i-1;j++)
       {
           if(angles[j]>angles[j+1])
           {
              temp = angles[j];
              angles[j] = angles[j+1] ;
              angles[j+1] = temp;
            
              tem = arr[j] ;
              arr[j] = arr[j+1];
              arr[j+1] = tem;
           }
       }
     /*   for(int i =0;i<n;i++)
        {
          cout<<angles[i]<<endl; 
        }
    
        for(int i =0;i<n;i++)
        {
          cout<<arr[i]<<endl; 
        }*/
    
      point* orderedpt = new point[n] ;
      for(int i =0; i<n; i++)
      {
        orderedpt[i] = pt[arr[i]];
      }
    return orderedpt ;
}
int removedup(point *pt,int count,point *nodup)
{
    bool *marker = new bool[count];
    for(int i=0;i<count;i++)
    {marker[i]= false;}
 
    int counter = 0;
    for(int i=0;i<count;i++)
    {  
        if(marker[i] == true)
        continue;
       
        marker[i] = true;
        nodup[counter] = pt[i];
        // cout<<nodup[counter]<<endl;
        counter++;
       
        for(int j=i+1;j<count;j++)
        {
            if(pt[i] == pt[j])
            {
               marker[j] = true;
            }
        }
    }
   /* for(int i=0;i<count;i++)
    cout<<marker[i]<<endl;*/
    
    return counter;
}
ostream & operator << (ostream &out, const point &p) 
{ 
    out<<"("<<p.x<<","<<p.y<<")"<<endl;
    return out;
}
int main()
{
    ifstream fin;
    fin.open("ip.txt");
    
    // reading input from file ip.txt
    int tri[6][2];
    for(int i =0; i<6;i++)
      for(int j=0;j<2;j++) {fin>>tri[i][j];}
    
    // validating the input
       for(int i =0; i<6;i++)                                                    
       for(int j=0;j<2;j++)
      {if(tri[i][j]<0)
        {cout<<"invalid input"<<endl;exit(1);
        }
      }
    // initialising points to later initialise a triangle
    point* pt=new point[6];
    for(int i=0;i<6;i++)
    {pt[i] = point(tri[i][0],tri[i][1]);}
        
    /*cout<<"points"<<endl;
    for(int i=0;i<6;i++)  //for check
    {cout<<pt[i]<<" ";}
    cout<<endl;*/
    
    // intialising truangles
    triangle t1(pt[0],pt[1],pt[2]);
    triangle t2(pt[3],pt[4],pt[5]);
    
    // collecting list of points inside other triangle
    point* pinside = new point[6] ;
    int count_in = 0;  
    count_in = ptinside(t2,t1,pinside);
     
 /* cout<<"points inside"<<endl;
    for(int i=0;i<count_in;i++)
    {cout<<pinside[i]<<" ";}
    cout<<endl;*/
    
    // collecting point of intersections from  both triangles 
    point* intsection = new point[6];
    int count_int = 0;
    count_int = Intersections(t1,t2,intsection);
        
    /* cout<<"points intersection"<<endl;
     for(int i=0;i<count_int;i++)
     {cout<<intsection[i]<<" ";}
      cout<<endl;*/
    
    // merging both inside points and intersection points
    int total_count = count_in + count_int ;
    point* pt_fin = new point[total_count];
    int j = 0;
    for(int i= 0 ; i<total_count;i++)
    { 
        if(i<count_in)
        pt_fin[i] = pinside[i];
        else
        {
           pt_fin[i] = intsection[j];
           j++ ;
        }
     }
    /*cout<<"points final merged"<<endl;
    for(int i=0;i<total_count;i++)
    {cout<<pt_fin[i]<<" ";}
    cout<<endl;
        cout<<"total_count :   "<<total_count<<endl;*/
    // removing any duplicate points
     point* nodup = new point[10];
     total_count = removedup(pt_fin,total_count,nodup);
        
    /*cout<<"after removing duplicate"<<endl;
    for(int i=0;i<total_count;i++)
    {cout<<nodup[i]<<" ";}
    cout<<endl;*/
    
  //  cout<<t1.area()<<endl;
  //  cout<<t2.area()<<endl;
    
   // cout<<total_count<<endl;
    
    point * ordered = new point[total_count];
    ordered = order(nodup,total_count);
    
   /* cout<<"after ordered"<<endl;
    for(int i =0;i<total_count;i++)
    {cout<<ordered[i]<<endl;}*/
    
    double ar = area(ordered,total_count);
  //  cout<<" polygon area "<<ar<<endl;
    //cout<<area(order(nodup,total_count),total_count);
    
   // calculating the overlapped area
    cout<<"total area : ";
    cout<<t1.area()+t2.area()-ar<<endl;
    
  return 0;
}