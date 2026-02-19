#include &lt;iostream&gt;
#include &lt;queue&gt;
using namespace std;
struct NVMRequest {
int lba; // Logical Block Address
string type; // &quot;read&quot; or &quot;write&quot;
};
void processNVM(queue&lt;NVMRequest&gt;&amp; q) {
while (!q.empty()) {
NVMRequest r = q.front(); q.pop();
// NVM has near-uniform access time — no seek needed
cout &lt;&lt; r.type &lt;&lt; &quot; LBA &quot; &lt;&lt; r.lba
&lt;&lt; &quot; -&gt; latency: ~0.1ms&quot; &lt;&lt; endl;
}
}
int main() {
queue&lt;NVMRequest&gt; q;
q.push({100, &quot;read&quot;});
q.push({5, &quot;write&quot;});
q.push({999, &quot;read&quot;});
processNVM(q);
return 0;
}
