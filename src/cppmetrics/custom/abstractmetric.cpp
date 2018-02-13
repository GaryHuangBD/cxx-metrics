#include "cppmetrics/custom/abstractmetric.h"

namespace cppmetrics {
namespace custom {

const std::string AbstractMetric::SERVER_VIEW = "serverMetrics";
const std::string AbstractMetric::CONCATOR = "-";

AbstractMetric::~AbstractMetric(){}

void AbstractMetric::nextPeroid()
{
    long now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    nextTime_ = now - now % period_ + period_;
}

void AbstractMetric::setStat(bool &isStat)
{
    isStat_ = true;
}

void AbstractMetric::statInner(MetricValuePtr &metricValuePtr)
{
    stat(metricValuePtr);
    isStat_ = true;
}

int AbstractMetric::addOrContinue(long currentTime, std::deque<std::string> &chunk)
{
    if (currentTime >= nextTime_)
    {
        int count = toJsonQueue(chunk);
        nextPeroid();
        return count;
    }
    return 0;
}

void AbstractMetric::refCountingSnapValues(std::deque<MetricResult> &results)
{
    if(isStat_)
    {
        refcount_ += 1;
        snapValues(results);
        isStat_ = false;
    }
}

int AbstractMetric::toJsonQueue(std::deque<std::string> &queue)
{
    std::deque<MetricResult> results;
    snapValues(results);
    long timestamp = (nextTime_ - period_)/1000;
    long _peroid = peroid()/1000;
    for(unsigned int i = 0; i < results.size(); ++i)
    {
        auto value = results.at(i);
        std::string ss;
        std::string _topic = topic().empty()
                ? value.metricName()
                : topic() + CONCATOR + value.metricName();
        ss.append("{")
                .append("\"view\": ").append("\"").append(SERVER_VIEW).append("\", ")
                .append("\"service\": ").append("\"").append(service()).append("\", ")
                .append("\"uri\": ").append("\"").append(value.uri()).append("\", ")
                .append("\"topic\": ").append("\"").append(_topic).append("\", ")
                .append("\"timestamp\": " + timestamp).append(", ")
                .append("\"step\": " + _peroid).append(", ")
                .append("\"value\": " + value.value()).append(", ")
                .append("\"tags\": ")
                .append("\"version=").append(version());

        if (!value.tagValue().empty()) {
            ss.append(",type")
                    .append("=")
                    .append(value.tagValue());
        }
        ss.append("\"");
        ss.append("}");
        queue.push_back(ss);
    }
    return results.size();
}

}

}
