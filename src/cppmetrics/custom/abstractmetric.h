#ifndef ABSTRACTMETRIC_H
#define ABSTRACTMETRIC_H

#include "cppmetrics/core/metric.h"
#include "cppmetrics/custom/metric_value.h"
#include "cppmetrics/custom/metric_result.h"
#include <chrono>
#include <atomic>
#include <bits/stl_deque.h>

namespace cppmetrics {
namespace custom {
class AbstractMetric : public core::Metric {
public:
    AbstractMetric(const std::string &service,
                   const std::string &version,
                   const std::string &uri,
                   const std::string &topic,
                   const long &period,
                   const bool &skipFirst):
        service_(service),
        version_(version),
        uri_(uri),
        topic_(topic),
        period_(period),
        skipFirst_(skipFirst)
    {
        nextPeroid();
    }

    virtual ~AbstractMetric();
    const std::string& service() const {return service_;}
    const std::string& version() const {return version_;}
    const std::string& uri() const {return uri_;}
    const std::string& topic() const {return topic_;}
    const long& peroid() const {return period_;}
    const bool& skipFirst() const {return skipFirst_;}
    void statInner(MetricValuePtr &metricValuePtr);

protected:
    void setStat(bool &stat);
    int addOrContinue(long currentTime, std::deque<std::string> &chunk);
    virtual std::string getType() const = 0;
    virtual void clear();
    virtual void stat(MetricValuePtr &metricValuePtr) = 0;
    virtual void snapValues(std::deque<MetricResult> &results) = 0;

private:
    std::string service_;
    std::string version_;
    std::string uri_;
    std::string topic_;
    long period_;
    bool skipFirst_;
    long nextTime_;
    bool isStat_;
    std::atomic_long refcount_;
    static const std::string SERVER_VIEW;
    static const std::string CONCATOR;

    void nextPeroid();
    void refCountingSnapValues(std::deque<MetricResult> &results);
    int toJsonQueue(std::deque<std::string> &queue);
};

typedef std::shared_ptr<AbstractMetric> AbstractMetricPtr;
}
}
#endif // ABSTRACTMETRIC_H
