#pragma once
#include <cstddef>
#include "common.h"

class StringViewer
{
private:
	std::size_t start;
	std::size_t length;

public:
	StringViewer(void) = default;
	StringViewer(std::size_t start, std::size_t length)
	{
		this->start = start;
		this->length = length;
	}

	std::string GetString(std::string &string)
	{
		return string.substr(start,length);
	}
};

/*         Sorted.                  
                                                 @@@:                                  
                                                :@@@@@@@:                             
                                                @@@  @@@@@,                           
                                               .@@#    ,@@@;                          
                                               @@@       @@@                          
                                               @@@       @@@`                          
                                              @@@`       @@@                           
                                            .@@@@       :@@@                         
                                           @@@@        `@@@                          
                                         @@@@`        :@@@                            
                                       @@@@,         #@@@                              
                                     @@@@'          #@@@                              
                                   @@@@#           :@@@                                
                                 ,@@@@             @@@`                               
                                @@@@              @@@@                                
                              .@@@:               @@@                                 
                             @@@@                 @@@@@@@',                          
                           :@@@:                 `@@@@@@@@@@@@@@@@@                   
                         ;@@@@                                 :@@@@@@`              
              ,@@@@@@@@@@@@@                                        #@@@`             
              @@@:::,.`                                               @@@.             
             @@@:                                                      @@@            
            `@@@                                                      .@@@            
            #@@'                                                      @@@.            
            @@@                                                     '@@@:             
            @@@                                                   :@@@@               
            @@@                                                     @@@.             
            @@@                                                     .@@@             
            #@@:                                                    @@@@              
             @@@                                                ,@@@@@@               
             @@@`                                               @@@@`                  
              @@@@@@@@@@@`                                      @@@                   
              '@@@@@@@@@@@@                                    @@@@                   
                        `@@@@                             @@@@@@@@                     
                          ,@@@@                           @@@@.                       
                             @@@@;                       :@@@                          
                               #@@@@:        '@@@`     :@@@@.                         
                                  ;@@@@@@@@@@@@`@@@@@@@@@@@                            
*/