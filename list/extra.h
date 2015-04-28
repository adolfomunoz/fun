#ifndef _FUNCTIONAL_EXTRA_H_
#define _FUNCTIONAL_EXTRA_H_

#include "fold.h"
#include "map.h"
#include "concatenate.h"
#include "../function/compose.h"
#include "../function/curry.h"

namespace fun {

/**************************************
 * fun::API                           *
 **************************************/
auto all     = compose(andl, map);
auto any     = compose(orl,  map);
    
};

#endif

