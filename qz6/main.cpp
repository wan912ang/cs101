#include <iostream>
#include <string>
using namespace std;

class Clock{
    public:
        int Hour;
        int minute;
        int second;
        string meridian;
        Clock(int h, int m, int s, string x){
            Hour = h;
            minute = m;
            second = s;
            meridian = x;
        }
        void display(){
            cout << Hour << ":" << minute << ":" << second << " " << meridian << endl;
        }
};

class StandardClock : Clock{
    private:
        string a_meridian;
    public:
        StandardClock(int h, int m, int s, string x):Clock(h,m,s,x){
            if(x == "AM"){
                a_meridian = "上午";
            }
            else if(x == "PM"){
                a_meridian = "下午";
            }
        }
        void display(){
            cout << a_meridian << " " << Hour << ":" << minute << ":" << second << endl;
        }
};

class MilitaryClock : Clock{
    private:
        int p_hour;
    public:
        MilitaryClock(int h, int m, int s, string x):Clock(h,m,s,x){
            p_hour = h;
            if(x == "PM"){
                p_hour += 12;
            }
        }
        void display(){
            cout << p_hour << ":" << minute << ":" << second << endl;
        }
};

int main(){
    Clock cc(10,25,43,"AM");
    StandardClock sc(10,25,43,"AM");
    MilitaryClock mc(10,25,43,"PM");
    cc.display();
    sc.display();
    mc.display();
    return 0;
}
