#ifndef METRIC_EVENT_PRODUCER_H
#define METRIC_EVENT_PRODUCER_H

#include "cppmetrics/custom/abstractmetric.h"
#include "Disruptor/RingBuffer.h"


namespace cppmetrics {
namespace exec {

struct MetricWrap{
    custom::AbstractMetricPtr metricPtr;
    custom::MetricValuePtr metricValuePtr;
};

class MetricEventProducer{
public:
    MetricEventProducer(std::shared_ptr<Disruptor::RingBuffer<MetricWrap> > ringbufferPtr) :
        ringbufferPtr_(ringbufferPtr)
    {}

    virtual ~MetricEventProducer();

    void onData(MetricWrap event)
    {
        auto nextSequence = ringbufferPtr_->next();
        (*ringbufferPtr_)[nextSequence].metricPtr = event.metricPtr;
        (*ringbufferPtr_)[nextSequence].metricValuePtr = event.metricValuePtr;
        ringbufferPtr_->publish(nextSequence);
    }

private:
    std::shared_ptr<Disruptor::RingBuffer<MetricWrap> > ringbufferPtr_;
};

inline MetricEventProducer::~MetricEventProducer() {}

}

}
#endif // METRIC_EVENT_PRODUCER_H
