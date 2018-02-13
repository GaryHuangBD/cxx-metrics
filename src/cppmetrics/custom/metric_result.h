#ifndef METRIC_RESULT_H
#define METRIC_RESULT_H

#include <bits/stringfwd.h>

namespace cppmetrics {
namespace custom {
class MetricResult
{
public:
    MetricResult(const std::string &uri,
                 const std::string &metricName,
                 const long &value,
                 const std::string &tagValue)
        : uri_(uri), metricName_(metricName), value_(value), tagValue_(tagValue)
    {}

    virtual ~MetricResult();

    const std::string& uri() const {return uri_;}
    const std::string& metricName() const {return metricName_;}
    const long& value() const {return value_;}
    const std::string& tagValue() const {return tagValue_;}

private:
    std::string uri_;
    std::string metricName_;
    long value_;
    std::string tagValue_;

};

}
}

#endif // METRIC_RESULT_H
