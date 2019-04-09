#ifndef _QUADRATURE_CLASS_
#define _QUADRATURE_CLASS_

#define IO_QUADRATURE (*(volatile uint32_t*)0xF00F8000)

class QuadratureClass {
  public:
    int read(void);
};

extern QuadratureClass Quadrature;

#endif

