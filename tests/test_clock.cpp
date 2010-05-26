/**
 * @file testr_clock.cpp
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 *
 *
 * @date 2009/12/13
 *
 * This file is part of the DGtal library
 */

 /**
   * Description of test_clock' <p>
   * Aim: simple test of \ref Clock
   */


#include <cstdio>
#include <cmath>
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/utils/Clock.h"

using namespace DGtal;
using namespace std;

/// Minimal tick must be >=0
bool test_minimalTick()
{
  double tick;
  Clock c;

  trace.info() << c <<std::endl;
  
  c.startClock();
  tick = c.stopClock();
  trace.info() << "Minimal tick: "<< tick <<endl;
  return (tick >= 0);
}

/// Loop ticks must be >=0
bool test_loopTick()
{
  double tick,tmp=0;

  Clock c;
  c.startClock();
  for(unsigned int i=0 ; i< 4334450; i++)
    tmp = cos(tmp+i);

  tick = c.stopClock();
  trace.info()<< "Loop tick: "<< tick <<endl;
  return (tick >= 0);
}

/// Test several loops
bool test_MultipleLoop()
{
 double tick1,tick2,tmp=0;

  Clock c;
  c.startClock();
  for(unsigned int i=0 ; i< 4334450; i++)
    tmp = cos(tmp+i);

  Clock c2;
  c2.startClock();
  for(unsigned int i=0 ; i< 4334450; i++)
    tmp = cos(tmp+i);

  tick2 = c2.stopClock();

  for(unsigned int i=0 ; i< 4334450; i++)
    tmp = cos(tmp+i);

  tick1 = c.stopClock();
  trace.info()<< "Loop tick1: "<< tick1 <<" Loop tick2: "<< tick2 <<endl;
  return (tick1 >= 0);
}


int main()
{
  if (test_minimalTick() && test_loopTick() && test_MultipleLoop())
    return 0;
  else
    return 1;

}