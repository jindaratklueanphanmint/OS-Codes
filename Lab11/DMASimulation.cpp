#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
using namespace std;

// TODO 1 : จ ำลอง Memory class Memory
class Memory
{
private:
    vector<uint8_t> data;
    size_t size;

public:
    Memory(size_t size) : size(size), data(size, 0) {}

    // TODO: เขียน read() และ write() methods
    void write(size_t address, uint8_t value)
    {
        // เช็ค bounds แล้ว write
    }

    uint8_t read(size_t address)
    {
        // เช็ค bounds แล้ว return value
    }

    void display(size_t start, size_t length)
    {
        // แสดงค่ำใน memory
    }
};

// TODO 2: จ ำลอง Programmed I/O (CPU ต้องท ำทุก byte)
class ProgrammedIO
{
private:
    int cpuCyclesUsed;

public:
    ProgrammedIO() : cpuCyclesUsed(0) {}

    long long transfer(Memory &mem, size_t destAddr,
                       vector<uint8_t> &source, size_t size)
    {
        auto start = chrono::high_resolution_clock::now();

        cout << "[PIO] CPU transferring " << size << " bytes..." << endl;

        for (size_t i = 0; i < size; i++)
        {
            // TODO: จ ำลอง CPU copy ทีละ byte
            // เพม cpuCyclesUsed
            mem.write(destAddr + i, source[i]);
            cpuCyclesUsed++;
        }

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

        cout << "[PIO] Complete. CPU cycles used: " << cpuCyclesUsed << endl;
        return duration;
    }
};

// TODO 3: จ ำลอง DMA Controller
class DMAController
{
private:
    uint32_t sourceAddress;
    uint32_t destAddress;
    uint32_t transferCount;
    bool busy;
    int cpuCyclesUsed; // DMA ใช้ CPU cycles น้อยมำก

public:
    DMAController() : busy(false), cpuCyclesUsed(0) {}

    // TODO: เขียน setup() สำหรบตงคำ DMA
    void setup(uint32_t src, uint32_t dest, uint32_t count)
    {
        // ตงคำ source, destination, และ count
    }

    // TODO: เขียน transfer() ที่จ ำลอง DMA transfer
    long long transfer(Memory &mem, vector<uint8_t> &source)
    {
        auto start = chrono::high_resolution_clock::now();

        busy = true;
        cout << "[DMA] Starting transfer of " << transferCount << " bytes..." << endl;
        cout << "[DMA] CPU is FREE to do other work!" << endl;

        // TODO: จ ำลอง DMA transfer (CPU cycles น้อยกว่ำ PIO มำก)
        // DMA ใช้ CPU cycles แค่ตอน setup และ interrupt เทำนน
        cpuCyclesUsed = 2; // setup + interrupt

        for (uint32_t i = 0; i < transferCount; i++)
        {
            mem.write(destAddress + i, source[sourceAddress + i]);
        }

        busy = false;
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

        cout << "[DMA] Transfer complete! CPU cycles used: " << cpuCyclesUsed << endl;
        cout << "[DMA] CPU interrupt sent to notify completion" << endl;
        return duration;
    }
};

int main()
{
    cout << "=== DMA vs Programmed I/O Comparison ===" << endl;

    const size_t DATA_SIZE = 1024; // 1KB
    Memory memory(4096);

    vector<uint8_t> sourceData(DATA_SIZE);
    for (size_t i = 0; i < DATA_SIZE; i++)
    {
        sourceData[i] = static_cast<uint8_t>(i % 256);
    }

    // TODO: ทดสอบ Programmed I/O
    cout << "\n=== Programmed I/O ===" << endl;
    ProgrammedIO pio;
    long long pioTime = pio.transfer(memory, 0, sourceData, DATA_SIZE);

    // TODO: ทดสอบ DMA
    cout << "\n=== DMA Transfer ===" << endl;
    Memory memory2(4096);
    DMAController dma;
    dma.setup(0, 0, DATA_SIZE);
    long long dmaTime = dma.transfer(memory2, sourceData);
    // TODO: เปรียบเทียบผล
    cout << "\n=== Performance Comparison ===" << endl;
    cout << "PIO Time: " << pioTime << " microseconds" << endl;
    cout << "DMA Time: " << dmaTime << " microseconds" << endl;
    return 0;
}