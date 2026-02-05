#include &lt;iostream&gt;
#include &lt;iomanip&gt;
#include &lt;cstdlib&gt;
#include &lt;ctime&gt;
#include &lt;bitset&gt;
using namespace std;
const int NUM_PAGES = 64;
const int NUM_FRAMES = 32;
const int PAGE_SIZE = 1024;
const int OFFSET_BITS = 10; // log2(1024) = 10 bits for offset
const int PAGE_BITS = 6; // log2(64) = 6 bits for page number
class PageTable {
private:
int pageTable[NUM_PAGES];
bool valid[NUM_PAGES];
public:
PageTable() {
srand(time(0));
bool usedFrames[NUM_FRAMES] = {false};
// Initialize page table with random frame numbers
for (int i = 0; i &lt; NUM_PAGES; i++) {
// 75% of pages are valid
if (rand() % 100 &lt; 75) {
int frame;
// Find an unused frame
do {
frame = rand() % NUM_FRAMES;
} while (usedFrames[frame]);
pageTable[i] = frame;
usedFrames[frame] = true;
valid[i] = true;
} else {
pageTable[i] = -1;
valid[i] = false;
}
}
}
int translateAddress(int logicalAddress) {
// Extract page number (upper bits)
int pageNumber = logicalAddress / PAGE_SIZE;

// Extract offset (lower bits)
int offset = logicalAddress % PAGE_SIZE;
// Validate page number
if (pageNumber &lt; 0 || pageNumber &gt;= NUM_PAGES) {
cout &lt;&lt; &quot;Error: Invalid page number &quot; &lt;&lt; pageNumber &lt;&lt; endl;
return -1;
}
// Check if page is valid
if (!valid[pageNumber]) {
cout &lt;&lt; &quot;Page Fault: Page &quot; &lt;&lt; pageNumber &lt;&lt; &quot; is not in memory&quot; &lt;&lt; endl;
return -1;
}
// Get frame number from page table
int frameNumber = pageTable[pageNumber];
// Calculate physical address
int physicalAddress = (frameNumber * PAGE_SIZE) + offset;
// Display translation details
cout &lt;&lt; &quot;Logical Address: &quot; &lt;&lt; logicalAddress &lt;&lt; endl;
cout &lt;&lt; &quot; Page Number: &quot; &lt;&lt; pageNumber &lt;&lt; endl;
cout &lt;&lt; &quot; Offset: &quot; &lt;&lt; offset &lt;&lt; endl;
cout &lt;&lt; &quot; Frame Number: &quot; &lt;&lt; frameNumber &lt;&lt; endl;
cout &lt;&lt; &quot;Physical Address: &quot; &lt;&lt; physicalAddress &lt;&lt; endl;
return physicalAddress;
}
void displayPageTable() {
cout &lt;&lt; &quot;\n=== PAGE TABLE ===&quot; &lt;&lt; endl;
cout &lt;&lt; setw(10) &lt;&lt; &quot;Page#&quot; &lt;&lt; setw(10) &lt;&lt; &quot;Frame#&quot; &lt;&lt; setw(10) &lt;&lt; &quot;Valid&quot; &lt;&lt; endl;
cout &lt;&lt; string(30, &#39;-&#39;) &lt;&lt; endl;
for (int i = 0; i &lt; NUM_PAGES; i++) {
cout &lt;&lt; setw(10) &lt;&lt; i
&lt;&lt; setw(10) &lt;&lt; (valid[i] ? to_string(pageTable[i]) : &quot;N/A&quot;)
&lt;&lt; setw(10) &lt;&lt; (valid[i] ? &quot;Yes&quot; : &quot;No&quot;) &lt;&lt; endl;
}
}
};
int main() {
cout &lt;&lt; &quot;ADDRESS TRANSLATION SIMULATOR&quot; &lt;&lt; endl;
cout &lt;&lt; &quot;=============================&quot; &lt;&lt; endl;
cout &lt;&lt; &quot;Page Size: &quot; &lt;&lt; PAGE_SIZE &lt;&lt; &quot; bytes&quot; &lt;&lt; endl;
cout &lt;&lt; &quot;Number of Pages: &quot; &lt;&lt; NUM_PAGES &lt;&lt; endl;
cout &lt;&lt; &quot;Number of Frames: &quot; &lt;&lt; NUM_FRAMES &lt;&lt; endl &lt;&lt; endl;
PageTable pt;
// Test with various logical addresses
int testAddresses[] = {0, 1024, 2048, 5120, 10240, 65535};
for (int addr : testAddresses) {
cout &lt;&lt; &quot;\n--- Translation Test ---&quot; &lt;&lt; endl;
pt.translateAddress(addr);
}
// Display complete page table
pt.displayPageTable();
// Interactive mode
char choice;

cout &lt;&lt; &quot;\nEnter addresses interactively? (y/n): &quot;;
cin &gt;&gt; choice;
if (choice == &#39;y&#39; || choice == &#39;Y&#39;) {
int addr;
do {
cout &lt;&lt; &quot;\nEnter logical address (-1 to quit): &quot;;
cin &gt;&gt; addr;
if (addr &gt;= 0) {
pt.translateAddress(addr);
}
} while (addr &gt;= 0);
}
return 0;
}
