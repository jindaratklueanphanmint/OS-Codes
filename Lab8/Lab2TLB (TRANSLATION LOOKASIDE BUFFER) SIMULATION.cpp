#include &lt;iostream&gt;
#include &lt;list&gt;
#include &lt;unordered_map&gt;
#include &lt;iomanip&gt;
using namespace std;
const int TLB_SIZE = 8;
class TLB {
private:
struct TLBEntry {
int pageNumber;
int frameNumber;
TLBEntry(int p, int f) : pageNumber(p), frameNumber(f) {}
};
list&lt;TLBEntry&gt; tlbCache; // Most recently used at front
unordered_map&lt;int, list&lt;TLBEntry&gt;::iterator&gt; tlbMap;
int hits;
int misses;
public:
TLB() : hits(0), misses(0) {}
int lookup(int pageNumber) {
// Search for page in TLB
auto it = tlbMap.find(pageNumber);
if (it != tlbMap.end()) {
// TLB Hit!
hits++;
int frameNumber = it-&gt;second-&gt;frameNumber;
// Move to front (LRU - most recently used)
tlbCache.splice(tlbCache.begin(), tlbCache, it-&gt;second);
cout &lt;&lt; &quot;TLB HIT: Page &quot; &lt;&lt; pageNumber
&lt;&lt; &quot; -&gt; Frame &quot; &lt;&lt; frameNumber &lt;&lt; endl;
return frameNumber;
} else {
// TLB Miss
misses++;

cout &lt;&lt; &quot;TLB MISS: Page &quot; &lt;&lt; pageNumber &lt;&lt; &quot; not in TLB&quot; &lt;&lt; endl;
return -1;
}
}
void insert(int pageNumber, int frameNumber) {
// Check if already in TLB
if (tlbMap.find(pageNumber) != tlbMap.end()) {
// Update existing entry and move to front
auto it = tlbMap[pageNumber];
it-&gt;frameNumber = frameNumber;
tlbCache.splice(tlbCache.begin(), tlbCache, it);
return;
}
// If TLB is full, remove LRU entry (back of list)
if (tlbCache.size() &gt;= TLB_SIZE) {
int removedPage = tlbCache.back().pageNumber;
cout &lt;&lt; &quot;TLB FULL: Removing page &quot; &lt;&lt; removedPage &lt;&lt; &quot; (LRU)&quot; &lt;&lt; endl;
tlbMap.erase(removedPage);
tlbCache.pop_back();
}
// Add new entry to front
tlbCache.push_front(TLBEntry(pageNumber, frameNumber));
tlbMap[pageNumber] = tlbCache.begin();
cout &lt;&lt; &quot;TLB INSERT: Page &quot; &lt;&lt; pageNumber
&lt;&lt; &quot; -&gt; Frame &quot; &lt;&lt; frameNumber &lt;&lt; endl;
}
void displayTLB() {
cout &lt;&lt; &quot;\n=== TLB Contents (MRU to LRU) ===&quot; &lt;&lt; endl;
cout &lt;&lt; setw(10) &lt;&lt; &quot;Page#&quot; &lt;&lt; setw(10) &lt;&lt; &quot;Frame#&quot; &lt;&lt; endl;
cout &lt;&lt; string(20, &#39;-&#39;) &lt;&lt; endl;
for (const auto&amp; entry : tlbCache) {
cout &lt;&lt; setw(10) &lt;&lt; entry.pageNumber
&lt;&lt; setw(10) &lt;&lt; entry.frameNumber &lt;&lt; endl;
}
}
void displayStats() {
int total = hits + misses;
double hitRatio = (total &gt; 0) ? (double)hits / total * 100 : 0;
cout &lt;&lt; &quot;\n=== TLB STATISTICS ===&quot; &lt;&lt; endl;
cout &lt;&lt; &quot;Total Accesses: &quot; &lt;&lt; total &lt;&lt; endl;
cout &lt;&lt; &quot;Hits: &quot; &lt;&lt; hits &lt;&lt; endl;
cout &lt;&lt; &quot;Misses: &quot; &lt;&lt; misses &lt;&lt; endl;
cout &lt;&lt; &quot;Hit Ratio: &quot; &lt;&lt; fixed &lt;&lt; setprecision(2)
&lt;&lt; hitRatio &lt;&lt; &quot;%&quot; &lt;&lt; endl;
}
void reset() {
hits = 0;
misses = 0;
}
};
// Combined with Page Table
class MemorySystem {
private:
TLB tlb;
unordered_map&lt;int, int&gt; pageTable; // page -&gt; frame mapping

public:
MemorySystem() {
// Initialize some page table entries
pageTable[0] = 5;
pageTable[1] = 2;
pageTable[2] = 8;
pageTable[3] = 1;
pageTable[4] = 9;
pageTable[5] = 3;
pageTable[6] = 7;
pageTable[7] = 4;
}
int translateAddress(int pageNumber) {
cout &lt;&lt; &quot;\n--- Translating Page &quot; &lt;&lt; pageNumber &lt;&lt; &quot; ---&quot; &lt;&lt; endl;
// First check TLB
int frame = tlb.lookup(pageNumber);
if (frame == -1) {
// TLB miss - check page table
if (pageTable.find(pageNumber) != pageTable.end()) {
frame = pageTable[pageNumber];
cout &lt;&lt; &quot;Page Table Lookup: Page &quot; &lt;&lt; pageNumber
&lt;&lt; &quot; -&gt; Frame &quot; &lt;&lt; frame &lt;&lt; endl;
// Insert into TLB
tlb.insert(pageNumber, frame);
} else {
cout &lt;&lt; &quot;PAGE FAULT: Page &quot; &lt;&lt; pageNumber
&lt;&lt; &quot; not in memory!&quot; &lt;&lt; endl;
return -1;
}
}
return frame;
}
void displayStatus() {
tlb.displayTLB();
tlb.displayStats();
}
};
int main() {
cout &lt;&lt; &quot;TLB SIMULATION&quot; &lt;&lt; endl;
cout &lt;&lt; &quot;==============&quot; &lt;&lt; endl;
cout &lt;&lt; &quot;TLB Size: &quot; &lt;&lt; TLB_SIZE &lt;&lt; &quot; entries&quot; &lt;&lt; endl;
cout &lt;&lt; &quot;Replacement Policy: LRU&quot; &lt;&lt; endl &lt;&lt; endl;
MemorySystem memSys;
// Simulate page references
int referenceString[] = {0, 1, 2, 3, 0, 1, 4, 0, 1, 2, 3, 5, 6, 7, 0, 1};
int numReferences = sizeof(referenceString) / sizeof(referenceString[0]);
cout &lt;&lt; &quot;Reference String: &quot;;
for (int i = 0; i &lt; numReferences; i++) {
cout &lt;&lt; referenceString[i] &lt;&lt; &quot; &quot;;
}
cout &lt;&lt; &quot;\n&quot; &lt;&lt; endl;
// Process each reference
for (int i = 0; i &lt; numReferences; i++) {
memSys.translateAddress(referenceString[i]);
}

// Display final status
memSys.displayStatus();
return 0;
}
