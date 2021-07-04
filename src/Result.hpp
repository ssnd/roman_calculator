#pragma once

using ErrorCode = int64_t;

template<typename T>
class Result {
  T val_;
  bool has_value_ = false;
  ErrorCode err_ = 0;
  std::string desc_;

 public:
  bool HasValue() const {
    return has_value_;
  }
  const std::string &ErrorDesc() const {
    return desc_;
  }
  bool HasError() const {
    return err_ > 0;
  }
  void SetValue(T value) {
    has_value_ = true;
    val_ = std::move(value);
  }
  void SetError(std::string desc, ErrorCode code = 1) {
    err_ = code;
    desc_ = std::move(desc);
  }
  T GetValue() const {
    return val_;
  }
};
