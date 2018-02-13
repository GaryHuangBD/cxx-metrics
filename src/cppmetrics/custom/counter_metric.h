#ifndef COUNTER_METRIC_H
#define COUNTER_METRIC_H

#include "cppmetrics/custom/abstractmetric.h"


namespace cppmetrics {
namespace custom {

class CounterMetric : public AbstractMetric {
public:
    void inc();
    void inc(long n);
    void dec();
    void dec(long n);

protected:
    void stat(long n);
    const long count() const {return count_;}
    virtual void stat(MetricValuePtr &metricValuePtr);
    virtual void snapValues(std::deque<MetricResult> &results);
    virtual void clear();

private:
    std::atomic_long count_;
    static const std::string TYPE;
};

typedef std::shared_ptr<CounterMetric> CounterMetricPtr;

}
}

#endif // COUNTER_METRIC_H
