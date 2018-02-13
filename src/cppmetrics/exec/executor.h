#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "Disruptor/ThreadPerTaskScheduler.h"
#include "Disruptor/Disruptor.h"
#include "metric_event_producer.h"



namespace cppmetrics {
namespace exec {

typedef std::shared_ptr<Disruptor::disruptor<MetricWrap>> DisruptorPtr;
typedef std::shared_ptr<Disruptor::ThreadPerTaskScheduler> TaskSchedulerPtr;

struct Worker
{
    MetricEventProducer producer;
    TaskSchedulerPtr metricExecutor;
};

class Executor {
public:
    static Worker woker;
    static void shutdown();
    virtual ~Executor();
private:
    Executor()
    {
        creatWorker();
    }
    static DisruptorPtr disruptor_ptr_;
    static void creatWorker();

};

inline Executor::~Executor(){}

}
}
#endif // EXECUTOR_H
