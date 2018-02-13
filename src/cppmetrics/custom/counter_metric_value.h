#ifndef COUNTER_METRIC_VALUE_H
#define COUNTER_METRIC_VALUE_H

#include "cppmetrics/custom/metric_value.h"


namespace cppmetrics {
namespace custom {
class CounterMetricValue : public MetricValue
{
public:
    CounterMetricValue(const long &count = 0) : count_(count){}
    virtual ~CounterMetricValue();
    const long& count() const {return count_;}

private:
    long count_;
};

inline CounterMetricValue::~CounterMetricValue() {}


typedef std::shared_ptr<CounterMetricValue> CounterMetricValuePtr;

}
}


#endif // COUNTER_METRIC_VALUE_H
