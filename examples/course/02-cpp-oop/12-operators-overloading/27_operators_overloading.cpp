#include <string>
#include <iostream>

class A
{
public:
     explicit A(const int& value): m_value{value} {}
     int getA() const { return m_value; }
     A& operator=(A&& a) { m_value = a.m_value; return *this; }
     A(A&& a) : m_value {a.m_value} {}
     friend A operator+(const A& a, int);
     friend A operator+(int x, const A& a)
     { 
          A aRes(x + a.m_value);
          return aRes;
     }

     // member operator
     A operator+(std::string& str);
private:
     int m_value;
};

A A::operator+(std::string& str)
{
    m_value += std::atoi(str.c_str());
    return A(m_value);
}

A operator+(const A& a, int x)
{
     return x + a;
}
A operator+(const A& a, const A& b)
{
     int x = a.getA() + b.getA();
     return A(x);
}
////////////////////////////////////////////
class Frame
{
public:
     enum class Origin
     {
          Server,
          Client,
     };
     Frame(int length, const std::string& payload, Origin origin):
          m_length{length}, m_payload{payload}, m_origin{origin} {}
          
     friend std::ostream& operator<<(std::ostream& out, const Frame& frame);
private:
     int m_length;
     std::string m_payload;
     Origin m_origin;
};

std::ostream& operator<<(std::ostream& out, const Frame::Origin& origin)
{
    out << (origin == Frame::Origin::Server ? "Server" : "Client");
    return out;
}

std::ostream& operator<<(std::ostream& out, const Frame& frame)
{
     out << "length " << frame.m_length
               << " data " << frame.m_payload <<  " origin " 
               << frame.m_origin;
     return out;
}

int main()
{
     A a(1);
     a = a + 2;
     std ::cout << "Result " << a.getA() << std::endl;
     a = 3 + a;
     std ::cout << "Result " << a.getA() << std::endl;
     A a1(2);
     std::cout << "Sum " << (a + a1).getA() << std::endl;
     
     std::string str("23");
     a = a + str;
     std ::cout << "Result sum string " << a.getA() << std::endl;

     Frame f(10, "Test frame", Frame::Origin::Client);
     std::cout << "Frame details: " << f << std::endl;

     return 0;
}