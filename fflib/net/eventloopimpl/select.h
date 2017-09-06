#ifndef _SELECT_IMPL_H_
#define _SELECT_IMPL_H_

#include <list>


#include "net/event_loop.h"
#include "base/task_queue_i.h"
#include "base/lock.h"

namespace ff {

#define CREATE_EPOLL_SIZE  4096
#define EPOLL_EVENTS_SIZE  128
//! 100 ms
#define EPOLL_WAIT_TIME    -1 

class Select: public EventLoopI
{
public:
    Select();
    ~Select();

    virtual int eventLoop();
    virtual int close();
    virtual int register_fd(Fd*);
    virtual int unregister_fd(Fd*);
    virtual int mod_fd(Fd*);

    int interupt_loop();//! 中断事件循环
protected:
    void fd_del_callback();

private:
    volatile bool            m_running;
    int                      m_efd;
    TaskQueueI*            m_task_queue;
    int                      m_interupt_sockets[2];
    //! 待销毁的error socket
    std::list<Fd*>   		     m_error_fd_set;
    Mutex                  m_mutex;
    
    //select
    fd_set         			 m_fdread;
    std::map<socket_fd_t, Fd*>  m_fd2ptr;
};

}
#endif
