#pragma once

#include <QQueue>
#include <QMutex>
#include <QMutexLocker>

constexpr quint32 CIRCULAR_QUEUE_DEFAULT_MAX = 1000;

template <typename T>
class CircularQueue
{
public:
    CircularQueue(quint32 maxSize = CIRCULAR_QUEUE_DEFAULT_MAX)
        : m_maxSize(maxSize)
    {
        if (maxSize <= 0)
            throw std::invalid_argument("Queue size must be positive");
    }

    void enqueue(T item)
    {
        QMutexLocker locker(&m_mutex);

        if (m_queue.size() == m_maxSize)
            m_queue.dequeue();

        m_queue.enqueue(item);
    }

    T dequeue()
    {
        QMutexLocker locker(&m_mutex);

        if (m_queue.isEmpty())
            throw std::runtime_error("Attempt to dequeue from empty ThreadSafeCircularQueue");

        return m_queue.dequeue();

    }

    bool isEmpty() const
    {
        QMutexLocker locker(&m_mutex);
        return m_queue.isEmpty();
    }

    quint32 size() const
    {
        QMutexLocker locker(&m_mutex);
        return m_queue.size();
    }

    quint32 maxSize() const {return m_maxSize;}

    void clear()
    {
        QMutexLocker locker(&m_mutex);
        m_queue.clear();
    }

private:
    const quint32 m_maxSize;
    QQueue<T> m_queue;
    mutable QMutex m_mutex;
};
