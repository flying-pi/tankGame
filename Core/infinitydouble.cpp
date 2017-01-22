#include "infinitydouble.h"

InfinityDouble::InfinityDouble(InfinityDouble& id) {
  this->w = id.w;
  this->isInfinity = id.isInfinity;
}

InfinityDouble::InfinityDouble() {}

InfinityDouble* InfinityDouble::FromValue(double w) {
  InfinityDouble* result = new InfinityDouble();
  result->w = w;
  result->isInfinity = false;
  return result;
}

InfinityDouble* InfinityDouble::InfinityValue() {
  InfinityDouble* result = new InfinityDouble();
  result->isInfinity = true;
  return result;
}
