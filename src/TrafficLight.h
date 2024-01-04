#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "TrafficObject.h"
#include <condition_variable>
#include <deque>
#include <mutex>

// forward declarations to avoid include cycle
class Vehicle;
enum TrafficLightPhase { red, green };

template <class T> class MessageQueue {
public:
  void send(T &&msg);
  T receive();

private:
  std::mutex _mutex;
  std::condition_variable _cond;
  std::deque<T> _messages;
};

// FP.1 : Define a class „TrafficLight“ which is a child class of TrafficObject.
// The class shall have the public methods „void waitForGreen()“ and „void
// simulate()“ as well as „TrafficLightPhase getCurrentPhase()“, where
// TrafficLightPhase is an enum that can be either „red“ or „green“. Also, add
// the private method „void cycleThroughPhases()“. Furthermore, there shall be
// the private member _currentPhase which can take „red“ or „green“ as its
// value.

class TrafficLight : public TrafficObject {
public:
  // constructor / desctructor

  TrafficLight();

  // getters / setters
  TrafficLightPhase getCurrentPhase();

  // typical behaviour methods
  void simulate();
  void waitForGreen();
  
  

private:

  TrafficLightPhase _currentPhase;
  void cycleThroughPhases();
  std::shared_ptr<MessageQueue<TrafficLightPhase>> msgQueue;
  std::condition_variable _condition;
  std::mutex _mutex;
};

#endif