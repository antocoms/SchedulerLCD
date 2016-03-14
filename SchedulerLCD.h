#ifndef SchedulerLCD_h
#define SchedulerLCD_h

#include <Arduino.h>



template<typename T>
class SchedulerLCD
{
   public:

      SchedulerLCD(T* lcd);
      ~SchedulerLCD();

      void setTimer(int timer);
      void print(const char* firstLine, ...);
      void reset();


   private:

      unsigned long time_last_call;
      int call, next_call, _timer;
      T* _lcd;
};



#endif



template<typename T>
SchedulerLCD<T>::SchedulerLCD(T* lcd)
{
  time_last_call = 0;
  call = 0;
  next_call = 1;
  _timer = 2000;
  _lcd = lcd;
}



template<typename T>
SchedulerLCD<T>::~SchedulerLCD()
{
 // ...
}



template<typename T>
void SchedulerLCD<T>::setTimer(int timer)
{
  _timer = timer;
}



template<typename T>
void SchedulerLCD<T>::print(const char* firstLine, ...)
{
  call++;

  if (millis() - time_last_call >= _timer && call == next_call)
  {
    va_list lines;
    va_start(lines,firstLine);
    const char* line = firstLine;
    int i = 0;

    _lcd -> clear();

    do {
      _lcd -> setCursor(0, i);
      _lcd -> printstr(line);
      i++;
    } while((line = va_arg(lines, char*)) != "\0");

    va_end(lines);
    next_call++;
    time_last_call = millis();
  }
}



template<typename T>
void SchedulerLCD<T>::reset()
{

  if (call+1 == next_call)
  {
    next_call = 1;
  }

  call = 0;
}
