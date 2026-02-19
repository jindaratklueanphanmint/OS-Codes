#include &lt;iostream&gt;
#include &lt;map&gt;
using namespace std;
class SwapManager {
int swapSize; // in MB
int usedSwap;
map&lt;int,int&gt; swapTable; // pid -&gt; MB used
public:
SwapManager(int size) : swapSize(size), usedSwap(0) {}
bool swapOut(int pid, int mb) {
if (usedSwap + mb &gt; swapSize) return false;
swapTable[pid] = mb;
usedSwap += mb;
cout &lt;&lt; &quot;Process &quot; &lt;&lt; pid &lt;&lt; &quot; swapped out (&quot; &lt;&lt; mb &lt;&lt; &quot;MB)&quot; &lt;&lt; endl;
return true;
}
void swapIn(int pid) {
if (swapTable.count(pid)) {
usedSwap -= swapTable[pid];
swapTable.erase(pid);
cout &lt;&lt; &quot;Process &quot; &lt;&lt; pid &lt;&lt; &quot; swapped back in&quot; &lt;&lt; endl;
}
}
};
int main() {
SwapManager sm(512);
sm.swapOut(1, 128);
sm.swapOut(2, 256);
sm.swapOut(3, 200); // should fail
sm.swapIn(1);
sm.swapOut(3, 200); // now succeeds
return 0;
}
