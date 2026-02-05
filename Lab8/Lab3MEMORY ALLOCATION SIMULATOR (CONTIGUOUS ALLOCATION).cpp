#include &lt;iostream&gt;
#include &lt;vector&gt;
#include &lt;string&gt;
#include &lt;algorithm&gt;
#include &lt;iomanip&gt;
using namespace std;
struct MemoryBlock {
int startAddress;
int size;
bool isFree;
int processID;
MemoryBlock(int start, int s, bool free = true, int pid = -1)
: startAddress(start), size(s), isFree(free), processID(pid) {}
};
class MemoryManager {
private:
vector&lt;MemoryBlock&gt; blocks;
const int TOTAL_MEMORY = 1048576; // 1MB
void mergeAdjacentFreeBlocks() {
for (size_t i = 0; i &lt; blocks.size() - 1; ) {
if (blocks[i].isFree &amp;&amp; blocks[i + 1].isFree) {
// Merge blocks
blocks[i].size += blocks[i + 1].size;
blocks.erase(blocks.begin() + i + 1);
} else {
i++;
}
}
}
public:
MemoryManager() {
// Initialize with one large free block
blocks.push_back(MemoryBlock(0, TOTAL_MEMORY, true));
}
bool allocateFirstFit(int processID, int size) {
cout &lt;&lt; &quot;\n--- First-Fit Allocation ---&quot; &lt;&lt; endl;
cout &lt;&lt; &quot;Process &quot; &lt;&lt; processID &lt;&lt; &quot; requests &quot; &lt;&lt; size &lt;&lt; &quot; bytes&quot; &lt;&lt; endl;
// Find first block that fits
for (size_t i = 0; i &lt; blocks.size(); i++) {
if (blocks[i].isFree &amp;&amp; blocks[i].size &gt;= size) {
// Found suitable block
cout &lt;&lt; &quot;Found free block at address &quot; &lt;&lt; blocks[i].startAddress
&lt;&lt; &quot; with size &quot; &lt;&lt; blocks[i].size &lt;&lt; endl;
// Allocate from this block
if (blocks[i].size &gt; size) {
// Split the block

int newBlockStart = blocks[i].startAddress + size;
int newBlockSize = blocks[i].size - size;
blocks[i].size = size;
blocks[i].isFree = false;
blocks[i].processID = processID;
// Insert free block after allocated block
blocks.insert(blocks.begin() + i + 1,
MemoryBlock(newBlockStart, newBlockSize, true));
} else {
// Use entire block
blocks[i].isFree = false;
blocks[i].processID = processID;
}
cout &lt;&lt; &quot;Allocated successfully at address &quot;
&lt;&lt; blocks[i].startAddress &lt;&lt; endl;
return true;
}
}
cout &lt;&lt; &quot;Allocation FAILED: No suitable block found&quot; &lt;&lt; endl;
return false;
}
bool allocateBestFit(int processID, int size) {
cout &lt;&lt; &quot;\n--- Best-Fit Allocation ---&quot; &lt;&lt; endl;
cout &lt;&lt; &quot;Process &quot; &lt;&lt; processID &lt;&lt; &quot; requests &quot; &lt;&lt; size &lt;&lt; &quot; bytes&quot; &lt;&lt; endl;
int bestIndex = -1;
int bestSize = TOTAL_MEMORY + 1;
// Find smallest block that fits
for (size_t i = 0; i &lt; blocks.size(); i++) {
if (blocks[i].isFree &amp;&amp; blocks[i].size &gt;= size) {
if (blocks[i].size &lt; bestSize) {
bestSize = blocks[i].size;
bestIndex = i;
}
}
}
if (bestIndex == -1) {
cout &lt;&lt; &quot;Allocation FAILED: No suitable block found&quot; &lt;&lt; endl;
return false;
}
cout &lt;&lt; &quot;Found best-fit block at address &quot; &lt;&lt; blocks[bestIndex].startAddress
&lt;&lt; &quot; with size &quot; &lt;&lt; blocks[bestIndex].size &lt;&lt; endl;
// Allocate from best-fit block
if (blocks[bestIndex].size &gt; size) {
// Split the block
int newBlockStart = blocks[bestIndex].startAddress + size;
int newBlockSize = blocks[bestIndex].size - size;
blocks[bestIndex].size = size;
blocks[bestIndex].isFree = false;
blocks[bestIndex].processID = processID;
blocks.insert(blocks.begin() + bestIndex + 1,
MemoryBlock(newBlockStart, newBlockSize, true));
} else {
blocks[bestIndex].isFree = false;
blocks[bestIndex].processID = processID;

}
cout &lt;&lt; &quot;Allocated successfully at address &quot;
&lt;&lt; blocks[bestIndex].startAddress &lt;&lt; endl;
return true;
}
bool allocateWorstFit(int processID, int size) {
cout &lt;&lt; &quot;\n--- Worst-Fit Allocation ---&quot; &lt;&lt; endl;
cout &lt;&lt; &quot;Process &quot; &lt;&lt; processID &lt;&lt; &quot; requests &quot; &lt;&lt; size &lt;&lt; &quot; bytes&quot; &lt;&lt; endl;
int worstIndex = -1;
int worstSize = -1;
// Find largest block
for (size_t i = 0; i &lt; blocks.size(); i++) {
if (blocks[i].isFree &amp;&amp; blocks[i].size &gt;= size) {
if (blocks[i].size &gt; worstSize) {
worstSize = blocks[i].size;
worstIndex = i;
}
}
}
if (worstIndex == -1) {
cout &lt;&lt; &quot;Allocation FAILED: No suitable block found&quot; &lt;&lt; endl;
return false;
}
cout &lt;&lt; &quot;Found worst-fit block at address &quot; &lt;&lt; blocks[worstIndex].startAddress
&lt;&lt; &quot; with size &quot; &lt;&lt; blocks[worstIndex].size &lt;&lt; endl;
// Allocate from worst-fit block
if (blocks[worstIndex].size &gt; size) {
// Split the block
int newBlockStart = blocks[worstIndex].startAddress + size;
int newBlockSize = blocks[worstIndex].size - size;
blocks[worstIndex].size = size;
blocks[worstIndex].isFree = false;
blocks[worstIndex].processID = processID;
blocks.insert(blocks.begin() + worstIndex + 1,
MemoryBlock(newBlockStart, newBlockSize, true));
} else {
blocks[worstIndex].isFree = false;
blocks[worstIndex].processID = processID;
}
cout &lt;&lt; &quot;Allocated successfully at address &quot;
&lt;&lt; blocks[worstIndex].startAddress &lt;&lt; endl;
return true;
}
void deallocate(int processID) {
cout &lt;&lt; &quot;\n--- Deallocation ---&quot; &lt;&lt; endl;
cout &lt;&lt; &quot;Freeing memory for Process &quot; &lt;&lt; processID &lt;&lt; endl;
bool found = false;
for (size_t i = 0; i &lt; blocks.size(); i++) {
if (!blocks[i].isFree &amp;&amp; blocks[i].processID == processID) {
cout &lt;&lt; &quot;Freed block at address &quot; &lt;&lt; blocks[i].startAddress
&lt;&lt; &quot; with size &quot; &lt;&lt; blocks[i].size &lt;&lt; endl;
blocks[i].isFree = true;
blocks[i].processID = -1;
found = true;

}
}
if (!found) {
cout &lt;&lt; &quot;Process &quot; &lt;&lt; processID &lt;&lt; &quot; not found in memory&quot; &lt;&lt; endl;
return;
}
// Merge adjacent free blocks
mergeAdjacentFreeBlocks();
cout &lt;&lt; &quot;Adjacent free blocks merged&quot; &lt;&lt; endl;
}
void displayMemory() {
cout &lt;&lt; &quot;\n=== MEMORY MAP ===&quot; &lt;&lt; endl;
cout &lt;&lt; setw(12) &lt;&lt; &quot;Start Addr&quot; &lt;&lt; setw(10) &lt;&lt; &quot;Size&quot;
&lt;&lt; setw(10) &lt;&lt; &quot;Status&quot; &lt;&lt; setw(12) &lt;&lt; &quot;Process ID&quot; &lt;&lt; endl;
cout &lt;&lt; string(44, &#39;-&#39;) &lt;&lt; endl;
for (const auto&amp; block : blocks) {
cout &lt;&lt; setw(12) &lt;&lt; block.startAddress
&lt;&lt; setw(10) &lt;&lt; block.size
&lt;&lt; setw(10) &lt;&lt; (block.isFree ? &quot;FREE&quot; : &quot;USED&quot;)
&lt;&lt; setw(12) &lt;&lt; (block.isFree ? &quot;-&quot; : to_string(block.processID))
&lt;&lt; endl;
}
}
void calculateFragmentation() {
int totalFreeSpace = 0;
int largestFreeBlock = 0;
int numFreeBlocks = 0;
int totalAllocatedSpace = 0;
int totalRequestedSpace = 0; // Would need to track this separately
for (const auto&amp; block : blocks) {
if (block.isFree) {
totalFreeSpace += block.size;
numFreeBlocks++;
if (block.size &gt; largestFreeBlock) {
largestFreeBlock = block.size;
}
} else {
totalAllocatedSpace += block.size;
}
}
cout &lt;&lt; &quot;\n=== FRAGMENTATION ANALYSIS ===&quot; &lt;&lt; endl;
cout &lt;&lt; &quot;Total Free Space: &quot; &lt;&lt; totalFreeSpace &lt;&lt; &quot; bytes&quot; &lt;&lt; endl;
cout &lt;&lt; &quot;Largest Free Block: &quot; &lt;&lt; largestFreeBlock &lt;&lt; &quot; bytes&quot; &lt;&lt; endl;
cout &lt;&lt; &quot;Number of Free Blocks: &quot; &lt;&lt; numFreeBlocks &lt;&lt; endl;
cout &lt;&lt; &quot;Total Allocated Space: &quot; &lt;&lt; totalAllocatedSpace &lt;&lt; &quot; bytes&quot; &lt;&lt; endl;
// External Fragmentation: free space that cannot be used
int externalFrag = totalFreeSpace - largestFreeBlock;
cout &lt;&lt; &quot;External Fragmentation: &quot; &lt;&lt; externalFrag &lt;&lt; &quot; bytes&quot; &lt;&lt; endl;
double fragPercent = (totalFreeSpace &gt; 0) ?
(double)externalFrag / totalFreeSpace * 100 : 0;
cout &lt;&lt; &quot;Fragmentation Percentage: &quot; &lt;&lt; fixed &lt;&lt; setprecision(2)
&lt;&lt; fragPercent &lt;&lt; &quot;%&quot; &lt;&lt; endl;
}
};
int main() {
cout &lt;&lt; &quot;MEMORY ALLOCATION SIMULATOR&quot; &lt;&lt; endl;

cout &lt;&lt; &quot;===========================&quot; &lt;&lt; endl;
cout &lt;&lt; &quot;Total Memory: 1 MB (1048576 bytes)&quot; &lt;&lt; endl;
MemoryManager mm;
// Test First-Fit
cout &lt;&lt; &quot;\n\n========== TESTING FIRST-FIT ==========&quot; &lt;&lt; endl;
mm.allocateFirstFit(1, 200000);
mm.allocateFirstFit(2, 150000);
mm.allocateFirstFit(3, 300000);
mm.displayMemory();
mm.deallocate(2);
mm.displayMemory();
mm.allocateFirstFit(4, 100000);
mm.displayMemory();
mm.calculateFragmentation();
// Reset for Best-Fit test
cout &lt;&lt; &quot;\n\n========== TESTING BEST-FIT ==========&quot; &lt;&lt; endl;
MemoryManager mm2;
mm2.allocateBestFit(1, 200000);
mm2.allocateBestFit(2, 150000);
mm2.allocateBestFit(3, 300000);
mm2.displayMemory();
mm2.deallocate(2);
mm2.allocateBestFit(4, 100000);
mm2.displayMemory();
mm2.calculateFragmentation();
// Reset for Worst-Fit test
cout &lt;&lt; &quot;\n\n========== TESTING WORST-FIT ==========&quot; &lt;&lt; endl;
MemoryManager mm3;
mm3.allocateWorstFit(1, 200000);
mm3.allocateWorstFit(2, 150000);
mm3.allocateWorstFit(3, 300000);
mm3.displayMemory();
mm3.deallocate(2);
mm3.allocateWorstFit(4, 100000);
mm3.displayMemory();
mm3.calculateFragmentation();
return 0;
}
