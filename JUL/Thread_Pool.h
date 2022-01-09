#pragma once

#include <thread> // for std::thread
#include <mutex>  // for std::unique_lock, std::mutex
#include <vector> // for std::vector
#include <queue>  // for std::queue
#include <functional> // for std::function
#include <condition_variable> // for std::conditional_variable

class Thread_Pool {
public:

	using Task = std::function<void()>;

	Thread_Pool(int num_threads) : m_threads(num_threads)
	{
		// limit the number of threads to the max. available
		const int max_available_threads = max_threads();
		auto max_threads = num_threads > max_available_threads ? max_available_threads : num_threads;

		for (int n = 0; n < max_threads; ++n) {
			m_pool.emplace_back([this]() -> void {
				for (;;) {

					Task task;
					{
						// locking
						std::unique_lock<std::mutex> lock(m_mutex);
						m_condition.wait(lock, [this]() -> bool {
							return !m_tasks.empty() || m_shutdown;
							});

						if (m_shutdown && m_tasks.empty()) { return; }

						// fetch next task from queue
						task = std::move(m_tasks.front());
						m_tasks.pop();
					}

					// do the task
					task();
				}});
		}
	}

	~Thread_Pool()
	{
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_shutdown = true;
		}

		m_condition.notify_all();

		for (std::thread& worker : m_pool) {
			worker.join();
		}
	}

	void push_back(Task&& task)
	{
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_tasks.push(task);
		}

		m_condition.notify_one();
	}


	// max. available threads
	int max_threads() const noexcept
	{
		return std::thread::hardware_concurrency() - 1;
	}

private:

	int m_threads = 0;
	std::vector<std::thread> m_pool;
	std::queue<Task> m_tasks;
	std::mutex m_mutex;
	std::condition_variable m_condition;
	bool m_shutdown = false;
};
