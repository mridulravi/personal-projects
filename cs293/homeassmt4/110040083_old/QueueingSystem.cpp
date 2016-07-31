#include "QueueingSystem.h"

void QueueingSystem::enqueue(Request r) {

  //Enqueue request in buffer, set serverBusy to true as this might be a request
  //coming to an idle server 

  buffer.push(r);
  serverBusy = true;

}

Request  QueueingSystem::nextReq() {

  //Returns request at the front of the queue
  //This is the request in service
  //Does not remove the request
  Request r = buffer.top();
  return r;

}

Request  QueueingSystem::dequeue() {

  //Returns request at the front of the queue (which is the request
  // being serviced
  // Removes the request and adjusts server busy state if no more
  // requests in queue

  Request r = buffer.top();
  buffer.pop();
  if (buffer.empty() )
    serverBusy = false;
  return r;

}

int QueueingSystem::Buffersize() {

  return buffer.size();

}

bool QueueingSystem::isBusy() {

  return serverBusy;

}
