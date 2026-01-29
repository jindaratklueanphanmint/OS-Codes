static bool transfer(BankAccount& from, BankAccount& to, double amount) {
    if (&from == &to) return false;
    
    // Use address comparison for consistent ordering
    BankAccount* first = (&from < &to) ? &from : &to;
    BankAccount* second = (&from < &to) ? &to : &from;
    
    std::lock(first->mtx, second->mtx);
    std::lock_guard<std::mutex> lock1(first->mtx, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(second->mtx, std::adopt_lock);
    
    if (from.balance >= amount) {
        from.balance -= amount;
        to.balance += amount;
        std::cout << "Transfer: $" << amount 
                  << " from Account " << from.accountId 
                  << " to Account " << to.accountId << "\n";
        return true;
    }
    return false;
}
