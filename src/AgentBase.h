#ifndef _PATH_FINDING_AGENT_BASE_H_
#define _PATH_FINDING_AGENT_BASE_H_

#include <string>
#include <string_view>

namespace path_finding {

class AgentBase {
public:
    AgentBase(std::string_view name);
    virtual ~AgentBase() = default;

    virtual void update() = 0;
    virtual void render() = 0;
    virtual void reset() {}

private:
    std::string name_;
};

} // namespace path_finding

#endif
