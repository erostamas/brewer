#include "CurvePlayer.h"
#include "Logging.h"

CurvePlayer::CurvePlayer(SystemPtr system)
: _system (system == nullptr ? std::make_shared<System>() : system) {

}

void CurvePlayer::playCurve(CurvePtr curve) {
    LOG_INFO << "[CurvePlayer] Playing curve - " << curve->getName();
    reset();
    _state = CurvePlayerState::RUNNING;
    _curve = curve;
    _currentSegment = _curve->getSegment(_currentSegmentIndex);
    _currentSetpoint = _currentSegment->getSetpoint();
    _nextStep = _system->getTsNow() + _currentSegment->getDuration();
    _endTime = _system->getTsNow() + _curve->getDuration();
    _currentCurveName = curve->getName();
}

void CurvePlayer::step() {
    if (_state == CurvePlayerState::PAUSED) {
        _endTime = _system->getTsNow() + _timeLeftOverall;
        _nextStep = _system->getTsNow() + _timeToNextSegment;
        return;
    } else if (_state != CurvePlayerState::RUNNING) {
        return;
    }
    _timeLeftOverall = _endTime - _system->getTsNow();
    if (_system->getTsNow() >= _nextStep) {
        if (_currentSegmentIndex < _curve->size() - 1) {
            ++_currentSegmentIndex;
            _currentSegment = _curve->getSegment(_currentSegmentIndex);
            if (_currentSegment == nullptr) {
                stop();
                return;
            }
            _currentSetpoint = _currentSegment->getSetpoint();
            _nextStep = _system->getTsNow() + _currentSegment->getDuration();
            _timeToNextSegment = _currentSegment->getDuration();
        } else {
            stop();
        }
    } else {
        _timeToNextSegment = _nextStep - _system->getTsNow();
    }
}

void CurvePlayer::stop() {
    if (_state == CurvePlayerState::RUNNING) {
        _curve = nullptr;
        _currentSegment = nullptr;
        _state = CurvePlayerState::IDLE;
        reset();
    }
}

void CurvePlayer::pause() {
    if (_state == CurvePlayerState::RUNNING) {
        _state = CurvePlayerState::PAUSED;
    }
}

void CurvePlayer::resume() {
    if (_state == CurvePlayerState::PAUSED) {
        _state = CurvePlayerState::RUNNING;
    }
}

void CurvePlayer::reset() {
    _currentSegmentIndex = 0;
    _nextStep = 0;
    _currentSetpoint = -1;
}