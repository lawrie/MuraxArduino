#ifndef _QUADRATURE_CLASS_
#define _QUADRATURE_CLASS_

#define IO_QUADRATURE_VALUE (*(volatile uint32_t*) IO_QUADRATURE)

#include <dev/io.h>

class QuadratureClass {
  public:
    int read(void);
};

extern QuadratureClass Quadrature;

#endif

