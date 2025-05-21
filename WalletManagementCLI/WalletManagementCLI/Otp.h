#ifndef OTP_H
#define OTP_H

#include <string>
#include <chrono>

class OTP {
public:
  int otpId;
  std::string otpCode;
  int userId;
  bool isUsed;
  std::chrono::system_clock::time_point expireTime;

  OTP(int id, std::string code, int uId, bool used, std::chrono::system_clock::time_point time);
};

#endif
