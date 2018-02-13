
#include "cppmetrics/custom/counter_metric.h"
#include "cppmetrics/custom/counter_metric_value.h"

namespace cppmetrics {
namespace custom {

const std::string CounterMetric::TYPE = "count";

void CounterMetric::inc()
{
}

void CounterMetric::inc(long n)
{
}

void CounterMetric::dec()
{
}

void CounterMetric::dec(long n)
{
}

void CounterMetric::stat(MetricValuePtr &valuePtr)
{
    CounterMetricValuePtr counter_value_ptr = std::static_pointer_cast<CounterMetricValue>(valuePtr);
    stat(counter_value_ptr->count());
}

void CounterMetric::stat(long n)
{
    count_ += n;
    bool _isStat = true;
    setStat(_isStat);
}

void CounterMetric::snapValues(std::deque<MetricResult> &results)
{
    MetricResult _value(uri(), TYPE, count(), "");
    results.push_back(_value);
}

void CounterMetric::clear()
{
    count_ = 0;
}

}
}
