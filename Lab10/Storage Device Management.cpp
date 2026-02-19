#include &lt;iostream&gt;
#include &lt;vector&gt;

#include &lt;bitset&gt;
using namespace std;
const int TOTAL_BLOCKS = 16;
class DiskManager {
bitset&lt;TOTAL_BLOCKS&gt; freeBlocks;
public:
DiskManager() { freeBlocks.set(); } // all free
int allocate() {
for (int i = 0; i &lt; TOTAL_BLOCKS; i++)
if (freeBlocks[i]) { freeBlocks[i] = 0; return i; }
return -1; // disk full
}
void release(int block) { freeBlocks[block] = 1; }
void status() {
cout &lt;&lt; &quot;Free blocks: &quot; &lt;&lt; freeBlocks.count() &lt;&lt; &quot;/&quot; &lt;&lt; TOTAL_BLOCKS &lt;&lt; endl;
}
};
int main() {
DiskManager dm;
int b1 = dm.allocate();
int b2 = dm.allocate();
dm.status();
dm.release(b1);
dm.status();
return 0;
}
Q5 Storage Device
