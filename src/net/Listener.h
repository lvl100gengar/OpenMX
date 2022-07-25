#pragma once

#include "Connection.h"
#include <functional>

namespace OpenMX {
namespace net {

    /**
     * @brief Base class for Listeners which signal upon receipt of a new result.
     * @tparam TListenResult The result type
     */
    template <typename TListenResult>
    class ListenerBase {
        private:
        using ListenerCallback = std::function<void(TListenResult *)>;
        ListenerCallback m_handler;

        protected:
        ListenerBase() : m_handler([] (TListenResult) {}) {}
        void onResult(TListenResult * result) { m_handler(result); }

        public:
        /**
         * @brief Sets the handler function that will be called when a result is available.
         * @param handler callback function
         */
        void setHandler(ListenerCallback handler) { m_handler(handler ? handler : [] (TListenResult) {}) }
    };

    /**
     * @brief A listener that never signals results.
     */
    class NullListener : public ListenerBase<void> {
    };

    /**
    * @brief A listener that only signals when TestListener::signalResult() is called
    * @tparam TListenResult The result type
    */
    template <typename TListenResult>
    class TestListener: public ListenerBase<TListenResult> {
        public:
        /**
         * @brief Invokes the result callback with the specified result
         * @param result The result that will be passed to the callback
         */
        void signalResult(TListenResult * result) { this->onResult(result); }
    };

    /**
     * @brief Listens for incoming TCP socket connections on a specified endpoint
     */
    class SocketListener : public ListenerBase<Connection> {
    };

    /**
     * @brief Listens for datagrams on a specified UDP port
     * 
     */
    class DatagramListener : public ListenerBase<Connection> {
    };

} // namespace net
} // namespace OpenMX