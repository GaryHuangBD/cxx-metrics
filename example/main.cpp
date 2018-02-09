//
// Created by garyhuang on 18-2-2.
//

#include <condition_variable>
#include <iostream>
#include <bits/std_mutex.h>
#include <Disruptor/Disruptor.h>
#include <Disruptor/ThreadPerTaskScheduler.h>
#include "Disruptor/IEventHandler.h"

struct LongEvent
{
    long value;
};

struct PrintingEventHandler : Disruptor::IEventHandler< LongEvent >
{
    explicit PrintingEventHandler(int toProcess) : m_actuallyProcessed(0), m_toProcess(toProcess)
    {}

    void onEvent(LongEvent& event, int64_t, bool) override
    {
        std::cout << "Event: " << event.value << std::endl;

        if (++m_actuallyProcessed == m_toProcess)
            m_allDone.notify_all();
    }

    void waitEndOfProcessing()
    {
        std::unique_lock<decltype(m_mutex)> lk(m_mutex);
        m_allDone.wait(lk);
    }

private:
    std::mutex m_mutex;
    std::condition_variable m_allDone;
    int m_toProcess;
    int m_actuallyProcessed;
};

int main()
{
    auto const ExpectedNumberOfEvents = 10000;
    auto const RingBufferSize = 1024;

    // Instantiate and start the disruptor
    auto eventFactory = []() { return LongEvent(); };
    auto taskScheduler = std::make_shared< Disruptor::ThreadPerTaskScheduler >();

    auto disruptor = std::make_shared< Disruptor::disruptor<LongEvent> >(eventFactory, RingBufferSize, taskScheduler);
    auto printingEventHandler = std::make_shared< PrintingEventHandler >(ExpectedNumberOfEvents);

    disruptor->handleEventsWith(printingEventHandler);

    taskScheduler->start();
    disruptor->start();

    // Publish events
    auto ringBuffer = disruptor->ringBuffer();
    for (auto i = 0; i<ExpectedNumberOfEvents; ++i)
    {
        auto nextSequence = ringBuffer->next();
        (*ringBuffer)[nextSequence].value = i;
        ringBuffer->publish(nextSequence);
    }

    // Wait for the end of execution and shutdown
    printingEventHandler->waitEndOfProcessing();

    disruptor->shutdown();
    taskScheduler->stop();

}
