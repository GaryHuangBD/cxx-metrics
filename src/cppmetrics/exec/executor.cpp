#include "executor.h"

namespace cppmetrics {
namespace exec {

struct MetricEventHandler : Disruptor::IEventHandler<MetricWrap>
{
    void onEvent(MetricWrap& event, int64_t, bool) override
    {
        event.metricPtr->statInner(event.metricValuePtr);
    }
};


void Executor::creatWorker()
{
    auto const RingBufferSize = 1024;
    // Instantiate and start the disruptor
    auto eventFactory = []() { return MetricWrap(); };
    auto taskScheduler = std::make_shared< Disruptor::ThreadPerTaskScheduler >();
    auto disruptor = std::make_shared< Disruptor::disruptor<MetricWrap> >(eventFactory, RingBufferSize, taskScheduler);
    auto eventHandler = std::make_shared<MetricEventHandler>();
    disruptor->handleEventsWith(eventHandler);
    taskScheduler->start();
    disruptor->start();

    auto ringBuffer = Executor::disruptor_ptr_->ringBuffer();
    MetricEventProducer producer(ringBuffer);

    Executor::disruptor_ptr_ = disruptor;
    Executor::woker.producer = producer;
    Executor::woker.metricExecutor = taskScheduler;
}

void Executor::shutdown()
{
    Executor::disruptor_ptr_->shutdown();
    Executor::woker.metricExecutor->stop();
}

}
}
