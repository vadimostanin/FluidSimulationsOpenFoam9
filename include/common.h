#include <vectorField.H>
#define WM_DP 1
#include <fixedValueFvPatchFields.H>
#include "fvPatchFieldMapper.H"
#include "volFields.H"
#include "surfaceFields.H"
#include "unitConversion.H"
#include <vector>
using namespace Foam;

#define ROT_MAX_SPEED (1e0/60*6.28)

typedef struct StartStopRangeT_
{
  bool mCCWDirection;
  scalar mStart, mStop, mSpeed;
  vector mAxis;
} StartStopRangeT ;

inline vectorField calculateVectorField(const vectorField &boundaryPatchField, const vector &center, const scalar &time, const std::vector<StartStopRangeT> &ranges)
{
  vectorField rot(boundaryPatchField.size(), vector(0,0,0));
  for(auto&& range : ranges)
  {
    if(time >= range.mStart && time <= range.mStop)
    {
      rot = range.mSpeed * (range.mCCWDirection ? 1 : -1) * range.mAxis ^ (boundaryPatchField - center);
      // std::cout << __func__ << ":" << __LINE__ << " rotate_speed=" << rotate_speed <<std::endl;
      break;
    }
  }
  return rot;
}
