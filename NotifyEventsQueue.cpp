#include "NotifyEventsQueue.hpp"


bool NotifyEventsQueue::handleMsg(std::string notifyType)
{
    // Wait for a message to be added to the queue
    std::unique_lock<std::mutex> lk(mMutex);

    if (mQueue.empty()) {
        MM_LOGE("NotifyEventsQueue handleMsg msg queue empty");
        return false;
    }

    NotifyEventsMessage msg = mQueue.front();
    for (auto & v : msg.mNotificationData.appStates) {
        MM_LOGI("NotifyEventsQueue handleMsg -------- url: %s", v.first.c_str());
    }
    MM_LOGI("NotifyEventsQueue handleMsg  -------- queue size: %d",  mQueue.size());

    if (notifyType != msg.mNotifyType) {
        MM_LOGE("NotifyEventsQueue handleMsg notifyType not match, notifyType: %s, msg->mNotifyType: %s", notifyType.c_str(), msg.mNotifyType.c_str());
        return false;
    }
    bool res = mCallback(msg.mNotificationData); 
    MM_LOGI("NotifyEventsQueue handleMsg done --------, mNotifyType: %s, queuesize: %d", msg.mNotifyType.c_str(), mQueue.size());
    mQueue.pop();
    return res;
}

void NotifyEventsQueue::clear()
{
    std::unique_lock<std::mutex> lk(mMutex);
    std::queue<NotifyEventsMessage> empty;
    std::swap(mQueue, empty);
}

void NotifyEventsQueue::postMsg(NotifyEventsMessage notifyEventsMsg)
{
    // Create a new ThreadMsg
    NotifyEventsMessage msg = notifyEventsMsg;

    // Add user data msg to queue and notify worker thread
    std::unique_lock<std::mutex> lk(mMutex);
    for (auto & v : msg.mNotificationData.appStates) {
        MM_LOGI("NotifyEventsQueue postMsg -------- url: %s", v.first.c_str());
    }
    MM_LOGI("NotifyEventsQueue postMsg done -------- queue size: %d", mQueue.size());
    mQueue.push(msg);
    mCondition.notify_one();
}

void NotifyEventsQueue::setEventsCallback(std::function<bool(NotificationData notifyData)> cb) {
    mCallback = cb;
    return;
}
