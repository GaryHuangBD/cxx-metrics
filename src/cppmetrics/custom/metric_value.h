#ifndef METRIC_VALUE_H
#define METRIC_VALUE_H

#include <bits/shared_ptr.h>


namespace cppmetrics {
namespace custom {

class MetricValue
{
public:
    virtual ~MetricValue() = 0;
};

inline MetricValue::~MetricValue(){}

typedef std::shared_ptr<MetricValue> MetricValuePtr;

}
}
#endif // METRIC_VALUE_H
