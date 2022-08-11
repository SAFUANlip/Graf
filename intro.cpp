#include <iostream>
#include <string>

/////
///// in master
/////
int main(){
	int a = 5;
	int b = 7;
	std::cout<<a+b;
    std::string s = "HH";
    std::string ss = "HAha";
    std::string sss;
    (s+ss) = sss;
    std::cout<<sss<<'\n';
    std::cout<<s<<' '<<ss<<'\n';

}


