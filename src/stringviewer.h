#pragma once
#include <cstddef>
#include "common.h"

class StringViewer
{
private:
	std::size_t Start;
	std::size_t Length;

public:
	StringViewer(void) = default;
	StringViewer(std::size_t Start, std::size_t Length)
	{
		this->Start = Start;
		this->Length = Length;
	}

	std::string GetString(std::string &String)
	{
		return String.substr(Start,Length);
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