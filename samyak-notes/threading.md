# Threading

topics that this doc will cover:
- std::thread, std::jthread, stop_token, and passing arguments with std::ref

std::thread needs to be .join()'d before destroying it. this call will block if necessary intil the other threads job is ifnished

threads will start right away

in a case where threads are racing to read / write to the same memory address, we have a "physical data race" which causes UB. however, if we use an atomic<T> to reprenset the same, we will nto have a phsycial data race hence no UB. should be noted that this can produce different outputs, but which is bug but not UB

every access to atomic implictly synchronizes

we must follow RAII prinicples. in a case where an exception is thrown while the lock was acquired, the lock is never released hence halting all execution

RAII pinciples = every "cleanup" action including unlocking mutex, should be done in descrturstor

std::lock_guard<std::mutex>, will fix this for us

std::scoped_lock is the newest addition, and they cna use multiple locks for the scope
std::unique_lock is move-able
 
std::condition_variable, works the same way as C
we also have notify_one and notify_all 

static variables for thread safe initialization! if not static, then use once_flag