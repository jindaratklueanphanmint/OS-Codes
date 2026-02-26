#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;
// == == == == == == == == == == == == == == == == == == == == == ==
// TODO 1 : Performance Metrics Structure / == == == == == == == == == == == == == == == == == == == == == ==
struct IOMetrics
{
    string testName;
    double throughput;
    double latency;
    double iops;
    // bytes per second / milliseconds / I / O operations per second long long totalBytes;
    int totalOperations;
    double duration;
    // seconds void display()
    {
        cout << "\n=== " << testName << " ===" << endl;
        cout << fixed << setprecision(2);
        cout << "Throughput:   " << throughput / 1024 / 1024 << " MB/s" << endl;
        cout << "Latency:      " << latency << " ms" << endl;
        cout << "IOPS:         " << iops << " ops/sec" << endl;
        cout << "Total Data:   " << totalBytes / 1024 << " KB" << endl;
        cout << "Operations:   " << totalOperations << endl;
        cout << "Duration:     " << duration << " sec" << endl;
    }
};

// ============================================
// TODO 2: Simulated Disk Drive
// ============================================
class SimulatedDisk
{
private:
    vector<vector<uint8_t>> sectors;
    size_t sectorSize;
    size_t numSectors;
    int currentHead; // current disk head position
    int seekTimeMs;  // ms per track
    int rotationalLatencyMs;

    // จ ำลอง seek time
    int calculateSeekTime(int targetSector)
    {
        int tracks = abs(targetSector - currentHead) / 100;
        return tracks * seekTimeMs + rotationalLatencyMs;
    }

public:
    SimulatedDisk(size_t sectorSz, size_t numSect,
                  int seekMs = 1, int rotMs = 1)
        : sectorSize(sectorSz), numSectors(numSect),
          currentHead(0), seekTimeMs(seekMs), rotationalLatencyMs(rotMs)
    {
        sectors.resize(numSectors, vector<uint8_t>(sectorSize, 0));
    }

    // TODO: Sequential Write
    double sequentialWrite(size_t numOps)
    {
        auto start = chrono::high_resolution_clock::now();

        for (size_t i = 0; i < numOps && i < numSectors; i++)
        {
            // Sequential: head เคลื่อนที่น้อย
            currentHead = i;
            vector<uint8_t> data(sectorSize, static_cast<uint8_t>(i % 256));
            sectors[i] = data;
        }

        auto end = chrono::high_resolution_clock::now();
        return chrono::duration<double>(end - start).count();
    }

    // TODO: Sequential Read
    double sequentialRead(size_t numOps)
    {
        auto start = chrono::high_resolution_clock::now();

        for (size_t i = 0; i < numOps && i < numSectors; i++)
        {
            currentHead = i;
            volatile uint8_t dummy = sectors[i][0]; // prevent optimization
            (void)dummy;
        }

        auto end = chrono::high_resolution_clock::now();
        return chrono::duration<double>(end - start).count();
    }

    // TODO: Random Write (จ ำลอง seek time)
    double randomWrite(size_t numOps)
    {
        auto start = chrono::high_resolution_clock::now();

        srand(42); // fixed seed for reproducibility
        for (size_t i = 0; i < numOps; i++)
        {
            size_t target = rand() % numSectors;
            // จ ำลอง seek time (ใน real disk จะมี delay)
            currentHead = target;
            vector<uint8_t> data(sectorSize, static_cast<uint8_t>(i % 256));
            sectors[target] = data;
        }

        auto end = chrono::high_resolution_clock::now();
        return chrono::duration<double>(end - start).count();
    }

    // TODO: Random Read
    double randomRead(size_t numOps)
    {
        auto start = chrono::high_resolution_clock::now();

        srand(42);
        for (size_t i = 0; i < numOps; i++)
        {
            size_t target = rand() % numSectors;
            currentHead = target;
            volatile uint8_t dummy = sectors[target][0];
            (void)dummy;
        }

        auto end = chrono::high_resolution_clock::now();
        return chrono::duration<double>(end - start).count();
    }

    size_t getSectorSize() { return sectorSize; }
};

// ============================================
// TODO 3: Buffer Size Impact Test
// ============================================
class BufferTest
{
public:
    // TODO: ทดสอบผลกระทบของ buffer size ต่อ performance
    static IOMetrics testBufferSize(size_t bufferSize, size_t totalData)
    {
        IOMetrics metrics;
        metrics.testName = "Buffer Size: " + to_string(bufferSize) + " bytes";

        vector<uint8_t> src(totalData);
        vector<uint8_t> dst(totalData, 0);

        // เติมข้อมูล
        for (size_t i = 0; i < totalData; i++)
            src[i] = i % 256;

        auto start = chrono::high_resolution_clock::now();

        size_t ops = 0;
        for (size_t offset = 0; offset < totalData; offset += bufferSize)
        {
            size_t copySize = min(bufferSize, totalData - offset);
            memcpy(dst.data() + offset, src.data() + offset, copySize);
            ops++;
        }

        auto end = chrono::high_resolution_clock::now();
        metrics.duration = chrono::duration<double>(end - start).count();
        metrics.totalBytes = totalData;
        metrics.totalOperations = ops;
        metrics.throughput = totalData / metrics.duration;
        metrics.latency = (metrics.duration / ops) * 1000.0;
        metrics.iops = ops / metrics.duration;

        return metrics;
    }
};

