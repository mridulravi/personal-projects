#include "QueueingSystem.h"

void QueueingSystem::enqueue(Request r) {

  //Enqueue request in buffer
  buffer.push(r);
 
}

Request  QueueingSystem::nextReq() {

  //Returns request at the front of the queue
 
  //Does not remove the request
  Request r = buffer.front();
  return r;

}

Request  QueueingSystem::dequeue() {

  //Returns request at the front of the queue (which is the request
  // being serviced)
  // Removes the request

  Request r = buffer.front();
  buffer.pop();
  return r;

}

int QueueingSystem::Buffersize() {

  return buffer.size();

}

