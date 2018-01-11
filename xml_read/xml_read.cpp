
#include <boost/property_tree/ptree.hpp>

#include <boost/property_tree/xml_parser.hpp>

#include <boost/typeof/typeof.hpp>

#include <iostream>

#include <exception>

int main()

{
    
    using boost::property_tree::ptree;
    
    ptree pt;
    
    try  {
        
        read_xml("config2.xml",pt);
        
        BOOST_AUTO(child,pt.get_child("school").get_child("class"));
        for(BOOST_AUTO(pos,child.begin());pos!=child.end();++pos)
            
            std::cout<<pos->second.get<int>("<xmlattr>.id")<<" "<<pos->second.get<std::string>("name")<<" "<<pos->second.get<std::string>("song")<<std::endl;
        
        // system("pause");测试时用，可以让程序暂时停在此处
        
    }
    
    catch (std::exception& e)
    
    {
        
        std::cout<<"Error:"<<e.what()<<std::endl;
        
        return -1;
        
    }
    
}
