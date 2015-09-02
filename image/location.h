// Copyright (c) 2015 Dingler. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DINGLER_IMAGE_LOCATION_H_
#define DINGLER_IMAGE_LOCATION_H_

#include <string>

#include "base/basictypes.h"

namespace image {
// A location within the image file of a given object
// eg. "/object/x" maps the url to the given object
// that are indexed in the image index
class Location {
public:
 Location();
 ~Location();
private:
 DISALLOW_COPY_AND_ASSIGN(Location);
};

}

#endif