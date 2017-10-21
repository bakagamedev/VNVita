#pragma once
#include <cstddef>
#include "common.h"

class Stringviewer
{
private:
	std::size_t Start;
	std::size_t Length;

public:
	Stringviewer(void) = default;
	Stringviewer(std::size_t Start, std::size_t Length)
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