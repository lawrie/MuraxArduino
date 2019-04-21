#ifndef _MUX_CLASS_
#define _MUX_CLASS_

class MuxClass {
  public:
    void set(int pin);
    void unset(int pin);
};

extern MuxClass Mux;

#endif

