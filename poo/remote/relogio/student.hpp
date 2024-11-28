#pragma once
#include "fn.hpp"

class Student {
private:            //atributos privados
    int hour2 {0};
    int minute2  {0};
    int second2  {0};
    // Time time;

public:

     int init(int hour = 0, int minute = 0, int second = 0) {
        //(void) hour;
        //(void) minute;
        //(void) second;
        //std::cout << hour << ":" << minute << ":" << second << std::endl;
        // this->time = Time(hour, minute, second);
        if(hour < 0 || hour > 23){
            std::cout << "fail: hora invalida"<< std::endl;
            this->hour2 = 0;
        }else{
        this->hour2 = hour;
        }
        if(minute < 0 || minute > 59){
            std::cout << "fail: minuto invalido"<< std::endl;
            this->minute2 = 0;
        }else{
        this->minute2 = minute;
        }
        if(second < 0 || second > 59){
            std::cout << "fail: segundo invalido"<< std::endl;
            this->second2 = 0;
        }else{
        this->second2 = second;
        }

        return 0;
    }

    void setHour(int hour) {
        (void) hour;
        if(hour < 0 || hour > 23){
            std::cout << "fail: hora invalida"<< std::endl;
        }else{
        this->hour2 = hour;
        }
        
        // this->time.setHour(hour);
    }

    void setMinute(int minute) {
        (void) minute;
        if(minute < 0 || minute > 59){
            std::cout << "fail: minuto invalido"<< std::endl;
        }else{
        this->minute2 = minute;
        }
        // this->time.setMinute(minute);
    }
    void setSecond(int second) {
        (void) second;
        if(second < 0 || second > 59){
            std::cout << "fail: segundo invalido"<< std::endl;
        }else{
        this->second2 = second;
        }
        // this->time.setSecond(second);
    }

    //void toString(){
      //  std::cout << hour << ":" << minute << ":" << second << std::endl;
        
    //}

    void nextSecond() {
        this->second2 ++;
        if(this->second2 == 60){
            this->second2 = 0;
            this->minute2 ++;
            if(this->minute2 == 60){
                this->minute2 = 0;
                this->hour2 ++;
                if(this->hour2 == 24){
                    this->hour2 = 0;
                }
            }
        }
        
    }
    
    void show() {
        std::cout << std::setfill('0') << std::setw(2) << this->hour2 << ":" << std::setw(2) << this->minute2 << ":" << std::setw(2) << this->second2 << std::endl;
        // fn::write(time);
    }
};