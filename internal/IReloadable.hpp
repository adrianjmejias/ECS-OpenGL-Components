#include <future>

class IReloadable{
    template <class TT>
    std::future<TT> Reload() = 0;
};