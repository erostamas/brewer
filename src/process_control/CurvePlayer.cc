#include "CurvePlayer.h"

CurvePlayer::CurvePlayer(SystemPtr system)
: _system (system == nullptr ? std::make_shared<System>() : system) {
    
}