#pragma once                   
#ifndef _B_H                   
#define _B_H                   
                               
#include <stdint.h>            
                               
                               
                               
class B{                       
    public:                    
        B(){                   
            b = 0;             
        };                     
    void SetB(uint32_t value){ 
            b = value;         
    }                          
                               
    uint32_t GetB(){           
        return b;              
    }                          
                               
    private:                   
        uint32_t b;            
                               
};                             
                               
                               
                               
                               
                               
                               
                               
                               
                               
                               
                               
                               
                               
                               
                               
#endif                         
