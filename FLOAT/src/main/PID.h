// I literally stole this code from last season, dont judge me.

#pragma once

class PID {
public:
  PID(double kp, double ki, double kd, double outMin, double outMax);

  // Run one control step. `dt` is the elapsed time in seconds since the last
  // call. Returns the clamped controller output.
  double compute(double error, double dt);

  // Clear integral/derivative memory — call on every state transition so a new
  // hold does not inherit the previous phase's accumulated error.
  void reset();

  // Re-tune live (A2: gains are placeholders until tuned in water).
  void setGains(double kp, double ki, double kd);

  double kp() const { return _kp; }
  double ki() const { return _ki; }
  double kd() const { return _kd; }

private:
  double _kp, _ki, _kd;
  double _outMin, _outMax;
  double _integral;
  double _prevError;
  bool   _firstStep;
};