// ============================================
// TODO 4: Asynchronous vs Synchronous I/O
// ============================================
class AsyncIOTest
{
public:
    // Synchronous I/O (blocking)
    static double synchronousIO(vector<uint8_t> &buffer, int iterations)
    {
        auto start = chrono::high_resolution_clock::now();

        volatile uint64_t sum = 0;
        for (int i = 0; i < iterations; i++)
        {
            // จ ำลอง blocking read
            for (size_t j = 0; j < buffer.size(); j++)
            {
                sum += buffer[j]; // CPU ต้องรอ I/O
            }
        }
        (void)sum;

        auto end = chrono::high_resolution_clock::now();
        return chrono::duration<double>(end - start).count();
    }

    // Asynchronous I/O (non-blocking simulation)
    static double asynchronousIO(vector<uint8_t> &buffer, int iterations)
    {
        auto start = chrono::high_resolution_clock::now();

        // จ ำลอง async: เตรียม I/O request แล้วท ำงำนอื่น
        volatile uint64_t sum = 0;
        volatile uint64_t computeResult = 0;

        for (int i = 0; i < iterations; i++)
        {
            // Phase 1: Submit I/O request (non-blocking)
            // Phase 2: Do other computation while waiting
            for (int c = 0; c < 100; c++)
            { // other work
                computeResult += c * c;
            }
            // Phase 3: Collect I/O result
            for (size_t j = 0; j < buffer.size(); j++)
            {
                sum += buffer[j];
            }
        }
        (void)sum;
        (void)computeResult;

        auto end = chrono::high_resolution_clock::now();
        return chrono::duration<double>(end - start).count();
    }
};

// ============================================
// TODO 5: Performance Report Generator
// ============================================
class PerformanceReport
{
private:
    vector<IOMetrics> results;

public:
    void addResult(IOMetrics m)
    {
        results.push_back(m);
    }

    void generateReport()
    {
        cout << "\n";
        cout << "╔════════════════════════════════════════════
 ══════════════════╗" << endl; 
            cout
             << "║              I/O PERFORMANCE REPORT                         ║" << endl;
        cout << "╠════════════════════════════════════════════
 ══════════════════╣" << endl; 
            cout
             << left << setw(25) << "║ Test Name"
             << right << setw(12) << "MB/s"
             << setw(12) << "Latency(ms)"
             << setw(12) << "IOPS"
             << "   ║" << endl;
        cout << "╠════════════════════════════════════════════
 ══════════════════╣" << endl; 

            for (auto &m : results)
        {
            cout << "║ " << left << setw(23) << m.testName
                 << right << fixed << setprecision(2)
                 << setw(12) << m.throughput / 1024 / 1024
                 << setw(12) << m.latency
                 << setw(12) << (int)m.iops
                 << "   ║" << endl;
        }

        cout << "╚════════════════════════════════════════════
 ══════════════════╝" << endl; 
    }

    // TODO: หำ best และ worst performer
    void analyzeBestWorst()
    {
        if (results.empty())
            return;

        auto best = max_element(results.begin(), results.end(),
                                [](const IOMetrics &a, const IOMetrics &b)
                                {
                                    return a.throughput < b.throughput;
                                });

        auto worst = min_element(results.begin(), results.end(),
                                 [](const IOMetrics &a, const IOMetrics &b)
                                 {
                                     return a.throughput < b.throughput;
                                 });

        cout << "\n       Best Throughput:  " << best->testName
             << " (" << fixed << setprecision(2)
             << best->throughput / 1024 / 1024 << " MB/s)" << endl;
        cout << "     Worst Throughput: " << worst->testName
             << " (" << fixed << setprecision(2)
             << worst->throughput / 1024 / 1024 << " MB/s)" << endl;
    }
};
int main()
{
    cout << "=== I/O Performance Measurement ===" << endl;
    PerformanceReport report;
    // ===== DISK PERFORMANCE TEST =====
    cout << "\n=== Disk I/O Performance ===" << endl;
    SimulatedDisk disk(512, 10000);
    const size_t NUM_OPS = 5000;
    // Sequential Write
    cout << "Testing Sequential Write..." << endl;
    double seqWriteTime = disk.sequentialWrite(NUM_OPS);
    IOMetrics seqWrite;
    seqWrite.testName = "Seq Write";
    seqWrite.totalBytes = NUM_OPS * disk.getSectorSize();
    seqWrite.totalOperations = NUM_OPS;
    seqWrite.duration = seqWriteTime;
    seqWrite.throughput = seqWrite.totalBytes / seqWriteTime;
    seqWrite.latency = (seqWriteTime / NUM_OPS) * 1000.0;
    seqWrite.iops = NUM_OPS / seqWriteTime;
    report.addResult(seqWrite);
    seqWrite.display();
    // Sequential Read
    cout << "Testing Sequential Read..." << endl;
    double seqReadTime = disk.sequentialRead(NUM_OPS);
    IOMetrics seqRead;
    seqRead.testName = "Seq Read";
    seqRead.totalBytes = NUM_OPS * disk.getSectorSize();
    seqRead.totalOperations = NUM_OPS;
    seqRead.duration