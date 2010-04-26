
#ifndef MALTA_H
#define MALTA_H

#include "mips4kc.h"
#include "display.h"

#define IO_BASE1 0xbf000000

#define IO_DEVICE(Type,Name,Address) \
  static volatile Type* const Name = (Type*) (Address)

#define IO_DEVICE1(Type,Name,Offset) IO_DEVICE(Type, Name, IO_BASE1 + Offset)

/* malta: 8 digit LED */
IO_DEVICE1(display_t,malta,0x10);

/* Make sure we don't clutter preprocessor namespace */
#undef IO_BASE1
#undef IO_DEVICE
#undef IO_DEVICE1

#endif
