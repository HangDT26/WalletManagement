#include "OTP.h"
#include "pch.h"

OTP::OTP(int id, std::string code, int uId, bool used, std::chrono::system_clock::time_point time)
  : otpId(id), otpCode(code), userId(uId), isUsed(used), expireTime(time) {}
