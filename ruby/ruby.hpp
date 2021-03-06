/*
  ruby
  version: 0.11 (2013-12-19)
  license: public domain
*/

#ifndef RUBY_H
#define RUBY_H

#include <nall/nall.hpp>

namespace ruby {

#include <ruby/video.hpp>
#include <ruby/audio.hpp>
#include <ruby/input.hpp>

struct VideoInterface {
  void driver(const char* driver = "");
  const char* optimalDriver();
  const char* safestDriver();
  const char* availableDrivers();
  bool init();
  void term();

  bool cap(const nall::string& name);
  nall::any get(const nall::string& name);
  bool set(const nall::string& name, const nall::any& value);

  bool lock(uint32_t*& data, unsigned& pitch, unsigned width, unsigned height);
  void unlock();
  void clear();
  void refresh();

  VideoInterface();
  ~VideoInterface();

private:
  Video* p = nullptr;
};

struct AudioInterface {
  void driver(const char* driver = "");
  const char* optimalDriver();
  const char* safestDriver();
  const char* availableDrivers();
  bool init();
  void term();

  bool cap(const nall::string& name);
  nall::any get(const nall::string& name);
  bool set(const nall::string& name, const nall::any& value);

  void sample(uint16_t left, uint16_t right);
  void clear();

  AudioInterface();
  ~AudioInterface();

private:
  Audio* p = nullptr;
};

struct InputInterface {
  nall::function<void (nall::HID::Device& device, unsigned group, unsigned input, int16_t oldValue, int16_t newValue)> onChange;

  void driver(const char* driver = "");
  const char* optimalDriver();
  const char* safestDriver();
  const char* availableDrivers();
  bool init();
  void term();

  bool cap(const nall::string& name);
  nall::any get(const nall::string& name);
  bool set(const nall::string& name, const nall::any& value);

  bool acquire();
  bool unacquire();
  bool acquired();

  nall::vector<nall::HID::Device*> poll();
  bool rumble(uint64_t id, bool enable);

  InputInterface();
  ~InputInterface();

private:
  Input* p = nullptr;
};

extern VideoInterface video;
extern AudioInterface audio;
extern InputInterface input;

};

#endif
