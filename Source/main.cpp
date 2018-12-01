#include "../lib/headers.hpp"


int main(int argc, char const *argv[])
{
    if(argv[1] == "-p" || "-P")
    {
        
        if(argv[2] != NULL)
        {
            port = atoi(argv[2]);
            
        }
        
        else
        {
            port = 8888;
        }
        
        

    }
    else
    {
        port = 8888;
    }
    
    

    
}
